/*
 * ihex.h
 *
 * Created: 18.11.2011 11:44:12
 *  Author: savpek
 */ 


#ifndef IHEX_H_
#define IHEX_H_

#include "compiler.h"
#include "./error_handler/config/error_codes.h"

#define IHEX_RTYPE_DATA 0x00
#define IHEX_RTYPE_END 0x01

/*  Ihex format contains:
	: 10 0100 00 214601360121470136007EFE09D21901 40
	S BC ADDR RT DATA                             CSUM
	Where:
	S: Start code ":",
	BC: Byte Count,
	ADDR: Memory addres,
	RT: Record type (00 or 01),
	  -00: Data
	  -01: End
	DATA: Well, data...
	CSUM: Checksum of BC, ADDR, RT and DATA. */ 
typedef struct {
	/* This contains amount of databytes in current
	 * page of data. */
	uint8_t byte_count;
	
	/* Data type, can be 00 or 01 in Ihex8 format */
	uint8_t record_type;
	
	uint16_t addr;
	
	uint8_t data_index;
	uint8_t data[16];
	
	/* This is 2 complement from sum of: BC, ADDR, RT, DATA fiels. */ 
	uint8_t checksum;
} ihex_row_t;

extern errorc_t ihex_checksum ( ihex_row_t *ihex_data_struct );

#endif /* IHEX_H_ */