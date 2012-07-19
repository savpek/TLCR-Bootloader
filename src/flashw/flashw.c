/*
 * flashw.c
 *
 * Created: 24.11.2011 13:02:35
 *  Author: savpek
 */ 

#include "compiler.h"
#include "flashcdw.h"

#include "./error_handler/inc/errorh.h"
#include "./flashw/config/flashw_settings.h"
#include "./ihex/inc/ihex.h"

typedef struct {
	uint32_t last_written_addr;
	uint32_t current_addr;
	uint8_t  page[AVR32_FLASHCDW_PAGE_SIZE];
} flashw_t;

static flashw_t flashw_buffer =
	{
	/* Initial values must be 0xff... because it is used
	 * to regonice that they haven't been set yet. */
	.last_written_addr = 0xFFFFFFFF,
	.current_addr = 0xFFFFFFFF,
	};

static uint8_t testdata[3] = {0, 1, 2};

static errorc_t write_data_to_flash ()
	{	
	/* Last argument is: erase before write = true. */
	*flashcdw_memcpy((volatile void*)(flashw_buffer.last_written_addr), (const void *)&flashw_buffer.page, AVR32_FLASHCDW_PAGE_SIZE, 1);
	
	/* We will write memory, next time page write will begin in current address. */
	flashw_buffer.last_written_addr = flashw_buffer.current_addr;
	
	/* Check for errors if any. */
	if(   0 != flashcdw_is_programming_error()
	   || 0 != flashcdw_is_lock_error() )
		{
		return EC_FAILURE;
		}
	else
		{
		return EC_SUCCESS;	
		}
	}

static uint32_t get_addr_diff()
	{
	return flashw_buffer.current_addr - flashw_buffer.last_written_addr;
	}

/* This writes ihex_row data to MCU flash. This function collects enough
 * (doudble word x 32) of data before it begins write it to memory. */
errorc_t flashw_write_routine(ihex_row_t *ihex_row)
	{
	/* When write function called first time, we should set location where 
	 * writing begins correctly. 0xFFF... is initial (not written) value. */
	if (0xFFFFFFFF == flashw_buffer.last_written_addr)
		{
		flashw_buffer.last_written_addr = FLASHW_BEGIN_OFFSET + ihex_row->addr;
		}
		
	/* On ihex format, theres addr on the frame. Address isn't absolute address, it is
	 * offset from defined write begin location. */
	flashw_buffer.current_addr = ihex_row->addr+FLASHW_BEGIN_OFFSET;
	
	uint8_t new_byte_counter = 0;
	while(new_byte_counter < ihex_row->byte_count)
		{
		/* If address buffer is full (eg. next addr that should be
		 * written is bigger than beginning of this page + page size).
		 * We write it. */
		if (AVR32_FLASHCDW_PAGE_SIZE <= get_addr_diff())
			{
			if (!write_data_to_flash()) return EC_FAILURE;
			}
		
		flashw_buffer.page[get_addr_diff()] = ihex_row->data[new_byte_counter];
		
		new_byte_counter++;
		flashw_buffer.current_addr++;	
		
		if(get_addr_diff() == 110)
			{
			asm("nop");
			}
		}
	
	return EC_SUCCESS;
	}

/* This dumps rest of data from buffer to flash memory. */
errorc_t flashw_write_dump( void )
	{
	
	}
