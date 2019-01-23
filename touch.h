#ifndef TOUCH_H
#define TOUCH_H

#include "protocol.h"

/**
 * touch_init(void)
 * Initiialize mouse
 */
void touch_init(void);

/**
 * enable/disable mouse cursor
 */
void touch_allow(padBool allow);

/**
 * Is left mouse button pressed?
 */
padBool touch_lmb(void);

/**
 * Get mouse position, and if LMB pressed, send touch event.
 */
void touch_main(void);

/**
 * touch done
 */
void touch_done(void);


#endif /* TOUCH_H */
