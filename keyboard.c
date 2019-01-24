#include <iocslib.h>
#include "keyboard.h"
#include "key.h"
#include "protocol.h"
#include "io.h"
#include "screen.h"
#include "trace.h"
#include "config.h"

#define true 1
#define false 0

extern unsigned char running;
extern unsigned char help_active;
extern char tmp[64];
extern ConfigInfo config;

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
      if (help_active)
	screen_show_help();
      else if (sc[0]==0x54)
	screen_show_help();
      if (sc[0]==0x61)
	io_hang_up();
      else if (sc[0]==0x63)
	terminal_set_tty();
      else if (sc[0]==0x64)
	terminal_set_plato();
      else if (sc[0]==0x65)
	trace_toggle();
      else if (sc[0]==0x6C)
	running=false;
      else if (TTY)
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
	  else if ((sc[0]==0x20) && (modifier & 1) && (modifier & 2))
	      keyboard_input_str("Dial String:",config.dial_string);
	  else if ((sc[0]==0x18) && (modifier & 1) && (modifier & 2))
	      keyboard_input_str("Init String:",config.init_string);
	  else if ((sc[0]==0x20) && (modifier & 2))
	    io_send_dial();
	  else if ((sc[0]==0x2e) && (modifier & 2))
	    io_send_back_out();	  
	  else
	    keyboard_out_tty(ch[0]);
      	}
      else
      	{
	  if ((ch[0]==0x0d) && (modifier & 1))
	    keyboard_out(PKEY_NEXT1);
	  else if ((sc[0]==0x0f) && (modifier & 1))
	    keyboard_out(PKEY_ERASE1);
	  else if ((sc[0]==0x62) && (modifier & 1))
	    keyboard_out(PKEY_COPY1);
	  else if ((sc[0]==0x62))
	    keyboard_out(PKEY_COPY);
	  else if ((sc[0]==0x0F))
	    keyboard_out(PKEY_ERASE);
	  else if ((sc[0]==0x30) && (modifier & 2))
	    keyboard_out(PKEY_MICRO);
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

/**
 * keyboard_input_str(prompt, str)
 * Input keyboard string with prompt in status bar
 */
void keyboard_input_str(char* prompt, char* str)
{
  char ch[2]={0x00,0x00};
  int len=strlen(str);
  char ptmp[64];
  
  strcpy(tmp,str);
  
  while ((ch[0] != 0x0d) && (ch[0] != 0x1B))
    {
      sprintf(ptmp,"%s %s",prompt,tmp);
      screen_show_status(ptmp);
      ch[0]=_iocs_b_keyinp()&0xFF;
      if (ch[0] == 0x08)
	{
	  if (len>0)
	    {
	      tmp[len-1]='\0';
	      len--;
	    }
	}
      else if ((ch[0] != 0x0d) && (ch[0] != 0x1B))
	{
	  strcat(tmp,ch);
	  len++;
	}
    }

  if (ch[0]==0x1B)
    {
      screen_show_status("Aborted.");
      return;
    }

  if (ch[0]==0x0d)
    {
      screen_show_status("Updated.");
      strcpy(str,tmp);
      config_save();
      return;
    }
}

void keyboard_out_tty(int ch)
{
  io_send_byte(ch);
}

