/*
<:copyright-BRCM:2016-2020:Apache:standard

 Copyright (c) 2016-2020 Broadcom. All Rights Reserved

 The term “Broadcom” refers to Broadcom Inc. and/or its subsidiaries

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

:>
 */


/*******************************************************************
 * bcmcli_session.c
 *
 * CLI engine - session management
 *
 *******************************************************************/

#include <bcmos_system.h>
#include <bcmolt_utils.h>

#define BCMCLI_INTERNAL
#include <bcmcli_session.h>

static bcmos_fastlock session_lock;
static bcmcli_session *session_list;
static int session_module_initialized;

/*
 * Internal functions
 */

static void _bcmcli_session_update_prompt(bcmcli_session *session)
{
    if (!session)
        return;

    if (session->parms.get_prompt)
    {
        session->parms.get_prompt(session, session->prompt_buf, BCMCLI_MAX_PROMPT_LEN);
        session->prompt_buf[BCMCLI_MAX_PROMPT_LEN - 1] = '\0';
    }
    else
    {
        session->prompt_buf[0] = '\0';
    }
}

static char *_bcmcli_session_gets(bcmcli_session *session, char *buffer, uint32_t size)
{
    const char *line = NULL;
    _bcmcli_session_update_prompt(session);
#ifdef CONFIG_LIBEDIT
    if (session && session->el && session->history)
    {
        int line_len;
        line = (el_gets(session->el, &line_len));
        if (!line)
            return NULL;
        if (line_len > size)
        {
            bcmos_printf("%s: buffer is too short %u - got %d. Truncated\n",
                        __FUNCTION__, size, line_len);
        }
        strncpy(buffer, line, size);
        if (*line && *line != '\n' && *line != '#')
            history(session->history, &session->histevent, H_ENTER, line);
    }
    else
#endif
#ifdef CONFIG_LINENOISE
    if (session && session->ln_session)
    {
        char *ln_line = linenoise(session->ln_session, session->prompt_buf, buffer, size);
        if (ln_line)
        {
            if (strlen(ln_line))
            {
                linenoiseHistoryAdd(session->ln_session, ln_line); /* Add to the history. */
            }
            else
            {
                strncpy(buffer, "\n", size-1);
            }
            buffer[size-1] = 0;
            line = buffer;
        }
    }
    else
#endif
    {
        bcmcli_session_print(session, "%s", session->prompt_buf);
        if (session && session->parms.gets)
            line = session->parms.gets(session, buffer, size);
        else
            line = fgets(buffer, size, stdin);
    }
    return line ? buffer : NULL;
}

#ifdef CONFIG_LIBEDIT

static char *_bcmcli_editline_prompt(EditLine *e)
{
    bcmcli_session *session = NULL;
    el_get(e, EL_CLIENTDATA, &session);
    BUG_ON(session == NULL || session->magic != BCMCLI_SESSION_MAGIC);
    _bcmcli_session_update_prompt(session);
    return session->prompt_buf;
}

static int _bcmcli_editline_cfn(EditLine *el, char *c)
{
    bcmcli_session *session = NULL;
    char insert_buf[80];
    int c1;
    bcmos_errno rc;

    el_get(el, EL_CLIENTDATA, &session);
    BUG_ON(session == NULL || session->magic != BCMCLI_SESSION_MAGIC);
    c1 = session->parms.get_char(session);

    /* ToDo: handle \t parameter extension */
    while (c1 > 0 && c1 == '\t')
    {
        const LineInfo *li = el_line(el);
        if (li->cursor - li->buffer > sizeof(session->tab_complete_buf))
            return -1;
        memcpy(session->tab_complete_buf, li->buffer, li->cursor - li->buffer);
        session->tab_complete_buf[li->cursor - li->buffer] = 0;
        rc = bcmcli_extend(session, session->tab_complete_buf, insert_buf, sizeof(insert_buf));
        if (rc)
        {
            c1 = session->parms.get_char(session);
            continue;
        }
        el_insertstr(el, insert_buf);
        printf("\r");
        el_set(el, EL_REFRESH, NULL);
        c1 = session->parms.get_char(session);
    }
    if (c1 < 0)
        return -1;
    *c = c1;
    return 1;
}
#endif

/* linenoise line editing library: completion support */
#ifdef CONFIG_LINENOISE

static int _bcmcli_linenoise_read_char(long fd_in, char *c)
{
    bcmcli_session *session = (bcmcli_session *)fd_in;
    int c1;
    c1 = session->parms.get_char(session);
    if (c1 < 0)
    {
        return -1;
    }
    *c = c1;
    return 1;
}

static int _bcmcli_linenoise_write(long fd_out, const char *buf, size_t len)
{
    bcmcli_session *session = (bcmcli_session *)fd_out;
    /* Use a shortcut for len==1 - which is char-by-char input.
       bcmos_printf("%*s", buf, 1) misbehaves on vxw platform,
       possibly because it is too slow.
    */
    if (len == 1 && !session->parms.write)
    {
        bcmos_putchar(buf[0]);
        return 1;
    }
    return bcmcli_session_write(session, buf, len);
}

static int _bcmcli_linenoise_tab(linenoiseSession *ln_session, char *buf, size_t buf_size, int *p_pos, const char **help)
{
    bcmcli_session *session = NULL;
    int pos = *p_pos;
    char insert_buf[80]="";
    int len;

    session = linenoiseSessionData(ln_session);
    BUG_ON(session == NULL || session->magic != BCMCLI_SESSION_MAGIC);
    bcmolt_strncpy(session->tab_complete_buf, buf, sizeof(session->tab_complete_buf));
    bcmolt_string_init(&session->tab_complete_help_string, session->tab_complete_help_buf, sizeof(session->tab_complete_help_buf));
    session->tab_complete_mode = BCMOS_TRUE;
    bcmcli_extend(session, session->tab_complete_buf, insert_buf, sizeof(insert_buf));
    session->tab_complete_mode = BCMOS_FALSE;

    len = strlen(buf);
    if (pos >=0 && pos < len)
    {
        bcmolt_strncpy(session->tab_complete_buf, buf, pos + 1);
        bcmolt_strncat(session->tab_complete_buf, insert_buf, sizeof(session->tab_complete_buf));
        bcmolt_strncat(session->tab_complete_buf, &buf[pos], sizeof(session->tab_complete_buf));
        pos += strlen(insert_buf);
    }
    else
    {
        bcmolt_strncpy(session->tab_complete_buf, buf, sizeof(session->tab_complete_buf));
        bcmolt_strncat(session->tab_complete_buf, insert_buf, sizeof(session->tab_complete_buf));
        pos = strlen(session->tab_complete_buf);
    }
    *p_pos = pos;
    bcmolt_strncpy(buf, session->tab_complete_buf, buf_size);
    *help = bcmolt_string_get(&session->tab_complete_help_string);
    return 1;
}

#endif

/* Default getc function */
static int _bcmcli_session_get_char(bcmcli_session *session)
{
    return bcmos_getchar();
}

/** Initialize session management module
 * \return
 *      0   =OK\n
 *      <0  =error code
 */
static void bcmcli_session_module_init(void)
{
    bcmos_fastlock_init(&session_lock, 0);
    session_module_initialized = 1;
}

/** Open management session */
bcmos_errno bcmcli_session_open_user(const bcmcli_session_parm *parm, bcmcli_session **p_session)
{
    bcmcli_session *session;
    bcmcli_session **p_last_next;
    const char *name;
    char *name_clone;
    uint32_t stack_size;
    long flags;

    if (!p_session || !parm)
        return BCM_ERR_PARM;
#ifndef CONFIG_EDITLINE
    if (parm->line_edit_mode == BCMCLI_LINE_EDIT_ENABLE)
    {
        bcmos_trace(BCMOS_TRACE_LEVEL_ERROR, "Line editing feature is not compiled in. define CONFIG_EDITLINE\n");
        return BCM_ERR_NOT_SUPPORTED;
    }
#endif
    if (!session_module_initialized)
        bcmcli_session_module_init();
    name = parm->name;
    if (!name)
        name = "*unnamed*";

    stack_size = (parm->stack_size > BCMCLI_SESSION_MIN_STACK_SIZE) ? parm->stack_size : BCMCLI_SESSION_MIN_STACK_SIZE;
    session=bcmos_calloc(sizeof(bcmcli_session) + strlen(name) + 1 + parm->extra_size + stack_size);
    if (!session)
        return BCM_ERR_NOMEM;
    session->parms = *parm;
    session->stack.start = (char *)session + sizeof(bcmcli_session) + parm->extra_size;
    session->stack.size = stack_size;
    name_clone = session->stack.start + session->stack.size;
    strcpy(name_clone, name);
    session->parms.name = name_clone;

    if (!session->parms.get_char)
        session->parms.get_char = _bcmcli_session_get_char;

#ifdef CONFIG_LIBEDIT
    if (!parm->gets && (parm->line_edit_mode == BCMCLI_LINE_EDIT_ENABLE ||
        parm->line_edit_mode == BCMCLI_LINE_EDIT_DEFAULT))
    {
        /* Initialize editline library */
        session->el = el_init(session->parms.name, stdin, stdout, stderr);
        session->history = history_init();
        if (session->el && session->history)
        {
            el_set(session->el, EL_EDITOR, "emacs");
            el_set(session->el, EL_PROMPT, &_bcmcli_editline_prompt);
            el_set(session->el, EL_TERMINAL, "xterm");
            el_set(session->el, EL_GETCFN, _bcmcli_editline_cfn);
            el_set(session->el, EL_CLIENTDATA, session);
            history(session->history, &session->histevent, H_SETSIZE, 800);
            el_set(session->el, EL_HIST, history, session->history);
        }
        else
        {
            bcmos_trace(BCMOS_TRACE_LEVEL_ERROR, "Can't initialize editline library\n");
            bcmos_free(session);
            return BCM_ERR_INTERNAL;
        }
    }
#endif

#ifdef CONFIG_LINENOISE
    /* Set the completion callback. This will be called every time the
     * user uses the <tab> key. */
    if (!parm->gets && (parm->line_edit_mode == BCMCLI_LINE_EDIT_ENABLE ||
                        parm->line_edit_mode == BCMCLI_LINE_EDIT_DEFAULT))
    {
        linenoiseSessionIO io={.fd_in=(long)session, .fd_out=(long)session,
            .read_char=_bcmcli_linenoise_read_char,
            .write=_bcmcli_linenoise_write
        };
        if (linenoiseSessionOpen(&io, session, &session->ln_session))
        {
            bcmos_trace(BCMOS_TRACE_LEVEL_ERROR, "Can't create linenoise session\n");
            bcmos_free(session);
            return BCM_ERR_INTERNAL;
        }
        linenoiseSetCompletionCallback(session->ln_session, _bcmcli_linenoise_tab);
    }
#endif

    bcmos_mutex_create(&session->write_lock, 0, "cli_session");
    session->magic = BCMCLI_SESSION_MAGIC;

    flags = bcmos_fastlock_lock(&session_lock);
    p_last_next = &session_list;
    while(*p_last_next)
        p_last_next = &((*p_last_next)->next);
    *p_last_next = session;
    bcmos_fastlock_unlock(&session_lock, flags);

    *p_session = session;

    return BCM_ERR_OK;
}

static int bcmcli_session_string_write(bcmcli_session *session, const char *buf, uint32_t size)
{
    bcmolt_string *str = bcmcli_session_user_priv(session);
    return bcmolt_string_copy(str, buf, size);
}

bcmos_errno bcmcli_session_open_string(bcmcli_session **session, bcmolt_string *str)
{
    bcmcli_session_parm sp = { .user_priv = str, .write = bcmcli_session_string_write };

    return bcmcli_session_open_user(&sp, session);
}

/** Close management session.
 * \param[in]   session         Session handle
 */
void bcmcli_session_close(bcmcli_session *session)
{
    long flags;

    BUG_ON(session->magic != BCMCLI_SESSION_MAGIC);
    flags = bcmos_fastlock_lock(&session_lock);
    if (session==session_list)
        session_list = session->next;
    else
    {
        bcmcli_session *prev = session_list;
        while (prev && prev->next != session)
            prev = prev->next;
        if (!prev)
        {
            bcmos_fastlock_unlock(&session_lock, flags);
            bcmos_trace(BCMOS_TRACE_LEVEL_ERROR, "%s: can't find session\n", __FUNCTION__);
            return;
        }
        prev->next = session->next;
    }
    bcmos_fastlock_unlock(&session_lock, flags);

#ifdef CONFIG_LIBEDIT
    if (session->history)
        history_end(session->history);
    if (session->el)
        el_end(session->el);
#endif
#ifdef CONFIG_LINENOISE
    if (session->ln_session)
        linenoiseSessionClose(session->ln_session);
#endif
    bcmos_mutex_destroy(&session->write_lock);
    session->magic = BCMCLI_SESSION_MAGIC_DEL;
    bcmos_free(session);

}

/** Configure RAW input mode
 *
 * \param[in]       session         Session handle
 * \param[in]       is_raw          TRUE=enable raw mode, FALSE=disable raw mode
 * \return
 *      =0  - OK \n
 *      BCM_ERR_NOT_SUPPORTED - raw mode is not supported\n
 */
bcmos_errno bcmcli_session_raw_mode_set(bcmcli_session *session, bcmos_bool is_raw)
{
#ifdef CONFIG_LINENOISE
    int rc;
    if (session->parms.gets)
        return BCM_ERR_NOT_SUPPORTED;
    rc = linenoiseSetRaw(session->ln_session, is_raw);
    return (rc == 0) ? BCM_ERR_OK : BCM_ERR_NOT_SUPPORTED;
#else
    return BCM_ERR_NOT_SUPPORTED;
#endif
}

/** Default write callback function
 * write to stdout
 */
static int _bcmcli_session_write(bcmcli_session *session, const char *buf, uint32_t size)
{
    return bcmos_printf("%.*s", size, buf);
}


/** Write function.
 * Write buffer to the current session.
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   buffer          output buffer
 * \param[in]   size            number of bytes to be written
 * \return
 *  >=0 - number of bytes written\n
 *  <0  - output error
 */
int bcmcli_session_write(bcmcli_session *session, const char *buf, uint32_t size)
{
    int (*write_cb)(bcmcli_session *session, const char *buf, uint32_t size);
    if (session && session->parms.write)
    {
        BUG_ON(session->magic != BCMCLI_SESSION_MAGIC);
        write_cb = session->parms.write;
    }
    else
        write_cb = _bcmcli_session_write;
    return write_cb(session, buf, size);
}


/** Read line
 * \param[in]       session         Session handle. NULL=use default
 * \param[in,out]   buf             input buffer
 * \param[in]       size            buf size
 * \return
 *      buf if successful
 *      NULL if EOF or error
 */
char *bcmcli_session_gets(bcmcli_session *session, char *buf, uint32_t size)
{
    return _bcmcli_session_gets(session, buf, size);
}

/** Acquire session write lock.
 * This function is useful to print block of data uninterruptible
 * in multi-thread context
 */
void bcmcli_session_lock(bcmcli_session *session)
{
    if (session == NULL)
        return;
    bcmos_mutex_lock(&session->write_lock);
}

/** Release session write lock.
 */
void bcmcli_session_unlock(bcmcli_session *session)
{
    if (session == NULL)
        return;
    bcmos_mutex_unlock(&session->write_lock);
}


/** Print function.
 * Prints in the context of current session.
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   format          print format - as in printf
 * \param[in]   ap              parameters list. Undefined after the call
 */
void bcmcli_session_vprint(bcmcli_session *session, const char *format, va_list ap)
{
    bcmcli_session_lock(session);
    if (session && (session->parms.write != NULL || session->tab_complete_mode))
    {
        BUG_ON(session->magic != BCMCLI_SESSION_MAGIC);
        vsnprintf(session->outbuf, sizeof(session->outbuf), format, ap);
        session->outbuf[sizeof(session->outbuf) - 1] = 0;
        if (session->tab_complete_mode)
            bcmolt_string_append(&session->tab_complete_help_string, "%s", session->outbuf);
        else
            bcmcli_session_write(session, session->outbuf, strlen(session->outbuf));
    }
    else
    {
        bcmos_vprintf(format, ap);
    }
    bcmcli_session_unlock(session);
}


/** Print function.
 * Prints in the context of current session.
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   format          print format - as in printf
 */
void bcmcli_session_print(bcmcli_session *session, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    bcmcli_session_vprint(session, format, ap);
    va_end(ap);
}

/** Get user_priv provoded in session partameters when it was registered
 * \param[in]       session         Session handle. NULL=use stdin
 * \return usr_priv value
 */
void *bcmcli_session_user_priv(bcmcli_session *session)
{
    if (!session)
        return NULL;
    BUG_ON(session->magic != BCMCLI_SESSION_MAGIC);
    return session->parms.user_priv;
}


/** Get extra data associated with the session
 * \param[in]       session         Session handle. NULL=default session
 * \return extra_data pointer or NULL if there is no extra data
 */
void *bcmcli_session_data(bcmcli_session *session)
{
    if (!session)
        return NULL;
    BUG_ON(!(session->magic == BCMCLI_SESSION_MAGIC  || session->magic == BCMCLI_SESSION_MAGIC_DEL));
    if (session->parms.extra_size <= 0)
        return NULL;
    return (char *)session + sizeof(*session);
}


/** Get session namedata
 * \param[in]       session         Session handle. NULL=default session
 * \return session name
 */
const char *bcmcli_session_name(bcmcli_session *session)
{
    if (!session)
        return NULL;
    BUG_ON(session->magic != BCMCLI_SESSION_MAGIC);
    return session->parms.name;
}


/** Get session access righte
 * \param[in]       session         Session handle. NULL=default debug session
 * \return session access right
 */
bcmcli_access_right bcmcli_session_access_right(bcmcli_session *session)
{
    if (!session)
        return BCMCLI_ACCESS_DEBUG;
    BUG_ON(session->magic != BCMCLI_SESSION_MAGIC);
    return session->parms.access_right;
}

/** Print buffer in hexadecimal format
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   buffer          Buffer address
 * \param[in]   offset          Start offset in the buffer
 * \param[in]   count           Number of bytes to dump
 * \param[in]   indent          Optional indentation string
 */
void bcmcli_session_hexdump(bcmcli_session *session, const void *buffer, uint32_t offset, uint32_t count, const char *indent)
{
    bcmos_hexdump((bcmos_msg_print_cb)bcmcli_session_print, session, buffer, offset, count, indent);
}

/** Allocate memory from session stack
 *
 * \param[in]       session         Session handle
 * \param[in]       size            Size of memory block to be allocated
 * \return address of memory block or NULL
 */
void *bcmcli_session_stack_calloc(bcmcli_session *session, uint32_t size)
{
    void *ptr;

    size = BCMOS_ROUND_UP(size, sizeof(void *));
    if (session->stack.allocated + size > session->stack.size)
        return NULL;
    ptr = &session->stack.start[session->stack.allocated];
    session->stack.allocated += size;
    memset(ptr, 0, size);
    return ptr;
}

/** Reset session stack
 *
 * \param[in]       session         Session handle
 */
void bcmcli_session_stack_reset(bcmcli_session *session)
{
    session->stack.allocated = 0;
}

/*
 * Exports
 */
EXPORT_SYMBOL(bcmcli_session_open);
EXPORT_SYMBOL(bcmcli_session_close);
EXPORT_SYMBOL(bcmcli_session_write);
EXPORT_SYMBOL(bcmcli_session_vprint);
EXPORT_SYMBOL(bcmcli_session_print);
EXPORT_SYMBOL(bcmcli_session_access_right);
EXPORT_SYMBOL(bcmcli_session_data);
EXPORT_SYMBOL(bcmcli_session_name);
EXPORT_SYMBOL(bcmcli_session_hexdump);
