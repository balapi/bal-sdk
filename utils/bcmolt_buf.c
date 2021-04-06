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

#include "bcmolt_buf.h"
#include "bcmos_system.h"

/** Initalize a bcmolt_buf stream
 *
 * \param buf
 * \param size
 * \param start
 * \param endian Endianness of numbers in the resulting stream
 */
void bcmolt_buf_init(bcmolt_buf *buf, uint32_t size, uint8_t *start)
{
    buf->len = size;
    buf->curr = start;
    buf->start = start;
    memset(&buf->io, 0, sizeof(buf->io));
}

/** Initalize a bcmolt_buf file IO stream
 *
 * \param buf    bcmolt_buf instance
 * \param size   Total length of the buffer stream in bytes
 * \param io     IO callbacks
 */
void bcmolt_buf_init_io(bcmolt_buf *buf, uint32_t size, const bcmolt_buf_io *io)
{
    BUG_ON(io->read==NULL || io->write==NULL);
    buf->io = *io;
    buf->len = size;
    buf->curr = buf->start = NULL;
}

/** Set the length of a bcmolt_buf instance
 *
 * \param buf    bcmolt_buf instance
 * \param size   Total length of the buffer stream in bytes
 */
void bcmolt_buf_set_length(bcmolt_buf *buf, uint32_t size)
{
    buf->len = size;
}

/** Read from the buffer
 *
 * \param buf    bcmolt_buf instance
 * \param to     Where to read to
 * \param len    Number of bytes to copy
 *
 * \return       BCMOS_TRUE if successfully copied
 */
bcmos_bool bcmolt_buf_read(bcmolt_buf *buf, void *to, size_t len)
{
    if ((buf->start + buf->len) >= (buf->curr + len))
    {
        if (buf->io.read != NULL)
        {
            int io_result = buf->io.read(buf->io.handle, (unsigned long)buf->curr, to, len);
            if (io_result != len)
                return BCMOS_FALSE;
        }
        else
        {
            memcpy(to, buf->curr, len);
        }
        buf->curr += len;
        return BCMOS_TRUE;
    }

    return BCMOS_FALSE;
}

/** Transfer bytes from one buf to another
 *
 * \param *from    Source buffer
 * \param *to      Destination buffer
 * \param bytes    Number of bytes to transfer
 * \return         BCMOS_TRUE if successfully transferred
 */
bcmos_bool bcmolt_buf_transfer_bytes(bcmolt_buf *from, bcmolt_buf *to, uint32_t bytes)
{
    uint8_t tmp[256];
    uint32_t toRead;
    while (bytes != 0)
    {
        toRead = bytes > sizeof(tmp) ? sizeof(tmp) : bytes;
        if (!bcmolt_buf_read(from, tmp, toRead) || !bcmolt_buf_write(to, tmp, toRead))
        {
            return BCMOS_FALSE;
        }

        bytes -= toRead;
    }

    return BCMOS_TRUE;
}

/** Write to the buffer
 *
 * \param buf    bcmolt_buf instance
 * \param from   Source, to copy from
 * \param len    Number of bytes to copy
 *
 * \return       BCMOS_TRUE if successfully copied
 */
bcmos_bool bcmolt_buf_write(bcmolt_buf *buf, const void *from, size_t len)
{
    if ((buf->start + buf->len) >= (buf->curr + len))
    {
        if (buf->io.write != NULL)
        {
            int io_result = buf->io.write(buf->io.handle, (unsigned long)buf->curr, from, len);
            if (io_result != len)
                return BCMOS_FALSE;
        }
        else
        {
            memcpy(buf->curr, from, len);
        }
        buf->curr += len;
        return BCMOS_TRUE;
    }
    else
    {
        return BCMOS_FALSE;
    }
}

/** Move the current pointer to a given position in the buffer
 *
 * \param pos    Byte position in the buffer to move the current pointer to
 *
 * \param *buf   Input buffer
 * \return       BCMOS_FALSE if len takes us past the end of buffer
 */
bcmos_bool bcmolt_buf_set_pos(bcmolt_buf *buf, uint32_t pos)
{
    if (pos <= buf->len)
    {
        buf->curr = buf->start + pos;
        return BCMOS_TRUE;
    }

    return BCMOS_FALSE;
}

/** Move the current pointer ahead by given number of bytes
 *
 * \param buf    bcmolt_buf instance
 * \param len    Number of bytes to skip
 *
 * \return       BCMOS_FALSE if len takes us past the end of buffer
 */
bcmos_bool bcmolt_buf_skip(bcmolt_buf *buf, uint32_t len)
{
    if ((buf->start + buf->len) >= (buf->curr + len))
    {
        buf->curr += len;
        return BCMOS_TRUE;
    }

    return BCMOS_FALSE;
}

/** Move the current pointer back by given number of bytes
 *
 * \param buf    bcmolt_buf instance
 * \param len    Number of bytes to go back
 *
 * \return       BCMOS_FALSE if len takes us past the start of buffer
 */
bcmos_bool bcmolt_buf_rewind(bcmolt_buf *buf, uint32_t len)
{
    if (buf->curr >= (buf->start + len))
    {
        buf->curr -= len;
        return BCMOS_TRUE;
    }

    return BCMOS_FALSE;
}

/** Reads a boolean from a buffer
 *
 * \param *buf
 * \param *val
 */
bcmos_bool bcmolt_buf_read_bool(bcmolt_buf *buf, bcmos_bool *val)
{
    /* this function isn't inlined like the rest because it's too complex to inline cleanly */
    uint8_t tmp;
    if (bcmolt_buf_read_u8(buf, &tmp))
    {
        *val = (tmp != 0);
        return BCMOS_TRUE;
    }
    else
    {
        return BCMOS_FALSE;
    }
}


#ifdef __KERNEL__
EXPORT_SYMBOL(bcmolt_buf_init);
EXPORT_SYMBOL(bcmolt_buf_read);
EXPORT_SYMBOL(bcmolt_buf_transfer_bytes);
EXPORT_SYMBOL(bcmolt_buf_write);
EXPORT_SYMBOL(bcmolt_buf_set_pos);
EXPORT_SYMBOL(bcmolt_buf_skip);
EXPORT_SYMBOL(bcmolt_buf_rewind);
EXPORT_SYMBOL(bcmolt_buf_read_bool);

MODULE_LICENSE("Dual BSD/GPL");
#endif
