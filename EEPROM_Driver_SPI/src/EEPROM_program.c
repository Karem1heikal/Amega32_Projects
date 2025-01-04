/*
 * EEPROM_program.c
 *
 *  Created on: Jul 8, 2024
 *      Author: user
 */

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/SPI_interface.h"
#include "../MCAL/DIO_interface.h"
#include "../HAL/EEPROM_config.h"
#include "../HAL/EEPROM_private.h"
#include "../HAL/EEPROM_interface.h"

// SPI EEPROM
u8 EEPROM_u8SendMemByte(u8 Copy_u8Data,u16 Copy_u16Address)
{
	u8 Local_intErrorState = OK;
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
	SPI_u8MasterSendPolling(WREN);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	_delay_ms(5);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
	SPI_u8MasterSendPolling(WRITE);
	SPI_u8MasterSendPolling((u8)Copy_u16Address);
	SPI_u8MasterSendPolling(Copy_u8Data);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	_delay_ms(5);
	return Local_intErrorState;
}

u8 EEPROM_u8SendMem16Byte(u8 *Copy_u8Data,u16 Copy_u16Address,u8 Copy_u8PageSize)
{
	u8 Local_intErrorState = OK;
	u8 Local_u8itration = 0;
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
	SPI_u8MasterSendPolling(WREN);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	_delay_ms(5);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
	SPI_u8MasterSendPolling(WRITE);
	SPI_u8MasterSendPolling((u8)Copy_u16Address);
	for(Local_u8itration = 0;Local_u8itration<Copy_u8PageSize;Local_u8itration++)
	{
		SPI_u8MasterSendPolling(Copy_u8Data[Local_u8itration]);
	}
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	_delay_ms(5);
	return Local_intErrorState;
}
u8 EEPROM_u8ReadMemByte(u8* Copy_pu8Read,u16 Copy_u16Address)
{
	u8 Local_intErrorState = OK;

	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
	SPI_u8MasterSendPolling(READ);
	SPI_u8MasterSendPolling((u8)Copy_u16Address);
	SPI_u8MasterSendPolling(DUMY_NUM);
	SPI_u8MasterRecvPolling(Copy_pu8Read);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
	return Local_intErrorState;
}
