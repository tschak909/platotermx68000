/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * trace.c - Trace output functions.
 */

#include <string.h>
#include "protocol.h"

#define true 1
#define false 0

#define TRACE_FILE "trace.txt"

unsigned char trace_active=false;

static int trace_handle;

/**
 * trace_open(void)
 * Open trace file trace.txt
 */
void trace_open(void)
{
  char c[20];

  if (trace_active==true)
    return;

  trace_handle = _dos_create(TRACE_FILE,0);
  if (trace_handle>0)
    trace_active=true;

  sprintf(c,"padByte trace[]={\n");
  _dos_write(trace_handle,c,strlen(c));
}

/**
 * trace_append(buf, len)
 * Append data from ShowPLATO into buffer
 */
void trace_append(padByte* buf, int len)
{
  int i;
  char c[8];
  if (trace_active==false)
    return;

  for (i=0;i<len;i++)
    {
      sprintf(c,"0x%02x,\n",buf[i]);
      _dos_write(trace_handle,c,6);
    }
}

/**
 * trace_close(void)
 * Close trace file.
 */
void trace_close(void)
{
  char c[4];

  if (trace_active==false)
    return;
  
  sprintf(c,"};\n");
  _dos_write(trace_handle,c,3);
}

/**
 * trace_toggle(void)
 * Toggle trace on/off
 */
void trace_toggle(void)
{
  if (trace_active==true)
    trace_close();
  else
    trace_open();

  switch(trace_active)
    {
    case true:
      screen_trace_status("ON");
      break;
    case false:
      screen_trace_status("OFF");
      break;
    }
}
