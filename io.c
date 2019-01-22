#include "io.h"
#include "protocol.h"

void io_init(void)
{
  _iocs_set232c(0x4C08);
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

void io_done()
{
}
