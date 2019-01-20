#include "protocol.h"
#include "screen.h"
#include "io.h"
#include "terminal.h"
#include "keyboard.h"
#include "splash.h"

#define true 1
#define false 0

unsigned char already_started=false;

void main(void)
{
  screen_init();
  ShowPLATO(splash,sizeof(splash));
  terminal_initial_position();
  io_init();
  for (;;)
    {
      keyboard_main();
      io_main();
    }
}
