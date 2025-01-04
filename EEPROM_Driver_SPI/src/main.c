/*
 * main.c
 *
 *  Created on: Jun 28, 2024
 *      Author: user
 */

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/PORT_interface.h"
#include "../MCAL/SPI_interface.h"
#include "../HAL/CLCD_interface.h"

#include "../HAL/EEPROM_SPI_interface.h"

void NotiFunc();
u8 x;
void main()
{
	PORT_voidInit();
	CLCD_voidInit();
	
	SPI_voidMasterInit();

	u8 DataArr[10]= {1,2,3,4,5,6,7,8,9,10};

	u8 data = 0,i=0;
	EEPROM_u8ReadMemByte(&data,0);
	if(data==0xff)
	{
		EEPROM_u8SendMem16Byte(DataArr,0x00,10);
	}
	while(1){

		for(i=0;i<9;i++)
		{
			CLCD_voidGoToXY(0,0);
			EEPROM_u8ReadMemByte(&data,i);
			CLCD_voidWriteNumber(data);
			_delay_ms(100);
		}



	}
	while(1);
}
void NotiFunc()
{
	// DOUE
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH);
}
