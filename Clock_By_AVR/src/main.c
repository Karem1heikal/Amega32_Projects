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
#include "../HAL/KPD_interface.h"
#include "../HAL/CLCD_interface.h"

#include "../MCAL/EXTI_interface.h"
#include "../MCAL/GIE_interface.h"

#define Pattern {0b0000100,\
				 0b0001110,\
				 0B0010101,\
				 0B0000100,\
				 0B0000100,\
				 0B0000100,\
				 0B0000100}

void StopWatchDisp(s8,s8,s8);
void SecSeqance(s8,s8,s8);
void minSeqance(s8,s8,s8);
void hourSeqance(s8,s8,s8);

u8 OutFlag = 0, postion=0;
s8 hrs=0,mins=0,secs=0;
u8 curser[8]= Pattern;
void OutSwitch();

void main()
{
	PORT_voidInit();
	CLCD_voidInit();
	GIE_voidEnable();
	EXTI_voidInt2Init();
	EXTI_u8Int2CallBack(OutSwitch);

	u8 buzzer = 0;

	u8 Key;
	LED_t led1 = {
		DIO_PORTB,
		DIO_PIN0,
		LED_SOUCE
	};

	CLCD_voidWriteSpecialCharacter(curser,0,1,1);
	while(1)
	{
		StopWatchDisp(hrs,mins,secs);
		do{
			Key = KPD_u8Key_pressed();
		}while(Key == KPD_NO_PRESSED_KEY);
		switch(Key)
		{
		case 1:
			CLCD_voidGoToXY(1,7);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(1,4);
			CLCD_voidSendData(' ');
			CLCD_voidWriteSpecialCharacter(curser,0,1,1);
			CLCD_voidGoToXY(0,1);
			postion = 0;
			break;
		case 2:
			CLCD_voidGoToXY(1,1);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(1,7);
			CLCD_voidSendData(' ');
			CLCD_voidWriteSpecialCharacter(curser,0,1,4);
			CLCD_voidGoToXY(0,4);
			postion = 1;
			break;
		case 3:
			CLCD_voidGoToXY(1,1);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(1,4);
			CLCD_voidSendData(' ');
			CLCD_voidWriteSpecialCharacter(curser,0,1,7);
			CLCD_voidGoToXY(0,6);
			postion = 2;
			break;
		case '+':
			switch(postion)
			{
			case 0:
				hrs++;
				if(hrs==24)
					hrs = 0;
				break;
			case 1:
				mins++;
				if(mins==60)
					mins = 0;
				break;
			case 2:
				secs++;
				if(secs==60)
					secs = 0;
				break;
			}
			break;
		case '-':
			switch(postion)
			{
			case 0:
				hrs--;
				if(hrs==-1)
					hrs = 23;
				break;
			case 1:
				mins--;
				if(mins==-1)
					mins = 59;
				break;
			case 2:
				secs--;
				if(secs==-1)
					secs = 59;
				break;
			}
			break;
		case '=':
			CLCD_voidSendCommand(1);
			SecSeqance(hrs,mins,secs);
			if(OutFlag == 1){
				OutFlag = 0;
				break ;
			}
			minSeqance(hrs,mins,secs);
			if(OutFlag == 1){
				OutFlag = 0;
				break ;
			}
			hourSeqance(hrs,mins,secs);
			if(OutFlag == 1){
				OutFlag = 0;
				break ;
			}
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("It's time!...");
			for(buzzer = 0;buzzer<3;buzzer++)
			{
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_HIGH);
				LED_u8TurnOn(&led1);
				_delay_ms(600);
				LED_u8TurnOff(&led1);
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_LOW);
				LED_u8TurnOn(&led1);
				_delay_ms(600);
				LED_u8TurnOff(&led1);
			}

			CLCD_voidSendCommand(1);
			postion = 0;
			CLCD_voidWriteSpecialCharacter(curser,0,1,1);
			break;
		case 'C':
			CLCD_voidSendCommand(1);
			hrs = 0;
			mins = 0;
			secs = 0;
			StopWatchDisp(hrs,mins,secs);
			postion = 0;
			CLCD_voidWriteSpecialCharacter(curser,0,1,1);
			break;
		}
	}
	while(1);
}

void OutSwitch()
{
	OutFlag = 1;
}
void SecSeqance(s8 x,s8 y,s8 z)
{
	if(z == 59)
		z = 60;
	while(z != 0)
	{
		z--;
		StopWatchDisp(x,y,z);
		if(OutFlag == 1)
		{
			hrs=x;mins=y;secs=z;
			postion = 0;
			CLCD_voidWriteSpecialCharacter(curser,0,1,1);
			return ;
		}
		_delay_ms(500);
	}
}
void minSeqance(s8 x,s8 y,s8 z)
{
	if(y == 59)
		y = 60;
	while(y != 0)
	{
		z = 59;
		y--;
		SecSeqance(x,y,z);
		if(OutFlag == 1)
		{
			hrs=x;mins=y;secs=z;
			postion = 0;
			CLCD_voidWriteSpecialCharacter(curser,0,1,1);
			return ;
		}
	}
}
void hourSeqance(s8 x,s8 y,s8 z)
{
	while(x != 0)
	{
		z = 59;
		y = 59;
		x--;
		minSeqance(x,y,z);
		if(OutFlag == 1)
		{
			hrs=x;mins=y;secs=z;
			postion = 0;
			CLCD_voidWriteSpecialCharacter(curser,0,1,1);
			return ;
		}
	}
}
void StopWatchDisp(s8 x,s8 y,s8 z)
{
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteNumber(x/10);
	CLCD_voidWriteNumber(x%10);
	CLCD_voidSendData(':');
	CLCD_voidGoToXY(0,3);
	CLCD_voidWriteNumber(y/10);
	CLCD_voidWriteNumber(y%10);
	CLCD_voidSendData(':');
	CLCD_voidGoToXY(0,6);
	CLCD_voidWriteNumber(z/10);
	CLCD_voidWriteNumber(z%10);
}
