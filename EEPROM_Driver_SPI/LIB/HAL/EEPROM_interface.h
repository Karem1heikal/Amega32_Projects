/*
 * EEPROM_interface.h
 *
 *  Created on: Jul 8, 2024
 *      Author: user
 */

#ifndef HAL_EEPROM_INTERFACE_H_
#define HAL_EEPROM_INTERFACE_H_

u8 EEPROM_u8SendMemByte(u8 Copy_u8Data,u16 Copy_u16Address);

u8 EEPROM_u8ReadMemByte(u8* Copy_pu8Read,u16 Copy_u16Address);


#endif /* HAL_EEPROM_INTERFACE_H_ */
