#include <doslib.h>
#include "io.h"
#include "protocol.h"
#include "config.h"
#include "terminal.h"

extern ConfigInfo config;

void io_init(void)
{
  io_set_baud(config.baud);
}

void io_send_byte(unsigned char b)
{
  _iocs_out232c(b);
}

void io_main(void)
{
  padByte buf[1];  
  if (_iocs_isns232c())
    {
      buf[0]=_iocs_inp232c();
      ShowPLATO(&buf,1);
    }
}

/**
 * io_send_string(str,len)
 * Send string to port.
 */
void io_send_string(const char* str, int len)
{
  int h;
  for (h=0;h<len;h++)
    {
      io_send_byte(str[h]);
    }
}

/**
 * io_set_baud(int baud) - Set baud rate
 */
void io_set_baud(int baud)
{
  int settings=0x4c00; /* Get old settings and mask off baud rate. */
  int new_baud;

  config.baud=baud;
  
  switch (baud)
    {
    case 300:
      new_baud=2;
      break;
    case 1200:
      new_baud=4;
      break;
    case 2400:
      new_baud=5;
      break;
    case 9600:
      new_baud=7;
      break;
    case 19200:
      new_baud=8;
      break;
    case 38400:
      new_baud=9;
      break;
    }

  settings|=new_baud;
  _iocs_set232c(settings);
  screen_show_baud_rate(baud);
  config_save();
}

/**
 * io_hang_up(void) - Hang up modem
 */
void io_hang_up(void)
{
  int i;
  screen_show_hang_up();
  terminal_set_tty();
  io_send_string("+++",3);
  for (i=0;i<600000;i++) {}
  io_send_string("ATH0\r\n",6);
}

void io_done()
{
}
