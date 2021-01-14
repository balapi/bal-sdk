/* linenoise.c -- guerrilla line editing library against the idea that a
 * line editing lib needs to be 20,000 lines of C code.
 *
 * You can find the latest source code at:
 *
 *   http://github.com/antirez/linenoise
 *
 * Does a number of crazy assumptions that happen to be true in 99.9999% of
 * the 2010 UNIX computers around.
 *
 * ------------------------------------------------------------------------
 *
 * Copyright (c) 2010-2013, Salvatore Sanfilippo <antirez at gmail dot com>
 * Copyright (c) 2010-2013, Pieter Noordhuis <pcnoordhuis at gmail dot com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ------------------------------------------------------------------------
 *
 * References:
 * - http://invisible-island.net/xterm/ctlseqs/ctlseqs.html
 * - http://www.3waylabs.com/nw/WWW/products/wizcon/vt220.html
 *
 * Todo list:
 * - Filter bogus Ctrl+<char> combinations.
 * - Win32 support
 *
 * Bloat:
 * - History search like Ctrl+r in readline?
 *
 * List of escape sequences used by this program, we do everything just
 * with three sequences. In order to be so cheap we may have some
 * flickering effect with some slow terminal, but the lesser sequences
 * the more compatible.
 *
 * CHA (Cursor Horizontal Absolute)
 *    Sequence: ESC [ n G
 *    Effect: moves cursor to column n
 *
 * EL (Erase Line)
 *    Sequence: ESC [ n K
 *    Effect: if n is 0 or missing, clear from cursor to end of line
 *    Effect: if n is 1, clear from beginning of line to cursor
 *    Effect: if n is 2, clear entire line
 *
 * CUF (CUrsor Forward)
 *    Sequence: ESC [ n C
 *    Effect: moves cursor forward of n chars
 *
 * When multi line mode is enabled, we also use an additional escape
 * sequence. However multi line editing is disabled by default.
 *
 * CUU (Cursor Up)
 *    Sequence: ESC [ n A
 *    Effect: moves cursor up of n chars.
 *
 * CUD (Cursor Down)
 *    Sequence: ESC [ n B
 *    Effect: moves cursor down of n chars.
 *
 * The following are used to clear the screen: ESC [ H ESC [ 2 J
 * This is actually composed of two sequences:
 *
 * cursorhome
 *    Sequence: ESC [ H
 *    Effect: moves the cursor to upper left corner
 *
 * ED2 (Clear entire screen)
 *    Sequence: ESC [ 2 J
 *    Effect: clear the whole screen
 *
 */

#include <bcmos_system.h>
#define BCM_LINENOISE_BYTE_POOL_SIZE (32*1024) /* each linenoise session has this much dynamic memory available */

#ifndef LINENOISE_DISABLE_TERMIOS
#include <termios.h>
#endif
#ifndef LINENOISE_DISABLE_IOCTL
#include <sys/ioctl.h>
#endif
#include "linenoise.h"

#ifndef STDIN_FILENO
#define STDIN_FILENO  0
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#define LINENOISE_DEFAULT_HISTORY_MAX_LEN 64
#define LINENOISE_MAX_LINE 4096

/* The linenoiseState structure represents the state during line editing.
 * We pass this state to functions implementing specific editing
 * functionalities. */
struct linenoiseState {
    long ifd;           /* Terminal stdin file descriptor. */
    char *buf;          /* Edited line buffer. */
    int buflen;         /* Edited line buffer size. */
    const char *prompt; /* Prompt to display. */
    const char *help;   /* 1-off help string. Cleared after printing */
    int plen;           /* Prompt length. */
    int pos;            /* Current cursor position. */
    int oldpos;         /* Previous refresh cursor position. */
    int len;            /* Current edited line length. */
    int cols;           /* Number of columns in terminal. */
    int maxrows;        /* Maximum num of rows used so far (multiline mode) */
    int history_index;  /* The history index we are currently editing. */
};

/* Session */
struct linenoiseSession {
    struct linenoiseSession *next;
    struct linenoiseState state;
    linenoiseSessionIO io;
    linenoiseCompletionCallback *completionCallback;
    char *read_ahead_buf;
    int read_ahead_pos;
    int history_max_len;
    int history_len;
    char **history;
    int mlmode;         /* Multi line mode. Default is single line. */
    int rawmode;        /* For atexit() function to check if restore is needed*/
#ifndef LINENOISE_DISABLE_TERMIOS
    struct termios orig_termios; /* In order to restore at exit.*/
#endif
    int dumb_terminal;
    int forced_dumb;
    int ncolreqs;        /* Outstandige get columns requests */
    void *session_data;

    /* BCM additions */
    char byte_pool_buf[BCM_LINENOISE_BYTE_POOL_SIZE];
    bcmos_byte_pool byte_pool;
};

enum KEY_ACTION{
    KEY_NULL = 0,	/* NULL */
    CTRL_A = 1,         /* Ctrl+a */
    CTRL_B = 2,         /* Ctrl-b */
    CTRL_C = 3,         /* Ctrl-c */
    CTRL_D = 4,         /* Ctrl-d */
    CTRL_E = 5,         /* Ctrl-e */
    CTRL_F = 6,         /* Ctrl-f */
    CTRL_H = 8,         /* Ctrl-h */
    KEY_TAB = 9,        /* Tab */
    CTRL_K = 11,        /* Ctrl+k */
    CTRL_L = 12,        /* Ctrl+l */
    KEY_LF = 10,        /* Enter: \n */
    KEY_CR = 13,        /* Enter: \r */
    CTRL_N = 14,        /* Ctrl-n */
    CTRL_P = 16,        /* Ctrl-p */
    CTRL_T = 20,        /* Ctrl-t */
    CTRL_U = 21,        /* Ctrl+u */
    CTRL_W = 23,        /* Ctrl+w */
    ESC = 27,           /* Escape */
    BACKSPACE =  127    /* Backspace */
};

static void refreshLine(linenoiseSession *session);
static void freeHistory(linenoiseSession *session);
static int linenoiseRaw(linenoiseSession *session, char *buf, size_t buflen, const char *prompt);

/* Debugging macro. */
/* #define LINENOISE_DEBUG_MODE */

#ifdef LINENOISE_DEBUG_MODE
#define LINENOISE_DEBUG_FILE    "/tmp/linenoise"
static FILE *lndebug_file;
#define lndebug(fmt, args...) \
    do {\
        fprintf(lndebug_file, "%s:%d " fmt, __FUNCTION__, __LINE__, ##args);\
        fflush(lndebug_file);\
    } while(0)
#else
#define lndebug(fmt, ...)
#endif


/* Session list. ToDo: protect update */
static linenoiseSession *sessions;

/* ======================= BCM additions ====================== */

static void bcm_linenoise_byte_pool_init(linenoiseSession *s)
{
    bcmos_errno err;
    bcmos_byte_pool_parm parms =
    {
        .name = "linenoise",
        .size = BCM_LINENOISE_BYTE_POOL_SIZE,
        .start = s->byte_pool_buf,
    };
    err = bcmos_byte_pool_create(&s->byte_pool, &parms);
    BUG_ON(err != BCM_ERR_OK);
#ifdef LINENOISE_DEBUG_MODE
    lndebug_file = fopen(LINENOISE_DEBUG_FILE, "w");
    BUG_ON(lndebug_file == NULL);
#endif
}

static inline void *bcm_linenoise_alloc(linenoiseSession *s, uint32_t size)
{
    return bcmos_byte_pool_alloc(&s->byte_pool, size);
}

static inline void bcm_linenoise_free(void *ptr)
{
    return bcmos_byte_pool_free(ptr);
}

/* ======================= Low level terminal handling ====================== */

/* Set if to use or not the multi line mode. */
void linenoiseSetMultiLine(linenoiseSession *session, int ml) {
    session->mlmode = ml;
}

int linenoiseGetMultiLine(linenoiseSession *session) {
    return session->mlmode;
}

int linenoiseGetDumbTerminal(linenoiseSession *session) {
    return session->dumb_terminal;
}

/* Raw mode: 1960 magic shit. */
static int enableRawMode(linenoiseSession *session) {
#ifndef LINENOISE_DISABLE_TERMIOS
    struct termios raw;

    if (tcgetattr(session->state.ifd, &session->orig_termios) == -1) goto fatal;

    raw = session->orig_termios;  /* modify the original mode */
    /* input modes: no break, no CR to NL, no parity check, no strip char,
     * no start/stop output control. */
    raw.c_iflag &= ~(BRKINT | IGNBRK | ICRNL | INPCK | ISTRIP | IXON | IXOFF);

    /* output modes - disable post processing */
    /* raw.c_oflag &= ~(OPOST); */

    /* control modes - set 8 bit chars */
    raw.c_cflag |= (CS8 /* | ISIG */);

    /* local modes - echoing off, canonical off, no extended functions,
     * no signal chars (^Z,^C) */
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
    /* control chars - set return condition: min number of bytes and timer.
     * We want read to return every single byte, without timeout. */
    raw.c_cc[VMIN] = 1; raw.c_cc[VTIME] = 0; /* 1 byte, no timer */

    /* put terminal in raw mode after flushing */
    if (tcsetattr(session->state.ifd, TCSAFLUSH, &raw) < 0) goto fatal;
    session->rawmode = 1;
    return 0;

fatal:
    errno = ENOTTY;
    return -1;
#else
    session->rawmode = 1;
    return 0; /* assume raw mode */
#endif
}

static void disableRawMode(linenoiseSession *session) {
    /* Don't even check the return value as it's too late. */
#ifndef LINENOISE_DISABLE_TERMIOS
    if (session->rawmode && tcsetattr(session->state.ifd,TCSAFLUSH,&session->orig_termios) != -1)
        session->rawmode = 0;
#endif
}


/* write ESC sequence */
static int writeEscSequence(linenoiseSession *session, const char *seq, int seq_len)
{
    int n;
    if (!seq)
        return 0;
    if (!seq_len)
        seq_len = strlen(seq);
    n = session->io.write(session->io.fd_out, seq, seq_len);
    return n;
}


/* Try to get the number of columns in the current terminal, or assume 80
 * if it fails. */
static int getColumnsRequest(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
#ifndef LINENOISE_DISABLE_IOCTL
    struct winsize ws;
    if (ioctl(1, TIOCGWINSZ, &ws) == 0 && ws.ws_col != 0)
    {
        l->cols = ws.ws_col;
    }
#endif
    {
        /* 4 sequences: store position, go to right margin, request position, restore position. */
        if (writeEscSequence(session, "\x1b" "7" "\x1b" "[999C" "\x1b" "[6n" "\x1b" "8", 14) != 14)
            goto failed;
        ++session->ncolreqs;
    }
    return l->cols;

failed:
    l->cols = 80;
    lndebug("getColumnsRequest failed: cols=%d\n", l->cols);
    return l->cols;
}

/* Clear the screen. Used to handle ctrl+l */
void linenoiseClearScreen(linenoiseSession *session) {
#ifndef LINENOISE_DEBUG_MODE
    if (writeEscSequence(session, "\x1b[H\x1b[2J", 7) <= 0) {
        /* nothing to do, just to avoid warning. */
    }
#endif
}

/* Beep, used for completion when there is nothing to complete or when all
 * the choices were already shown. */
static void linenoiseBeep(void) {
    fprintf(stderr, "\x7");
    fflush(stderr);
}

static int linenoiseDefaultReadChar(long fd_in, char *c)
{
	int n;
    do {
        n = read(fd_in, c, 1);
    } while(!n || (n==1 && ! *c));
    return n;
}

static int linenoiseDefaultWrite(long fd_out, const char *buf, size_t len)
{
    return write(fd_out, buf, len);
}

int linenoiseSessionOpen(const linenoiseSessionIO *io, void *session_data, linenoiseSession **session)
{
    linenoiseSession *s;
    if (!io || !session)
        return -1;
    s = bcmos_calloc(sizeof(*s));
    if (!s)
        return -1;
    s->history_max_len = LINENOISE_DEFAULT_HISTORY_MAX_LEN;
    s->io = *io;
    s->dumb_terminal = io->dumb_terminal;
    s->session_data = session_data;
    *session = s;
    s->next = sessions;
    sessions = s;

    if (!s->io.read_char)
    {
        s->io.read_char = linenoiseDefaultReadChar;
        if (!s->io.fd_in)
            s->io.fd_in = STDIN_FILENO;
    }
    if (!s->io.write)
    {
        s->io.write = linenoiseDefaultWrite;
        if (!s->io.fd_out)
            s->io.fd_out = STDOUT_FILENO;
    }

    /* IT: temp */
    s->mlmode = 1;
    s->state.ifd = STDIN_FILENO;

    bcm_linenoise_byte_pool_init(s);

    return 0;
}


void linenoiseSessionClose(linenoiseSession *session)
{
    linenoiseSession *s = sessions, *prev=NULL;
    while (s && s != session)
    {
        prev = s;
        s = s->next;
    }
    if (s)
    {
        if (prev)
            prev->next = s->next;
        else
            sessions = s->next;
        disableRawMode(s);
        freeHistory(s);
        if (s->read_ahead_buf)
            bcm_linenoise_free(s->read_ahead_buf);
        bcmos_byte_pool_destroy(&s->byte_pool);
        bcmos_free(s);
    }
}

void *linenoiseSessionData(linenoiseSession *session) {
    return session->session_data;
}


void linenoiseSetDumbTerminal(linenoiseSession *session, int dumb) {
    if (!session->io.dumb_terminal)
    {
        session->dumb_terminal = dumb;
        session->forced_dumb = dumb;
    }
}

/* ============================== Completion ================================ */

/* This is an helper function for linenoiseEdit() and is called when the
 * user types the <tab> key in order to complete the string currently in the
 * input. It can call linenoiseSetBuffer in order to replace the current edit buffer
 */
static void completeLine(linenoiseSession *session) {
    struct linenoiseState *ls = &session->state;

    if (!session->completionCallback(session, ls->buf, ls->buflen, &ls->pos, &ls->help))
    {
        linenoiseBeep();
    }
    ls->len = strlen(ls->buf);
    if (ls->pos < 0 || ls->pos > ls->len)
        ls->pos = ls->len;
    refreshLine(session);
}

/* Register a callback function to be called for tab-completion. */
void linenoiseSetCompletionCallback(linenoiseSession *session, linenoiseCompletionCallback *fn) {
    session->completionCallback = fn;
}

/* =========================== Line editing ================================= */

/* We define a very simple "append buffer" structure, that is an heap
 * allocated string where we can append to. This is useful in order to
 * write all the escape sequences in a buffer and flush them to the standard
 * output in a single call, to avoid flickering effects. */
struct abuf {
    linenoiseSession *s; /* BCM additon */
    char *b;
    int len;
};

static void abInit(struct abuf *ab, linenoiseSession *s) {
    ab->s = s;
    ab->b = NULL;
    ab->len = 0;
}

static void abAppend(struct abuf *ab, const char *s, int len) {
    char *_new = bcm_linenoise_alloc(ab->s, ab->len+len);
    if (_new == NULL) return;
    if (ab->b)
    {
        memcpy(_new,ab->b,ab->len);
        bcm_linenoise_free(ab->b);
    }
    if (s)
        memcpy(_new+ab->len,s,len);
    ab->b = _new;
    ab->len += len;
}

static void abFree(struct abuf *ab) {
    if (ab->b != NULL)
    {
        bcm_linenoise_free(ab->b);
        ab->b = NULL;
    }
}

/* Single line low level cursor refresh.
 */
static void refreshCursorSingleLine(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    char seq[64];
    size_t plen = strlen(l->prompt);
    char *buf = l->buf;
    size_t len = l->len;
    size_t pos = l->pos;
    struct abuf ab;

    while((plen+pos) >= l->cols) {
        buf++;
        len--;
        pos--;
    }
    while (plen+len > l->cols) {
        len--;
    }

    abInit(&ab, session);
    /* Cursor to left edge */
    snprintf(seq,64,"\x1b[999D");
    abAppend(&ab,seq,strlen(seq));
    if (pos+plen)
    {
        snprintf(seq,64,"\x1b[%dC", (int)(pos+plen));
        abAppend(&ab,seq,strlen(seq));
    }
    if (writeEscSequence(session, ab.b, ab.len) == -1) {} /* Can't recover from write error. */
    abFree(&ab);
}

/* Single line low level line refresh.
 *
 * Rewrite the currently edited line accordingly to the buffer content,
 * cursor position, and number of columns of the terminal. */
static void refreshSingleLine(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    char seq[64];
    size_t plen = strlen(l->prompt);
    char *buf = l->buf;
    size_t len = l->len;
    size_t pos = l->pos;
    struct abuf ab;

    while((plen+pos) >= l->cols) {
        buf++;
        len--;
        pos--;
    }
    while (plen+len > l->cols) {
        len--;
    }

    abInit(&ab, session);
    /* Cursor to left edge */
    snprintf(seq,64,"\x1b[999D");
    abAppend(&ab,seq,strlen(seq));
    /* Write the prompt and the current buffer content */
    abAppend(&ab,l->prompt,strlen(l->prompt));
    abAppend(&ab,buf,len);
    /* Erase to right */
    snprintf(seq,64,"\x1b[0K");
    abAppend(&ab,seq,strlen(seq));
    /* Move cursor to original position. */
    snprintf(seq,64,"\x1b[999D");
    abAppend(&ab,seq,strlen(seq));
    if (pos+plen)
    {
        snprintf(seq,64,"\x1b[%dC", (int)(pos+plen));
        abAppend(&ab,seq,strlen(seq));
    }
    if (writeEscSequence(session, ab.b, ab.len) == -1) {} /* Can't recover from write error. */
    abFree(&ab);
}

/* Multi line low level cursor position refresh.
 *
 * Rewrite the currently edited line accordingly to the buffer content,
 * cursor position, and number of columns of the terminal. */
static void refreshCursorMultiLine(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    char seq[64];
    int plen = strlen(l->prompt);
    int old_rpos = (plen+l->oldpos+l->cols)/l->cols; /* cursor relative row. */
    int new_rpos = (plen+l->pos+l->cols)/l->cols; /* cursor relative row. */
    int old_cpos = (plen+l->oldpos)%l->cols; /* cursor relative row. */
    int new_cpos = (plen+l->pos)%l->cols; /* cursor relative row. */
    struct abuf ab;

    /* Update maxrows if needed. */
    if (new_rpos > (int)l->maxrows) new_rpos = l->maxrows;

    lndebug("oldp=%d newp=%d or=%d nr=%d oc=%d nc=%d\n\n", l->oldpos, l->pos, old_rpos, new_rpos, old_cpos, new_cpos);

    abInit(&ab, session);

    /* Handle row */
    if (new_rpos > old_rpos)
    {
        snprintf(seq,64,"\x1b[%dB", new_rpos - old_rpos);
        abAppend(&ab,seq,strlen(seq));
    }
    else if (new_rpos < old_rpos)
    {
        snprintf(seq,64,"\x1b[%dA", old_rpos - new_rpos);
        abAppend(&ab,seq,strlen(seq));
    }

    /* Handle column */
    if (new_cpos > old_cpos)
    {
        snprintf(seq,64,"\x1b[%dC", new_cpos - old_cpos);
        abAppend(&ab,seq,strlen(seq));
    }
    else if (new_cpos < old_cpos)
    {
        snprintf(seq,64,"\x1b[%dD", old_cpos - new_cpos);
        abAppend(&ab,seq,strlen(seq));
    }

    l->oldpos = l->pos;

    if (writeEscSequence(session, ab.b, ab.len) == -1) {} /* Can't recover from write error. */
    abFree(&ab);
}

/* Multi line low level line refresh.
 *
 * Rewrite the currently edited line accordingly to the buffer content,
 * cursor position, and number of columns of the terminal. */
static void refreshMultiLine(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    char seq[64];
    int plen = strlen(l->prompt);
    int rows = (plen+l->len+l->cols-1)/l->cols; /* rows used by current buf. */
    int rpos = (plen+l->oldpos+l->cols)/l->cols; /* cursor relative row. */
    int rpos2; /* rpos after refresh. */
    int old_rows = l->maxrows;
    int pos;
    int j;
    struct abuf ab;

    abInit(&ab, session);

    /* Clear lines only if help string is NULL. Otherwise, print the help string and let
       terminal scroll naturally
    */
    if (l->help == NULL || !strlen(l->help)) {
        /* First step: clear all the lines used before. To do so start by
        * going to the last row. */
        if (old_rows-rpos > 0) {
            lndebug("go down %d", old_rows-rpos);
            snprintf(seq,64,"\x1b[%dB", old_rows-rpos);
            abAppend(&ab,seq,strlen(seq));
        }

        /* Now for every row clear it, go up. */
        for (j = 0; j < old_rows-1; j++) {
            lndebug("clear+up");
            snprintf(seq,64,"\x1b[999D\x1b[0K\x1b[1A");
            abAppend(&ab,seq,strlen(seq));
        }

        /* Clean the top line. */
        lndebug("clear");
        snprintf(seq,64,"\x1b[999D\x1b[0K");
        abAppend(&ab,seq,strlen(seq));
    }
    else {
        abAppend(&ab,l->help,strlen(l->help));
        l->help = NULL;
    }
    /* Write the prompt and the current buffer content */
    abAppend(&ab,l->prompt,strlen(l->prompt));
    abAppend(&ab,l->buf,l->len);

    /* If we are at the very end of the screen with our prompt, we need to
     * emit a newline and move the prompt to the first column. */
    if (l->pos &&
        l->pos == l->len &&
        (l->pos+plen) % l->cols == 0)
    {
        lndebug("<newline>");
        abAppend(&ab,"\n",1);
        snprintf(seq,64,"\x1b[999D");
        abAppend(&ab,seq,strlen(seq));
        rows++;
    }

    /* Move cursor to right position. */
    rpos2 = (plen+l->pos+l->cols)/l->cols; /* current cursor relative row. */
    lndebug("rpos2 %d", rpos2);

    /* Go up till we reach the expected positon. */
    if (rows-rpos2 > 0) {
        lndebug("go-up %d", rows-rpos2);
        snprintf(seq,64,"\x1b[%dA", rows-rpos2);
        abAppend(&ab,seq,strlen(seq));
    }

    /* Set column. */
    lndebug("set col %d", 1+((plen+(int)l->pos) % (int)l->cols));
    snprintf(seq,64,"\x1b[999D");
    abAppend(&ab,seq,strlen(seq));
    pos = ((plen+(int)l->pos) % (int)l->cols);
    if (pos)
    {
        snprintf(seq,64,"\x1b[%dC", pos);
        abAppend(&ab,seq,strlen(seq));
    }
    lndebug("\n");
    l->oldpos = l->pos;

    if (writeEscSequence(session, ab.b, ab.len) == -1) {} /* Can't recover from write error. */
    abFree(&ab);

    /* Update maxrows */
    l->maxrows = rows;

    lndebug(" - out\n");
}

/* Calls the two low level functions refreshCursorSingleLine() or
 * refreshCursorMultiLine() according to the selected mode. */
static void refreshCursor(linenoiseSession *session) {
    int old_cols = session->state.cols;
    /* Re-learn the number of column - in case it changed */
    getColumnsRequest(session);
    if (session->state.cols != old_cols) {
        /* Terminal has been resized. Refresh edited line */
        refreshLine(session);
    }
    else {
        if (session->mlmode)
            refreshCursorMultiLine(session);
        else
            refreshCursorSingleLine(session);
    }
}

/* Calls the two low level functions refreshSingleLine() or
 * refreshMultiLine() according to the selected mode. */
static void refreshLine(linenoiseSession *session) {
    /* Re-learn the number of column - in case it changed */
    getColumnsRequest(session);

    if (session->mlmode)
        refreshMultiLine(session);
    else
        refreshSingleLine(session);
}

/* Insert the character 'c' at cursor current position.
 *
 * On error writing to the terminal -1 is returned, otherwise 0. */
static int linenoiseEditInsert(linenoiseSession *session, char c) {
    struct linenoiseState *l = &session->state;
    if (l->len < l->buflen) {
        if (l->len == l->pos) {
            int plen = strlen(l->prompt);
            int rows = (plen+l->len+l->cols)/l->cols;

            l->buf[l->pos] = c;
            l->pos++;
            l->len++;
            l->buf[l->len] = '\0';
            lndebug(" plen=%d len=%d pos=%d cols=%d buf=<%s>\n",
                (int)l->plen, (int)l->len, (int)l->pos, (int)l->cols, l->buf);
            if (session->io.write(session->io.fd_out, &c, 1) == -1) return -1;
            l->oldpos = l->pos;
            l->maxrows = rows;
        } else {
            memmove(l->buf+l->pos+1,l->buf+l->pos,l->len-l->pos);
            l->buf[l->pos] = c;
            l->len++;
            l->pos++;
            l->buf[l->len] = '\0';
            lndebug(" plen=%d len=%d pos=%d cols=%d buf=<%s>\n",
                l->plen, l->len, l->pos, l->cols, l->buf);
            refreshLine(session);
        }
    }
    return 0;
}

/* Move cursor on the left. */
static void linenoiseEditMoveLeft(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    if (l->pos > 0) {
        l->pos--;
        refreshCursor(session);
    }
}

/* Move cursor on the right. */
static void linenoiseEditMoveRight(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    if (l->pos < l->len) {
        l->pos++;
        refreshCursor(session);
    }
}

/* Move cursor to the start of the line. */
static void linenoiseEditMoveHome(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    if (l->pos != 0) {
        l->pos = 0;
        refreshCursor(session);
    }
}

/* Move cursor to the end of the line. */
static void linenoiseEditMoveEnd(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    if (l->pos != l->len) {
        l->pos = l->len;
        refreshCursor(session);
    }
}

/* strdup implementation */
static inline char *linenoise_strdup(linenoiseSession *session, const char *s)
{
    size_t size = strlen(s) + 1;
    char *new = bcm_linenoise_alloc(session, size);
    if (new)
        memcpy(new, s, size);
    return new;
}

/* Substitute the currently edited line with the next or previous history
 * entry as specified by 'dir'. */
#define LINENOISE_HISTORY_NEXT 0
#define LINENOISE_HISTORY_PREV 1
static void linenoiseEditHistoryNext(linenoiseSession *session, int dir) {
    struct linenoiseState *l = &session->state;
    if (session->history_len > 1) {
        /* Update the current history entry before to
         * overwrite it with the next one. */
        bcm_linenoise_free(session->history[session->history_len - 1 - l->history_index]);
        session->history[session->history_len - 1 - l->history_index] = linenoise_strdup(session, l->buf);
        /* Show the new entry */
        l->history_index += (dir == LINENOISE_HISTORY_PREV) ? 1 : -1;
        if (l->history_index < 0) {
            l->history_index = 0;
            return;
        } else if (l->history_index >= session->history_len) {
            l->history_index = session->history_len-1;
            return;
        }
        strncpy(l->buf,session->history[session->history_len - 1 - l->history_index],l->buflen);
        l->buf[l->buflen-1] = '\0';
        l->len = l->pos = strlen(l->buf);
        refreshLine(session);
    }
}

/* Delete the character at the right of the cursor without altering the cursor
 * position. Basically this is what happens with the "Delete" keyboard key. */
static void linenoiseEditDelete(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    if (l->len > 0 && l->pos < l->len) {
        memmove(l->buf+l->pos,l->buf+l->pos+1,l->len-l->pos-1);
        l->len--;
        l->buf[l->len] = '\0';
        refreshLine(session);
    }
}

/* Backspace implementation. */
static void linenoiseEditBackspace(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    if (l->pos > 0 && l->len > 0) {
        memmove(l->buf+l->pos-1,l->buf+l->pos,l->len-l->pos);
        l->pos--;
        l->len--;
        l->buf[l->len] = '\0';
        refreshLine(session);
    }
}

/* Delete the previosu word, maintaining the cursor at the start of the
 * current word. */
static void linenoiseEditDeletePrevWord(linenoiseSession *session) {
    struct linenoiseState *l = &session->state;
    size_t old_pos = l->pos;
    size_t diff;

    while (l->pos > 0 && l->buf[l->pos-1] == ' ')
        l->pos--;
    while (l->pos > 0 && l->buf[l->pos-1] != ' ')
        l->pos--;
    diff = old_pos - l->pos;
    memmove(l->buf+l->pos,l->buf+old_pos,l->len-old_pos+1);
    l->len -= diff;
    refreshLine(session);
}

static int linenoiseReadChar(linenoiseSession *session, char *c)
{
    int n;

    do {
        if (session->read_ahead_buf)
        {
            *c = session->read_ahead_buf[session->read_ahead_pos++];
            lndebug("read char from buf %d(%c)\n", *c, *c);
            if (*c)
                return 1;
            bcm_linenoise_free(session->read_ahead_buf);
            session->read_ahead_buf = NULL;
            /* Fall through */
        }
        n = session->io.read_char(session->io.fd_in, c);
    } while (!n || (n == 1 && ! *c));
    lndebug("read char from io %d(%c) n=%d\n", *c, *c, n);
    return n;
}

static int linenoiseHandleEscSequence(linenoiseSession *session)
{
    struct linenoiseState *l = &session->state;
    char seq[32];

    /* Read the next two bytes representing the escape sequence.
     * Use two calls to handle slow terminals returning the two
     * chars at different times. */
    if (linenoiseReadChar(session, seq) == -1) return -1;
    if (linenoiseReadChar(session, seq+1) == -1) return -1;
    lndebug("seq=%02x(%c) seq1=%02x(%c)\n", seq[0], seq[0], seq[1], seq[1]);

    /* ESC [ sequences. */
    if (seq[0] == '[') {
        if (seq[1] >= '0' && seq[1] <= '9') {
            int n = 2;
            char terminator = 0;

            /* Extended escape, read additional byte(s) */
            while (linenoiseReadChar(session, seq+n) != -1 && n < sizeof(seq) - 1)
            {
                terminator = seq[n++];
                if ( !(terminator >= '0' && terminator <= '9') && terminator != ';')
                    break;
            }
            seq[n] = 0;
            switch (terminator ) {
                case '~':
                    linenoiseEditDelete(session);
                    break;
                case 'R':
                {
                    int row, col;
                    /* Position report */
                    seq[n-1] = 0; /* Cut R */
                    sscanf(seq+1, "%d;%d", &row, &col);
                    l->cols = col;
                    session->ncolreqs = 0;
                    lndebug("position report row=%d col=%d\n", row, col);
                }
                default:
                    break;
            }
        } else {
            switch(seq[1]) {
            case 'A': /* Up */
                linenoiseEditHistoryNext(session, LINENOISE_HISTORY_PREV);
                break;
            case 'B': /* Down */
                linenoiseEditHistoryNext(session, LINENOISE_HISTORY_NEXT);
                break;
            case 'C': /* Right */
                linenoiseEditMoveRight(session);
                break;
            case 'D': /* Left */
                linenoiseEditMoveLeft(session);
                break;
            case 'H': /* Home */
                linenoiseEditMoveHome(session);
                break;
            case 'F': /* End*/
                linenoiseEditMoveEnd(session);
                break;
            default:
                break;
            }
        }
    }

    /* ESC O sequences. */
    else if (seq[0] == 'O') {
        switch(seq[1]) {
        case 'H': /* Home */
            linenoiseEditMoveHome(session);
            break;
        case 'F': /* End*/
            linenoiseEditMoveEnd(session);
            break;
        default:
            break;
        }
    }
    return 0;
}

/* This function is the core of the line editing capability of linenoise.
 * It expects 'fd' to be already in "raw mode" so that every key pressed
 * will be returned ASAP to read().
 *
 * The resulting string is put into 'buf' when the user type enter, or
 * when ctrl+d is typed.
 *
 * The function returns the length of the current buffer. */
static int linenoiseEdit(linenoiseSession *session, char *buf, size_t buflen, const char *prompt)
{
    struct linenoiseState *l = &session->state;
    int nread = 0;

    /* Populate the linenoise state that we pass to functions implementing
     * specific editing functionalities. */
    l->buf = buf;
    l->buflen = buflen;
    l->prompt = prompt;
    l->plen = strlen(prompt);
    l->oldpos = l->pos = 0;
    l->len = 0;
    if (!l->cols)
        l->cols = 80;
    getColumnsRequest(session);
    l->maxrows = 0;
    l->history_index = 0;

    /* Buffer starts empty. */
    l->buf[0] = '\0';
    l->buflen--; /* Make sure there is always space for the nulterm */

    /* The latest history entry is always our current buffer, that
     * initially is just an empty string. */
    linenoiseHistoryAdd(session, "");
    if (l->plen && session->io.write(session->io.fd_out, prompt, l->plen) == -1) return -1;
    while(1) {
        char c;

        nread = linenoiseReadChar(session, &c);
        if (nread <= 0) goto edit_out;

        lndebug("c=%02x(%c)\n", c, c);
        /* Only autocomplete when the callback is set. It returns < 0 when
         * there was an error reading from fd. Otherwise it will return the
         * character that should be handled next. */
        if (c == KEY_TAB && session->completionCallback != NULL) {
            completeLine(session);
            continue;
        }

        switch(c) {
        case KEY_CR:    /* enter */
        case KEY_LF:    /* enter */
            session->history_len--;
            bcm_linenoise_free(session->history[session->history_len]);
            goto edit_out;
        case CTRL_C:     /* ctrl-c */
            return -1;
        case BACKSPACE:   /* backspace */
        case 8:     /* ctrl-h */
            linenoiseEditBackspace(session);
            break;
        case CTRL_D:     /* ctrl-d, remove char at right of cursor, or of the
                       line is empty, act as end-of-file. */
            if (l->len > 0) {
                linenoiseEditDelete(session);
            } else {
                session->history_len--;
                bcm_linenoise_free(session->history[session->history_len]);
                return -1;
            }
            break;
        case CTRL_T:    /* ctrl-t, swaps current character with previous. */
            if (l->pos > 0 && l->pos < l->len) {
                int aux = buf[l->pos-1];
                buf[l->pos-1] = buf[l->pos];
                buf[l->pos] = aux;
                if (l->pos != l->len-1) l->pos++;
                refreshLine(session);
            }
            break;
        case CTRL_B:     /* ctrl-b */
            linenoiseEditMoveLeft(session);
            break;
        case CTRL_F:     /* ctrl-f */
            linenoiseEditMoveRight(session);
            break;
        case CTRL_P:    /* ctrl-p */
            linenoiseEditHistoryNext(session, LINENOISE_HISTORY_PREV);
            break;
        case CTRL_N:    /* ctrl-n */
            linenoiseEditHistoryNext(session, LINENOISE_HISTORY_NEXT);
            break;
        case ESC:    /* escape sequence */
            linenoiseHandleEscSequence(session);
            break;
        default:
            if (linenoiseEditInsert(session,c))
            {
                lndebug("editInsert failed\n");
                return -1;
            };
            break;
        case CTRL_U: /* Ctrl+u, delete the whole line. */
            buf[0] = '\0';
            l->pos = l->len = 0;
            refreshLine(session);
            break;
        case CTRL_K: /* Ctrl+k, delete from current to end of line. */
            buf[l->pos] = '\0';
            l->len = l->pos;
            refreshLine(session);
            break;
        case CTRL_A: /* Ctrl+a, go to the start of the line */
            linenoiseEditMoveHome(session);
            break;
        case CTRL_E: /* ctrl+e, go to the end of the line */
            linenoiseEditMoveEnd(session);
            break;
        case CTRL_L: /* ctrl+l, clear screen */
            linenoiseClearScreen(session);
            refreshLine(session);
            break;
        case CTRL_W: /* ctrl+w, delete previous word */
            linenoiseEditDeletePrevWord(session);
            break;
        }
    }
edit_out:
    lndebug(" - out. len=%d buf=<%s>\n", l->len, buf);
    return (nread >= 0) ? l->len : -1;
}

/* Get without editing */
static int linenoiseNoedit(linenoiseSession *session, char *buf, size_t buflen) {
    char c;
    int len = 0;
    int switch_to_smart_mode = 0;
    int nread = 0;
#ifndef LINENOISE_DISABLE_TERMIOS
    int atty_term = isatty(STDIN_FILENO);
#else
    int atty_term = 1;
#endif

    while ((nread = linenoiseReadChar(session, &c)) != -1 && len < buflen - 1)
    {
        if (c == '\n' || c == '\r')
            break;
        buf[len++] = c;
        /* If buffer contains ESC sequence - perhaps the terminal is not dumb after all */
        if (c == ESC && !session->io.dumb_terminal && !session->forced_dumb && atty_term)
        {
            switch_to_smart_mode = 1;
            break;
        }
        /* Echo here is terminal is in raw mode */
        if (session->rawmode)
        {
            session->io.write(session->io.fd_out, &c, 1);
        }
    }
    buf[len] = 0;
    if (switch_to_smart_mode)
    {
        /* Copy buffer into read-ahead buffer and re-parse */
        lndebug("switching to smart mode\n");
        /* If there already is read_ahead buf - realloc it */
        if (session->read_ahead_buf)
        {
            char *new_buf;
            new_buf = bcm_linenoise_alloc(session, strlen(session->read_ahead_buf) - session->read_ahead_pos + len + 1);
            if (!new_buf)
                return -1;
            memcpy(new_buf, buf, len);
            strcpy(&new_buf[len], &session->read_ahead_buf[session->read_ahead_pos]);
            bcm_linenoise_free(session->read_ahead_buf);
            session->read_ahead_buf = new_buf;
        }
        else
        {
            session->read_ahead_buf = bcm_linenoise_alloc(session, len + 1);
            if (!session->read_ahead_buf)
                return -1;
            strcpy(session->read_ahead_buf, buf);
        }
        session->read_ahead_pos = 0;
        session->dumb_terminal = 0;
        session->ncolreqs = 0;
        *buf = 0;
        nread = linenoiseEdit(session, buf, buflen, "");
    }
    lndebug(" - out. len=%d buf=<%s> nread=%d\n", (int)strlen(buf), buf, nread);
    return (nread >=0) ? strlen(buf) : -1;
}


/* This function calls the line editing function linenoiseEdit() using
 * the STDIN file descriptor set in raw mode. */
static int linenoiseRaw(linenoiseSession *session, char *buf, size_t buflen, const char *prompt) {
    int rc = 0;

    lndebug("\n");
#ifndef LINENOISE_DISABLE_TERMIOS
    if (!isatty(STDIN_FILENO)) {
        /* Not a tty: read from file / pipe. */
	rc = linenoiseNoedit(session, buf, buflen);
	if (rc >= 0)
	    session->io.write(session->io.fd_out, "\n", 1);
    }
    else
#endif
    {
        /* Interactive editing. */
        if (enableRawMode(session) == -1) return -1;

        if (!session->dumb_terminal && session->ncolreqs > 1)
        {
            session->dumb_terminal = 1;
            lndebug("dumb_terminal=%d\n", session->dumb_terminal);
        }
        if (session->dumb_terminal) {
            session->io.write(session->io.fd_out, prompt, strlen(prompt));
            rc = linenoiseNoedit(session, buf, buflen);
        } else {
            rc = linenoiseEdit(session, buf, buflen, prompt);
        }

        disableRawMode(session);
        if (rc >= 0)
            session->io.write(session->io.fd_out, "\n", 1);
    }
    lndebug(" - out. len=%d buf=<%s> rc=%d\n", (int)strlen(buf), buf, rc);
    return rc;
}

/* The high level function that is the main API of the linenoise library.
 * This function checks if the terminal has basic capabilities, just checking
 * for a blacklist of stupid terminals, and later either calls the line
 * editing function or uses dummy fgets() so that you will be able to type
 * something even in the most desperate of the conditions. */
char *linenoise(linenoiseSession *session, const char *prompt, char *buf, size_t size) {

    if (size == 0) {
        errno = EINVAL;
        return NULL;
    }

    /* Configure terminal as dumb if it doesn't support basic ESC sequences */
    if (session->io.dumb_terminal || session->forced_dumb) {
        int rc;

        session->io.write(session->io.fd_out, prompt, strlen(prompt));
        rc = linenoiseNoedit(session, buf, size);
        session->io.write(session->io.fd_out, "\n", 1);
        lndebug(" - out. len=%d buf=<%s>\n", (int)strlen(buf), buf);
        return (rc == -1) ? NULL : buf;
    } else {
        if (linenoiseRaw(session, buf, size, prompt) == -1) return NULL;
        lndebug(" - out. len=%d buf=<%s>\n", (int)strlen(buf), buf);
        return buf;
    }
}

/* ================================ History ================================= */

/* Free the history, but does not reset it. Only used when we have to
 * exit() to avoid memory leaks are reported by valgrind & co. */
static void freeHistory(linenoiseSession *session) {
    if (session->history) {
        int j;

        for (j = 0; j < session->history_len; j++)
            bcm_linenoise_free(session->history[j]);
        bcm_linenoise_free(session->history);
        session->history = NULL;
    }
}

/* This is the API call to add a new entry in the linenoise history.
 * It uses a fixed array of char pointers that are shifted (memmoved)
 * when the history max length is reached in order to remove the older
 * entry and make room for the new one, so it is not exactly suitable for huge
 * histories, but will work well for a few hundred of entries.
 *
 * Using a circular buffer is smarter, but a bit more complex to handle. */
int linenoiseHistoryAdd(linenoiseSession *session, const char *line) {
    char *linecopy;

    if (session->history_max_len == 0) return 0;

    /* Initialization on first call. */
    if (session->history == NULL) {
        session->history = bcm_linenoise_alloc(session, sizeof(char*)*session->history_max_len);
        if (session->history == NULL) return 0;
        memset(session->history,0,(sizeof(char*)*session->history_max_len));
    }

    /* Don't add duplicated lines. */
    if (session->history_len && !strcmp(session->history[session->history_len-1], line)) return 0;

    /* Add an heap allocated copy of the line in the history.
     * If we reached the max length, remove the older line. */
    linecopy = linenoise_strdup(session, line);
    if (!linecopy) return 0;
    if (session->history_len == session->history_max_len) {
        bcm_linenoise_free(session->history[0]);
        memmove(session->history,session->history+1,sizeof(char*)*(session->history_max_len-1));
        session->history_len--;
    }
    session->history[session->history_len] = linecopy;
    session->history_len++;
    return 1;
}

/* Set the maximum length for the history. This function can be called even
 * if there is already some history, the function will make sure to retain
 * just the latest 'len' elements if the new history length value is smaller
 * than the amount of items already inside the history. */
int linenoiseHistorySetMaxLen(linenoiseSession *session, int len) {
    char **new;

    if (len < 1) return 0;
    if (session->history) {
        int tocopy = session->history_len;

        new = bcm_linenoise_alloc(session, sizeof(char*)*len);
        if (new == NULL) return 0;

        /* If we can't copy everything, free the elements we'll not use. */
        if (len < tocopy) {
            int j;

            for (j = 0; j < tocopy-len; j++) bcm_linenoise_free(session->history[j]);
            tocopy = len;
        }
        memset(new,0,sizeof(char*)*len);
        memcpy(new,session->history+(session->history_len-tocopy), sizeof(char*)*tocopy);
        bcm_linenoise_free(session->history);
        session->history = new;
    }
    session->history_max_len = len;
    if (session->history_len > session->history_max_len)
        session->history_len = session->history_max_len;
    return 1;
}

int linenoiseSetRaw(linenoiseSession *session, int raw)
{
    int rc = 0;
    if (raw)
        rc = enableRawMode(session);
    else
        disableRawMode(session);
    return rc;
}

int linenoiseGetRaw(linenoiseSession *session)
{
    return session->rawmode;
}

#ifndef LINENOISE_DISABLE_HIST_SAVE

/* Save the history in the specified file. On success 0 is returned
 * otherwise -1 is returned. */
int linenoiseHistorySave(linenoiseSession *session, const char *filename) {
    FILE *fp = fopen(filename,"w");
    int j;

    if (fp == NULL) return -1;
    for (j = 0; j < session->history_len; j++)
        fprintf(fp,"%s\n",session->history[j]);
    fclose(fp);
    return 0;
}

/* Load the history from the specified file. If the file does not exist
 * zero is returned and no operation is performed.
 *
 * If the file exists and the operation succeeded 0 is returned, otherwise
 * on error -1 is returned. */
int linenoiseHistoryLoad(linenoiseSession *session, const char *filename) {
    FILE *fp = fopen(filename,"r");
    char *buf;

    if (fp == NULL) return -1;
    buf = bcm_linenoise_alloc(session, LINENOISE_MAX_LINE);
    if (!buf)
    {
        fclose(fp);
        return -1;
    }

    while (fgets(buf,LINENOISE_MAX_LINE,fp) != NULL) {
        char *p;

        p = strchr(buf,'\r');
        if (!p) p = strchr(buf,'\n');
        if (p) *p = '\0';
        linenoiseHistoryAdd(session, buf);
    }
    fclose(fp);
    bcm_linenoise_free(buf);
    return 0;
}

#endif
