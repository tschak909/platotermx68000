/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * config.c - Config file functions
 */

#include <doslib.h>
#include <string.h>
#include "config.h"

ConfigInfo config;

/**
 * config_init(void)
 * load config into config variable, create if needed.
 */
void config_init(void)
{
  config_load();
}

/**
 * config_load(void)
 * Load config into config variable.
 */
void config_load(void)
{
  int handle;
  
  handle=_dos_open(CONFIG_FILE,0);

  if (handle<0)
    {
      config_set_defaults();
    }
  else
    {
      _dos_read(handle,(char *)&config,sizeof(ConfigInfo));
    }

  _dos_close(handle);
  
}

/**
 * config_set_defaults(void)
 * Set default configuration
 */
void config_set_defaults(void)
{
  config.baud=19200;
  strcpy(config.init_string,"ATZ");
  strcpy(config.dial_string,"ATDTIRATA.ONLINE:8005");
  config_save();
}

/**
 * config_save(void)
 * Save config in config variable to config file.
 */
void config_save(void)
{
  int handle;
  handle=_dos_open(CONFIG_FILE,2);

  if (handle<0)
    {
      handle=_dos_create(CONFIG_FILE,0);
      if (handle<0)
	return;
    }

  _dos_write(handle,(char *)&config,sizeof(ConfigInfo));

  _dos_close(handle);
}

