#include "io.h"
#include "protocol.h"

void io_init(void)
{
  _iocs_set232c(0x4c10);
}

void io_send_byte(unsigned char b)
{
  _iocs_out232c(b);
}

void io_main(void)
{
  padByte buf[8192];
  int len,i;
  if (_iocs_isns232c())
    {
      buf[0]=_iocs_inp232c();
      ShowPLATO(&buf,1);
    }
}

void io_done()
{
}
