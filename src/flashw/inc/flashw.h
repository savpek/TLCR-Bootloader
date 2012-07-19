/*
 * flashw.h
 *
 * Created: 24.11.2011 12:19:50
 *  Author: savpek
 */ 


#ifndef FLASHW_H_
#define FLASHW_H_

/* ASF */
#include "compiler.h"
#include "flashcdw.h"

/* TLCR lib */
#include "./error_handler/inc/errorh.h"
#include "./ihex/inc/ihex.h"

/* This writes ihex_row data to MCU flash. This function collects enough
 * (doudble word x 32) of data before it begins write it to memory. Actual
 * data count doesn't matter however, true trigger to begin memory writing is
 * target address. */
extern errorc_t flashw_write_routine(ihex_row_t *ihex_row);

/* This dumps rest of data from buffer to flash memory. */
extern errorc_t flashw_write_dump( void );

#endif /* FLASHW_H_ */