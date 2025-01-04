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

// ********************** Traffic Light *************************** //
void main()
{
	PORT_voidInit();
	u8 seg[10]={0x3f,0x06,0x5B,0x4f,0x66,0x6D,0x7D,0x07,0x7f,0x6f};
	u8 i=0;
	while(1)
	{
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_HIGH);
		for(i=0;i<10;i++)
		{
			DIO_u8SetPortValue(DIO_PORTC,~seg[(9-i)%10]);
			_delay_ms(500);
		}
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN0,DIO_PIN_LOW);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_HIGH);
		for(i=0;i<3;i++)
		{
			DIO_u8SetPortValue(DIO_PORTC,~seg[(2-i)%3]);
			_delay_ms(500);
		}
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN1,DIO_PIN_LOW);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_HIGH);
		for(i=0;i<10;i++)
		{
			DIO_u8SetPortValue(DIO_PORTC,~seg[(9-i)%10]);
			_delay_ms(500);
		}
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN2,DIO_PIN_LOW);
	}
	while(1);
}
