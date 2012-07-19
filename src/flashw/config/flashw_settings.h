/*
 * FLASHW_BEGIN_OFFSET.h
 *
 * Created: 24.11.2011 17:05:27
 *  Author: savpek
 */ 


#ifndef FLASHW_SETTINGS_H_
#define FLASHW_SETTINGS_H_

/* This defines begin address of written data.
 * for example, if bootloader uses this (which uses 
 * 8kB bootsector) and flash memory begin from addr 
 * 0x008000, then this values should be set to
 * 0x80000000+0x1F40(8kB) = 0x80001F40. */
#define FLASHW_BEGIN_OFFSET  0x80005000


#endif /* FLASHW_BEGIN_OFFSET_H_ */