#include <iocslib.h>
#include "keyboard.h"
#include "key.h"
#include "protocol.h"
#include "io.h"
#include "screen.h"

unsigned char ch;

void keyboard_out(int platoKey)
{
  if (platoKey==0xff)
    {
      return;
    }
  
  if (platoKey>0x7F)
    {
      Key(ACCESS);
      Key(ACCESS_KEYS[platoKey-0x80]);
      return;
    }
  Key(platoKey);
  return;
}

void keyboard_main(void)
{
  padByte ch[1];
  padByte sc[1];
  int inp;
  int modifier=_iocs_b_sftsns();
  if (_iocs_b_keysns())
    {
      inp=_iocs_b_keyinp();
      ch[0] = inp&0xFF;
      sc[0] = inp>>8;
      if (TTY)
      	{
	  if ((sc[0]==0x02) && (modifier & 2))
	    io_set_baud(1200);
	  else if ((sc[0]==0x03) && (modifier & 2))
	    io_set_baud(2400);
	  else if ((sc[0]==0x04) && (modifier & 2))
	    io_set_baud(300);
	  else if ((sc[0]==0x07) && (modifier & 2))
	    io_set_baud(9600);
	  else if ((sc[0]==0x09) && (modifier & 2))
	    io_set_baud(38400);
	  else if ((sc[0]==0x0a) && (modifier & 2))
	    io_set_baud(19200);
	  else
	    keyboard_out_tty(ch[0]);
      	}
      else
      	{
	  if ((ch[0]==0x0d) && (modifier & 1))
	    keyboard_out(PKEY_NEXT1);
	  else if ((sc[0]==0x54) && (modifier & 1))
	    keyboard_out(PKEY_HELP1);
	  else if ((sc[0]==0x54))
	    keyboard_out(PKEY_HELP);
	  else if ((sc[0]==0x0f) && (modifier & 1))
	    keyboard_out(PKEY_ERASE1);
	  else if ((sc[0]==0x62) && (modifier & 1))
	    keyboard_out(PKEY_COPY1);
	  else if ((sc[0]==0x62))
	    keyboard_out(PKEY_COPY);
	  else if ((sc[0]==0x0F))
	    keyboard_out(PKEY_ERASE);
	  else if (modifier & 2) /* CTRL pressed */
	    {
	      if (modifier & 1)
		ch[0]|=0x80;
	      keyboard_out(ctrl_key_to_pkey[ch[0]]);
	    }
	  else
	    keyboard_out(key_to_pkey[(ch[0])]);
      	}
    }
}

void keyboard_clear(void)
{
}

void keyboard_out_tty(int ch)
{
  io_send_byte(ch);
}
