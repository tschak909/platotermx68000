/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * config.h - Config file functions
 */

#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_FILE "plato.cfg"

typedef struct _configInfo {
  int baud;
  int rtscts;
  char init_string[128];
  char dial_string[128];
} ConfigInfo;

/**
 * config_init(void)
 * load config into config variable, create if needed.
 */
void config_init(void);

/**
 * config_load(void)
 * Load config into config variable.
 */
void config_load(void);

/**
 * config_set_defaults(void)
 * Set default configuration
 */
void config_set_defaults(void);

/**
 * config_save(void)
 * Save config in config variable to config file.
 */
void config_save(void);

#endif /* CONFIG_H */
