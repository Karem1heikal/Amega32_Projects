/*
 * EEPROM_config.h
 *
 *  Created on: Jul 8, 2024
 *      Author: user
 */

#ifndef HAL_EEPROM_CONFIG_H_
#define HAL_EEPROM_CONFIG_H_

#define EEPROM_08k	1
#define EEPROM_04k	2
#define EEPROM_02k	3

#define EEPROM_COMPONENT	EEPROM_08k

#define GND 	0
#define VCC		1

#if	EEPROM_COMPONENT == EEPROM_08k
#define A2 		GND
#elif EEPROM_COMPONENT == EEPROM_04k
#define A2 		GND
#define A1 		GND
#elif EEPROM_COMPONENT == EEPROM_02k
#define A2 		GND
#define A1 		GND
#define A0 		GND
#else
#error "Error in Choosing EEPROM component"
#endif

#define EEPROM_ADDRESS 0xA0

#endif /* HAL_EEPROM_CONFIG_H_ */
