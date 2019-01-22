#include <iocslib.h>
#include "touch.h"

/**
 * enable/disable mouse cursor
 */
void touch_allow(padBool allow)
{
  if (allow==padT)
    _iocs_ms_curon();
  else
    _iocs_ms_curof();
}
