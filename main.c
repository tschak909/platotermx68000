#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"
#include "touch.h"
#include "splash.h"
#include "config.h"

#define true 1
#define false 0

unsigned char already_started=false;
unsigned char running=false;
extern ConfigInfo config;

void main(void)
{
  config_init();
  screen_init();
  touch_init();
  ShowPLATO(splash,sizeof(splash));
  terminal_initial_position();
  io_init();
  running=true;
  while (running==true)
    {
      keyboard_main();
      io_main();
      touch_main();
    }
  io_done();
  touch_done();
  screen_done();
}
