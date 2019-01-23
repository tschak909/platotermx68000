#include "io.h"
#include "protocol.h"
#include "config.h"

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
  /* int len,i; */

  /* len=0; */
  
  /* while (_iocs_isns232c()!=0) */
  /*   { */
  /*     buf[len++]=_iocs_inp232c(); */
  /*   } */

  /* if (len>0) */
  /*   { */
  /*     ShowPLATO(&buf,len); */
  /*     len=0; */
  /*   } */
  
  if (_iocs_isns232c())
    {
      buf[0]=_iocs_inp232c();
      ShowPLATO(&buf,1);
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

void io_done()
{
}
