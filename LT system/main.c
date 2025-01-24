/*
 * main.c
 *
 *  Created on: Jul 22, 2023
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
#include "SSD_interface.h"
#include "KPD_interface.h"
void BuzzerSound();
void LED_CONTROL(u8 ledNum);
void NotifyFunc();
u32 Maping(u32 MinRangeX,u32 MaxRangeX, u32 MinRangY, u32 MaxRangeY,u32 InpValue);
void LTSystem();
// ADC variables initialization
u16 milliVolt,	milliVolt1,NUMLED;
u8 ARRADC[2]={0,1};
u16 result[2]={0};
Chain_t channel={ARRADC,2,result,NotifyFunc};
//u16 Local_u16readingchannel;
void main()
{
	//buzzer
	/*
	PORT_voidInit();
	while(1)
	{
		BuzzerSound();
	}*/
	PORT_voidInit();
	CLCD_voidInit();
	ADC_voidInit();
	GINT_voidEnable();

	/*kpd ,SSd Number*/
	u8 Keypress=45,trials=2;
	//voltage in milli ,password Storage variable
	u16  password=0,pass=0,p=1;
	// entre or not
	u8 isEntered=0;
	// SSD arr 1 => 3
	u8 arr[3]={SSD_u8VisableNUM1,SSD_u8VisableNUM2,SSD_u8VisableNUM3};
	// display 3
	DIO_u8SetPortValue(DIO_PORTC,arr[trials]);
	CLCD_voidSendString("WELCOME");
	_delay_ms(1000);
	CLCD_voidSendCommand(1);
	while(1)
	{
		CLCD_voidSendCommand(1);
		CLCD_voidSendString("Enter ID : ");
		do{
			do{
				Keypress=KPD_u8Key_pressed();
			}while(Keypress==0xff);
			if((0<=Keypress)&&(Keypress<=9)){
				isEntered=1;
				CLCD_voidWriteNumber(Keypress);
				pass=pass+Keypress*p;
				p*=10;
			}
		}while(Keypress!=14);
		p/=10;
		//real password
		password=pass;
		pass=0;
		CLCD_voidSendCommand(1);
		while(1){

			CLCD_voidSendString("Enter pass:");
			do{
				do{
					Keypress=KPD_u8Key_pressed();
				}while(Keypress==0xff);
				if((0<=Keypress)&&(Keypress<=9)){

					CLCD_voidWriteNumber(Keypress);
					pass=pass+Keypress*p;
					p/=10;
				}
			}while(Keypress!=14);
			CLCD_voidGoToXY(1,0);
			CLCD_voidWriteNumber(pass);
			CLCD_voidSendData(' ');
			CLCD_voidWriteNumber(password);
			_delay_ms(1000);
			if((pass==password)&&(isEntered==1))
			{
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("WELCOME ID ");
				CLCD_voidWriteNumber(pass);
				_delay_ms(1000);
				CLCD_voidSendCommand(1);
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_HIGH);
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN5,DIO_PIN_LOW);
				//--------------------- system ---------------------
				while(1){
					LTSystem();
				}
			}
			else
			{
				if(isEntered==1){
					trials--;
					DIO_u8SetPortValue(DIO_PORTC,arr[trials]);
					pass=0;
					password=0;
					p=1;
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("Try Again ! ");
					_delay_ms(1000);
					CLCD_voidSendCommand(1);
					if(trials>0)
					{
						isEntered=0;
						continue;
					}else{
						DIO_u8SetPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH);
						break;
					}
				}
				else{
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("   Please,");
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Enter your data.");
					_delay_ms(1000);
					continue;
				}
			}
		}
	}
	while(1);

}
u32 Maping(u32 MinRangeX,u32 MaxRangeX, u32 MinRangY, u32 MaxRangeY,u32 InpValue)
{
	return (((InpValue-MinRangeX)*(MaxRangeY-MinRangY)/(MaxRangeX-MinRangeX))+MinRangY);
}

void LED_CONTROL(u8 ledNum)
{
	DIO_u8SetPortValue(DIO_PORTC,(1<<ledNum)-1);
}
void LTSystem()
{
	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidSendString("temp : ");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("leds : ");
	ADC_u8StartChainConvertionAsynch(&channel);
	_delay_ms(20);
	if(milliVolt>30){
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);
	}
	else
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
}

void NotifyFunc()
{
	//DIO_u8SetPortValue(DIO_PORTD,Local_u16readingchannel);
	milliVolt=(u16)((u32)(channel.result[0])*5000UL/256UL);
	milliVolt/=10;
	CLCD_voidGoToXY(0,8);
	CLCD_voidWriteNumber(milliVolt);
	milliVolt1=(u16)((u32)(channel.result[1])*5000UL/256UL);
	milliVolt1/=10;
	NUMLED=Maping(3,474,1,8,milliVolt1);
	NUMLED=9-NUMLED;
	LED_CONTROL(NUMLED);
	CLCD_voidGoToXY(1,8);
	CLCD_voidWriteNumber(NUMLED);
}
void BuzzerSound()
{
	u8 i;
	/* Diaphragm */
	for(i=0;i<20;i++){
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_HIGH);
		_delay_ms(50);
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		_delay_ms(50);
	}
	_delay_ms(1000);
	for(i=0;i<20;i++){
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_HIGH);
		_delay_ms(70);
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		_delay_ms(70);
	}
	_delay_ms(1000);
	for(i=0;i<20;i++){
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_HIGH);
		_delay_ms(100);
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		_delay_ms(100);
	}
	_delay_ms(1000);
	for(i=0;i<20;i++){
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_HIGH);
		_delay_ms(200);
		DIO_u8SetPinValue(DIO_PORTB,DIO_PIN7,DIO_PIN_LOW);
		_delay_ms(200);
	}
	_delay_ms(1000);
}
