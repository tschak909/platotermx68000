/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * io.h - Input/output functions (serial/ethernet)
 */

#ifndef IO_H
#define IO_H

#define XON  0x11
#define XOFF 0x13

/**
 * io_init() - Set-up the I/O
 */
void io_init(void);

/**
 * io_send_byte(b) - Send specified byte out
 */
void io_send_byte(unsigned char b);

/**
 * io_send_string(str,len)
 * Send string to port.
 */
void io_send_string(const char* str, int len);

/**
 * io_main() - The IO main loop
 */
void io_main(void);

/**
 * io_set_baud(int baud) - Set baud rate
 */
void io_set_baud(int baud);

/**
 * io_hang_up(void) - Hang up modem
 */
void io_hang_up(void);

/**
 * io_send_cr(void)
 */
void io_send_cr(void);

/**
 * io_send_dial(void) - send dial string
 */
void io_send_dial(void);

/**
 * io_send_back_out(void) - send back out
 */
void io_send_back_out(void);

/**
 * io_done() - Called to close I/O
 */
void io_done(void);

#endif /* IO_H */
