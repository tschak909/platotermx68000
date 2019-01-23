#include <iocslib.h>
#include <mouse.h>
#include "touch.h"
#include "screen.h"

#define X(x) (x)
#define Y(y) (y^0x1FF)

padBool lmb=padF;
padBool lastlmb=padF; /* left mouse button state */
padBool isAllowed;

/**
 * touch_init(void)
 * Initiialize mouse
 */
void touch_init(void)
{
  _iocs_ms_init();
  _iocs_ms_curof();
}

/**
 * enable/disable mouse cursor
 */
void touch_allow(padBool allow)
{
  isAllowed=allow;
  if (allow==padT)
    _iocs_ms_curon();
  else
    _iocs_ms_curof();
}

padBool touch_lmb(void)
{
  if (_iocs_ms_getdt()&0xFF00)
    return padT;
  else
    return padF;
}

void touch_main(void)
{
  int x,y;
  padPt coord;
  
  if (isAllowed==padF)
    return;

  lmb=touch_lmb();
  if (lmb==padT)
    {
      if (lmb!=lastlmb)
	{
	  mspos(&x,&y);
	  coord.x=X(x);
	  coord.y=Y(y);
	  Touch(&coord);
	}
    }
  lastlmb=lmb;
}

/**
 * touch done
 */
void touch_done(void)
{
  _iocs_ms_curof();
}
