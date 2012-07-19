/*
 * terminal.h
 *
 * Created: 18.11.2011 12:46:30
 *  Author: savpek
 */ 


#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "compiler.h"
#include "./error_handler/inc/errorh.h"

/* This gets byte value of 2 received chars, for example
 * characters E and 1 returns byte value 0xE1. Echoes received data. */
extern errorc_t strchr_get_byte( uint8_t *ret_byte );

#endif /* TERMINAL_H_ */