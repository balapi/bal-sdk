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
 * bcmcli_session.h
 *
 * BCM CLI engine - session management
 *
 *******************************************************************/

#ifndef BCMCLI_SESSION_H

#define BCMCLI_SESSION_H

#include <bcmos_system.h>
#include <stdarg.h>
#include "bcmolt_string.h"

/** \defgroup bcmcli_session Management Session Control
 *
 * APIs in this header file allow to create/destroy management sessions.
 * Management session is characterized by its access level and also
 * input/output functions.
 * Management sessions allow managed entities in the system to communicate
 * with local or remote managers (e.g., local or remote shell or NMS)
 * @{
 */

/** Access rights */
typedef enum
{
    BCMCLI_ACCESS_GUEST,     /**< Guest. Doesn't have access to commands and directories registered with ADMIN rights */
    BCMCLI_ACCESS_ADMIN,     /**< Administrator: full access */
    BCMCLI_ACCESS_DEBUG,     /**< Administrator: full access + extended debug features */
} bcmcli_access_right;

/** Line edit mode */
typedef enum
{
    BCMCLI_LINE_EDIT_DEFAULT,/**< Enable line editing and history if CONFIG_EDITLINE is defined, disable otherwise */
    BCMCLI_LINE_EDIT_ENABLE, /**< Enable line editing. Requires CONFIG_EDITLINE define and libedit-dev library */
    BCMCLI_LINE_EDIT_DISABLE,/**< Disable line editing and history */
} bcmcli_line_edit_mode;


/** Management session handle
 */
typedef struct bcmcli_session bcmcli_session;


/** Session parameters structure.
 * See \ref bcmcli_session_open
 */
typedef struct bcmcli_session_parm
{
    const char *name;       /**< Session name */
    void *user_priv;        /**< Private user's data */

    /** Session's output function. NULL=use write(stdout)
     * returns the number of bytes written or <0 if error
     */
    int (*write)(bcmcli_session *session, const char *buf, uint32_t size);

    /** Session line input function. NULL=use default(stdin[+line edit) */
    char *(*gets)(bcmcli_session *session, char *buf, uint32_t size);

    /** Session char input function. NULL=use bcmos_getchar() */
    int (*get_char)(bcmcli_session *session);

    /** Fill the specified buffer with the prompt for this session (NULL-terminated). NULL = no prompt. */
    void (*get_prompt)(bcmcli_session *session, char *buf, uint32_t max_len);

    /** Access rights */
    bcmcli_access_right access_right;

    /** Line editing mode */
    bcmcli_line_edit_mode line_edit_mode;

    /** Stack size for per-session dynamic memory allocation. */
    uint32_t stack_size;
#define BCMCLI_SESSION_MIN_STACK_SIZE    (128 * 1024)

    /** Extra data size to be allocated along with session control block.
     * The extra data is accessible using bcmcli_session_data().
     * Please note that if session is created using bcmcli_session_open(),
     * extra_size is reserved.
     * It can only be used for user context allocation if session is created
     * using bcmcli_session_open_user()
     */
    uint32_t extra_size;
} bcmcli_session_parm;


/** Open monitor session
 *
 * Monitor supports multiple simultaneous sessions with different
 * access rights.
 * Note that there already is a default session with full administrative rights,
 * that takes input from stdin and outputs to stdout.
 *
 * Please don't use parm.extra_size. This field is reserved.
 *
 * \param[in]   parm        Session parameters. Must not be allocated on the stack.
 * \param[out]  p_session   Session handle
 * \return
 *      0   =OK\n
 *      <0  =error code
 */
bcmos_errno bcmcli_session_open(const bcmcli_session_parm *parm, bcmcli_session **p_session);


/** Close monitor session.
 * \param[in]   session         Session handle
 */
void bcmcli_session_close(bcmcli_session *session);


/** Write function.
 * Write buffer to the current session.
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   buf             output buffer
 * \param[in]   size            number of bytes to be written
 * \return
 *  >=0 - number of bytes written\n
 *  <0  - output error
 */
int bcmcli_session_write(bcmcli_session *session, const char *buf, uint32_t size);


/** Read line
 * \param[in]       session         Session handle. NULL=use default
 * \param[in,out]   buf             input buffer
 * \param[in]       size            buf size
 * \return
 *      buf if successful
 *      NULL if EOF or error
 */
char *bcmcli_session_gets(bcmcli_session *session, char *buf, uint32_t size);


/** Print function.
 * Prints in the context of current session.
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   format          print format - as in printf
 */
void bcmcli_session_print(bcmcli_session *session, const char *format, ...)
#ifndef BCMCLI_SESSION_DISABLE_FORMAT_CHECK
    __attribute__((format(printf, 2, 3)))
#endif
    ;

/** Print function.
 * Prints in the context of current session.
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   format          print format - as in printf
 * \param[in]   ap              parameters list. Undefined after the call
 */
void bcmcli_session_vprint(bcmcli_session *session, const char *format, va_list ap);

/** Print buffer in hexadecimal format
 * \param[in]   session         Session handle. NULL=use stdout
 * \param[in]   buffer          Buffer address
 * \param[in]   offset          Start offset in the buffer
 * \param[in]   count           Number of bytes to dump
 * \param[in]   indent          Optional indentation string
 */
void bcmcli_session_hexdump(bcmcli_session *session, const void *buffer, uint32_t offset, uint32_t count, const char *indent);

/** Get extra data associated with the session
 * \param[in]       session         Session handle. NULL=default session
 * \return extra_data pointer or NULL if there is no extra data
 */
void *bcmcli_session_data(bcmcli_session *session);


/** Get user_priv provided in session parameters when it was registered
 * \param[in]       session         Session handle. NULL=default session
 * \return usr_priv value
 */
void *bcmcli_session_user_priv(bcmcli_session *session);


/** Get session name
 * \param[in]       session         Session handle. NULL=use stdin
 * \return session name
 */
const char *bcmcli_session_name(bcmcli_session *session);


/** Get session access rights
 * \param[in]       session         Session handle. NULL=default debug session
 * \return session access right
 */
bcmcli_access_right bcmcli_session_access_right(bcmcli_session *session);

/** @} end of bcmcli_session group */

/** Low-level interface for when session is used outside CLI
 *
 * \param[in]   parm        Session parameters. Must not be allocated on the stack.
 * \param[out]  p_session   Session handle
 * \return
 *      0   =OK\n
 *      <0  =error code
 */
bcmos_errno bcmcli_session_open_user(const bcmcli_session_parm *parm, bcmcli_session **p_session);

/** Open a session that prints to the specified string
 */
bcmos_errno bcmcli_session_open_string(bcmcli_session **session, bcmolt_string *str);

/** Allocate memory from session stack
 *
 * \param[in]       session         Session handle
 * \param[in]       size            Size of memory block to be allocated
 * \return address of memory block or NULL
 */
void *bcmcli_session_stack_calloc(bcmcli_session *session, uint32_t size);

/** Reset session stack
 *
 * \param[in]       session         Session handle
 */
void bcmcli_session_stack_reset(bcmcli_session *session);

/** Configure RAW input mode
 *
 * \param[in]       session         Session handle
 * \param[in]       is_raw          TRUE=enable raw mode, FALSE=disable raw mode
 * \return
 *      =0  - OK \n
 *      BCM_ERR_NOT_SUPPORTED - raw mode is not supported\n
 */
bcmos_errno bcmcli_session_raw_mode_set(bcmcli_session *session, bcmos_bool is_raw);

/** Context extension
 *
 * - if no command - display list of command or extend command
 * - if prev char is " "
 *      - if positional and next parm is enum - show/extends list of matching values
 *      - else - show/extend list of unused parameters
 *   else
 *      - if entering value and enum - show/extends list of matching values
 *      - else - show/extend list of matching unused parameters
 *
 * \param[in]       session         Session handle
 * \param[in]       input_string    String to be parsed
 * \param[out]      insert_str      String to insert at cursor position
 * \param[in]       insert_size     Insert buffer size
 * \return
 *      =0  - OK \n
 *      BCM_ERR_PARM - parsing error\n
 */
bcmos_errno bcmcli_extend(bcmcli_session *session, char *input_string,
    char *insert_str, uint32_t insert_size);

/** Acquire session write lock.
 * This function is useful to print block of data uninterruptible
 * in multi-thread context
 */
void bcmcli_session_lock(bcmcli_session *session);

/** Release session write lock.
 */
void bcmcli_session_unlock(bcmcli_session *session);

#ifdef BCMCLI_INTERNAL

#define BCMCLI_SESSION_OUTBUF_LEN 4096
#define BCMCLI_SESSION_TAB_COMPLETE_BUF_LEN 4096
#define BCMCLI_SESSION_TAB_COMPLETE_HELP_BUF_LEN (16*1024)
#define BCMCLI_MAX_PROMPT_LEN 10

/* editline functionality */
/* If libedit is included - it takes precedence */
#ifdef CONFIG_LIBEDIT
#include <histedit.h>
#undef CONFIG_LINENOISE
#endif /* #ifdef CONFIG_LIBEDIT */

#ifdef CONFIG_LINENOISE
#include <linenoise.h>
#endif

/* Management session structure */
struct bcmcli_session
{
    bcmcli_session *next;
    bcmcli_session_parm parms;
    uint32_t magic;
#define BCMCLI_SESSION_MAGIC            (('s'<<24)|('e'<<16)|('s'<<8)|'s')
#define BCMCLI_SESSION_MAGIC_DEL        (('s'<<24)|('e'<<16)|('s'<<8)|'~')

    /* Line editing and history support */
#ifdef CONFIG_LIBEDIT
    EditLine *el;
    History *history;
    HistEvent histevent;
#endif
#ifdef CONFIG_LINENOISE
    linenoiseSession *ln_session;
#endif
    struct
    {
        char *start;
        uint32_t size;
        uint32_t allocated;
    } stack;
    char outbuf[BCMCLI_SESSION_OUTBUF_LEN];
    char prompt_buf[BCMCLI_MAX_PROMPT_LEN];
    char tab_complete_buf[BCMCLI_SESSION_TAB_COMPLETE_BUF_LEN];
    char tab_complete_help_buf[BCMCLI_SESSION_TAB_COMPLETE_HELP_BUF_LEN];
    bcmolt_string tab_complete_help_string;
    bcmos_bool tab_complete_mode;   /* In tab-complete mode bcmcli_session_print() "prints" to tab_complete_help_buf */
    bcmos_mutex write_lock;

    /* Followed by session data */
};
#endif

#ifndef ENABLE_CLI
#define bcmcli_session_print(session, format, ...) \
    do \
    { \
    } \
    while (0)
#define bcmcli_session_open_user(parm, p_session) BCM_ERR_OK;
#define bcmcli_session_close(s_session) \
    do \
    { \
    } \
    while (0)
#endif

#ifndef ENABLE_CLI
#define bcmcli_session_vprint(session, format, ap) \
    do \
    { \
    } \
    while (0)
#define bcmcli_session_open_user(parm, p_session) BCM_ERR_OK;
#define bcmcli_session_close(s_session) \
    do \
    { \
    } \
    while (0)
#endif

#endif /* #ifndef BCMCLI_SESSION_H */
