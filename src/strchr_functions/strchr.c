/*
 * terminal_get_functions.c
 *
 * Created: 18.11.2011 13:07:59
 *  Author: savpek
 */ 

#include "compiler.h"
#include "./error_handler/inc/errorh.h"
#include "./usart/inc/usart_wb.h"

static errorc_t get_hex_from_char (uint8_t character, uint8_t *ret_value )
	{
	/* We must find that is character between 48(0)-57(9), or is it letter
	 * 65(A)-70(F). First we check that is it an number: */
	if ( 48 <= character && 
		 57 >= character )
		{
		*ret_value = character-48;
		return EC_TRUE;
		}
		
	/* Then check is value between A-F range. */
	if ( 65 <= character && 
		 70 >= character )
		{
		*ret_value = (character-65+10);
		return EC_TRUE;
		}
	
	/* This happens if given character isn't correct character for hex value */	
	return EC_FALSE;
	}

/* This gets byte value of 2 received chars, for example
 * characters E and 1 returns byte value 0xE1. Echoes received data. */
extern errorc_t strchr_get_byte( uint8_t *ret_byte )
	{
	uint8_t char_temp = 0;
	uint8_t char_value_temp = 0;
	uint8_t return_value_temp = 0;
	
	/* First we look for high value of byte (first char). */
	char_temp = usart_getchar();
	
	#ifdef DEBUG_MODE
	usart_putchar(char_temp);
	#endif
	
	if (EC_FALSE == get_hex_from_char(char_temp, &char_value_temp))
		{
		return EC_FALSE;
		}
	
	/* First character counts as first 4 bits from HEX value */
	return_value_temp = (char_value_temp<<4);

	char_temp = usart_getchar();

	#ifdef DEBUG_MODE
	usart_putchar(char_temp);
	#endif
	
	if (EC_FALSE == get_hex_from_char(char_temp, &char_value_temp))
		{
		return EC_FALSE;
		}
	
	/* Second character counts as last 4 bits. */	
	return_value_temp |= (char_value_temp);
	
	*ret_byte = return_value_temp;
	
	/* Exit function with EC_SUCCES code. */
	return EC_TRUE; 
	}
