/*
 * ihex.c
 *
 * Created: 18.11.2011 12:17:13
 *  Author: savpek
 */ 

#include "compiler.h"
#include "./ihex/inc/ihex.h"
#include "./error_handler/inc/errorh.h"

errorc_t ihex_checksum( ihex_row_t *ihex_data_struct )
	{
	/* Checksum is calculated so that we sum all other bytes
	 * (byte count, addr, mode, data...) except first ":" mark
	 * and last byte, which is 2 complement of sum of rest. */
	
	/* First we sum all fields */
	uint8_t fields_sum = 0;
	
	fields_sum = ihex_data_struct->byte_count +
				 (ihex_data_struct->addr&0x00FF) +
				 (ihex_data_struct->addr>>8) +
				 ihex_data_struct->record_type;
	
	uint8_t field_counter = 0;			 
	while(field_counter < ihex_data_struct->byte_count)
		{
		fields_sum += ihex_data_struct->data[field_counter];
		field_counter++;	
		}
		
	/* Now we compare twos complement of fields_sum
	 * to checksum field. Twos complement can be done
	 * by subract fields_sum from value 0x100. */
	if (((0x100 - fields_sum)&0xFF) == ihex_data_struct->checksum)
		{
		return EC_TRUE;	
		}
	else
		{
		return EC_FALSE;
		}
	}