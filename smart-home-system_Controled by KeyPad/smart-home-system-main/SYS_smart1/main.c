/*
 * main.c
 *
 *  Created on: Apr 19, 2024
 *      Author: user
 */


#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GINT_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "smartAPP.h"


void main()
{
	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	GINT_voidEnable();
	/*kpd ,SSd Number*/
	u8 Keypress=0;
	s8 trials = 3;
	//voltage in milli ,password Storage variable
	u16  Enter_password=0,defult_pass=1234,multiplier=1;
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Welcome Sr");
	_delay_ms(500);

	while(1)
	{
		CLCD_voidSendCommand(1);
		CLCD_voidSendString("Enter pass:"); // 4 Digit for password
		do{
			do{
				Keypress=KPD_u8Key_pressed();
			}while(Keypress==0xff);
			if((0<=Keypress)&&(Keypress<=9)){
				CLCD_voidWriteNumber(Keypress);
				Enter_password=Enter_password*multiplier+Keypress;
				multiplier=10;
			}
		}while(Keypress!=14);
		if(Enter_password==defult_pass) // pass
		{
			while(1)
			{
				// blink Green led
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
				_delay_ms(400);
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_LOW);
				//**** Start System *****
				LTSystem();
			}
		}
		else
		{
			trials--;
			if(trials==0)
			{
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("    ShutDown");
				CLCD_voidGoToXY(1,9);
				CLCD_voidSendData('3');
				_delay_ms(500);
				CLCD_voidGoToXY(1,9);
				CLCD_voidSendData('2');
				_delay_ms(500);
				CLCD_voidGoToXY(1,9);
				CLCD_voidSendData('1');
				_delay_ms(500);
				CLCD_voidSendCommand(1);
				trials = 3;
				multiplier=1;
				Enter_password = 0;
				_delay_ms(500);
			}
			else{
				// ON ==> Red Led
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
				BuzzerSound();
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("    Try Again!");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Trials : ");
				CLCD_voidGoToXY(1,9);
				CLCD_voidWriteNumber(trials);
				_delay_ms(500);
				// OFF ==> Red Led
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
				// Initial Values
				multiplier=1;
				Enter_password = 0;
			}
		}
	}

}


