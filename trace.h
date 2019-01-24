#ifndef TRACE_H
#define TRACE_H

/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * trace.h - Trace output functions.
 */

/**
 * trace_open(void)
 * Open trace file trace.txt
 */
void trace_open(void);

/**
 * trace_append(buf, len)
 * Append data from ShowPLATO into buffer
 */
void trace_append(padByte* buf, int len);

/**
 * trace_close(void)
 * Close trace file.
 */
void trace_close(void);

#endif /* TRACE_H */
