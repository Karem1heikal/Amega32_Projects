/*
 * smartAPP.c
 *
 *  Created on: Apr 28, 2024
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

// ADC variables initialization

u16 milliVolt;
u8 readIR_sens;
u16 GlobData;
// Temp Variables
u8 TempEnter = 0;
u8 TempMultiplier = 10;

void LTSystem()
{
	CLCD_voidSendCommand(0x80);
	CLCD_voidSendString("1-AirCon 2-SafeMod");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("3-Rooms  4-fan");
	// ***** Choose Options *****
	do{
		GlobData = KPD_u8Key_pressed();
	}while(GlobData==KPAD_STATE_ILDE);
	if(GlobData==1)
	{
		CLCD_voidSendCommand(1);
		CLCD_voidSendString("temp : ");
		for( u8 i=0;i<2 ; i++)
		{
			do{
				GlobData = KPD_u8Key_pressed();
			}while(GlobData==KPAD_STATE_ILDE);
			if((0<=GlobData)&&(GlobData<=9))
			{
				CLCD_voidWriteNumber(GlobData);
				TempEnter+=TempMultiplier*GlobData;
				// mul 10 to 2nd Digit
				TempMultiplier/=10;
			}
			else{
				// reset Values
				TempEnter = 0;
				TempMultiplier = 10;
				break;
			}
		}
		_delay_ms(200);
		do
		{
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("temp : ");
			//CLCD_voidSendData(GlobData);
			// start conversion : Choose Channel (0)  &  return (Reading)   &   Notification Func
			ADC_u8StartConversionAsynch(0,&milliVolt,NotifyFunc);
			if(milliVolt>TempEnter){
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);
			}
			else
				DIO_u8SetPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
			// Get keypad to get out from this mode
			GlobData = KPD_u8Key_pressed();
			// C_button to out
			if(GlobData == C_button)
			{
				// reset Values
				TempEnter = 0;
				TempMultiplier = 10;
				CLCD_voidSendCommand(1);
				break;
			}
			else
				GlobData = KPAD_STATE_ILDE;
		}while(GlobData == KPAD_STATE_ILDE );
	}
	if(GlobData==2)  // safety mode
	{
		CLCD_voidSendCommand(1);
		CLCD_voidSendString(" Safe Mode ");
		do
		{
			// Read Pir sensor
			DIO_u8GetPinValue(DIO_PORTB,DIO_PIN5,&readIR_sens);
			if(readIR_sens)
			{
				// ON ==> Red Led
				DIO_u8SetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
				//  buzzer Function
				BuzzerSound();
				// OFF ==> Red Led
				DIO_u8SetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);

			}
			GlobData = KPD_u8Key_pressed();
			if(GlobData==C_button) break;
		}while(GlobData == KPAD_STATE_ILDE );
	}
	if(GlobData == 3) // Room mode
	{
		CLCD_voidSendCommand(0x1);
		CLCD_voidSendString("(1) R_1 (3) R_3");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("(2) R_2 (4) R_4");
		do{
			// Choose any Room
			GlobData = KPD_u8Key_pressed();
			if((1<=GlobData)&&(GlobData<=4))
			{
			switch(GlobData)
			{
				case Room1:
					DIO_u8TogglePinValue(DIO_PORTC,DIO_PIN4); //Led room1
					GlobData= KPAD_STATE_ILDE;							  	// return Idle State
					break;
				case Room2:
					DIO_u8TogglePinValue(DIO_PORTC,DIO_PIN5); //Led room2
					GlobData= KPAD_STATE_ILDE;								// return Idle State
					break;
				case Room3:
					DIO_u8TogglePinValue(DIO_PORTC,DIO_PIN6); //Led room3
					GlobData= KPAD_STATE_ILDE;								// return Idle State
					break;
				case Room4:
					DIO_u8TogglePinValue(DIO_PORTC,DIO_PIN7); //Led room4
					GlobData= KPAD_STATE_ILDE;								// return Idle State
					break;

				}
		}
		else if(GlobData==C_button)
		{
			CLCD_voidSendCommand(1);
			break;
		}
		else
		{
			GlobData = KPAD_STATE_ILDE;
		}
		}while(GlobData == KPAD_STATE_ILDE );
	}
	if(GlobData==4) // Fan mode
	{
		CLCD_voidSendCommand(1);
		CLCD_voidSendString("Fan 1-ON 2-OFF");
		do{
			GlobData = KPD_u8Key_pressed();
			if(GlobData == C_button)
			{
				CLCD_voidSendCommand(1);
				break;
			}
			else if((1<=GlobData)&&(GlobData<=2))
			{
				switch(GlobData)
				{
				case 1:
					DIO_u8SetPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_HIGH);
					GlobData = KPAD_STATE_ILDE;
					break;
				case 2:
					DIO_u8SetPinValue(DIO_PORTB,DIO_PIN6,DIO_PIN_LOW);
					GlobData = KPAD_STATE_ILDE;
					break;
				}
			}
			else
				GlobData = KPAD_STATE_ILDE;
		}while(GlobData==KPAD_STATE_ILDE);

	}

}
void NotifyFunc()
{
	// Volt_analog = ( Digital_Read * Vref ) / 2^(resolution)   (in V)  To convert (mV) ==> (multiply by 1000)
	milliVolt=(u16)((u32)(milliVolt)*5000UL/256UL);
	// Temp sensor relation    	 1 *C  ---> 10 mV
	milliVolt/=10;
	CLCD_voidGoToXY(0,8);
	// 	milliVolt == > current Temp
	CLCD_voidWriteNumber(milliVolt);
	// check if current Temp > Entered Temp

	// display Entered Temp
	CLCD_voidGoToXY(1,0);
	CLCD_voidWriteNumber(TempEnter);
	CLCD_voidSendString(" *C - Done ! ");
}

void BuzzerSound()
{
	u8 i;
	/* Diaphragm */
	for(i=0;i<20;i++){
		DIO_u8SetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH);
		_delay_ms(50);
		DIO_u8SetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_LOW);
		_delay_ms(50);
	}

}
