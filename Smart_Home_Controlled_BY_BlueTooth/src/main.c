/*
 * main.c
 *
 *  Created on: Jun 28, 2024
 *      Author: user
 */

#include <util/delay.h>
#include <string.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/PORT_interface.h"
#include "../MCAL/ADC_interface.h"
#include "../MCAL/GIE_interface.h"
#include "../MCAL/TIMER_interface.h"
#include "../MCAL/USART_interface.h"

#include "../HAL/SERVO_interface.h"
#include "../HAL/CLCD_interface.h"




char strdata[20]={0};
u32 AppMap(u32 InMin,u32 InMax,u32 OutMin,u32 OutMax,u32 InVal);
void BuzzerSound();
#define NO_NOTE		0
#define LDR_NOTE	2
#define LM35_NOTE	1


u8 ChannelArr[2]={ADC7,ADC6};
u16 ResultArr[2];

void LedAdjustMotorAdjust();

u8 notifyFlag1 = NO_NOTE;
u8 notifyFlag2 = NO_NOTE;
u16 LdrVal = 0;
u16 Lm35Val = 0;
u16 CompPWM = 0;
void main()
{
	PORT_voidInit();
	CLCD_voidInit();
	USART_init();
	ADC_voidInit();
	GIE_voidEnable();
	SERVO_voidInit();
	u16 data,password = 0;
	u8 num,multi = 1,trials = 2,curserPos = 11;
	ADC_Chain adc1 = {ChannelArr,2,LedAdjustMotorAdjust,ResultArr};
	Timer_t t0 = {TIMER0,TIMER0_FAST_PWM,OC0_DIS,TIMER10_DIV_64,TIMER0_INT_DISABLE};
	TIMER_voidInit(&t0);
	Timer_t t1 = {TIMER1,TIMER1_IC_FAST_PWM,OC1A_DIS,TIMER10_DIV_8,TIMER1A_INT_DISABLE};
	TIMER1_voidSetICR(20000);
	TIMER_voidInit(&t1);

	USART_u8SendStringPoll("welcome! *_*");
	USART_u8SendPolling(0xD);
	USART_u8SendPolling(0xD);

	
	while(1)
	{
		//USART_u8SendStringPoll("Enter Password : ");
		CLCD_voidSendString("Enter Pass: ");
		for(num=0;num < 4 ;num++)
		{
			USART_u8ReceivePollingWithOut(&data);
			if(('0'<=data)&&(data<='9'))
			{

				CLCD_voidGoToXY(0,curserPos);
				CLCD_voidSendData(data);
				_delay_ms(100);
				CLCD_voidGoToXY(0,curserPos);
				CLCD_voidSendData('*');
				password = (data&0x0f) +password*multi;
				multi = 10;
				curserPos++;
			}
			if(data==0x0D)
				break;
		}
		if(password==1234)
		{
			USART_u8SendPolling(0xD);
			USART_u8SendPolling(0xD);
			USART_u8SendStringPoll("welcome! *_*");
			USART_u8SendPolling(0xD);
			USART_u8SendStringPoll("1-open door.    2-close door.");
			USART_u8SendPolling(0xD);
			USART_u8SendStringPoll("3-open Light.   4-close Light.");
			USART_u8SendPolling(0xD);
			USART_u8SendStringPoll("5-Adjust Light. 6-open fan.");
			USART_u8SendPolling(0xD);
			USART_u8SendStringPoll("7-close fan.    8-Adjust fan.");
			USART_u8SendPolling(0xD);
			USART_u8SendStringPoll("9-Play music.");
			USART_u8SendPolling(0xD);
			DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
			CLCD_voidGoToXY(0,0);
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("D: OFF  L: OFF");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("F: OFF  M: S");
			while(1)
			{
				USART_u8ReceiveBufferPollWithOut(strdata,20);
				if(strcmp(strdata,"light on")==0){
					notifyFlag1 = NO_NOTE;
					t1.CompOutMode = OC1A_DIS;
					TIMER1_voidCompOutModeChange(&t1);
					DIO_u8SetPinValue(DIO_PORTD,DIO_PIN5,DIO_PIN_HIGH);

					CLCD_voidGoToXY(0,11);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(0,11);
					CLCD_voidSendString("ON");
				}
				else if(strcmp(strdata,"light off")==0)
				{
					notifyFlag1 = NO_NOTE;
					t1.CompOutMode = OC1A_DIS;
					TIMER1_voidCompOutModeChange(&t1);
					DIO_u8SetPinValue(DIO_PORTD,DIO_PIN5,DIO_PIN_LOW);
					CLCD_voidGoToXY(0,11);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(0,11);
					CLCD_voidSendString("OFF");
				}
				else if(strcmp(strdata,"light adjust")==0)
				{
					notifyFlag1 = LDR_NOTE;
					t1.CompOutMode = OC1A_CCST;
					TIMER1_voidCompOutModeChange(&t1);
					ADC_u8StartChainConvAsynch(&adc1);
					CLCD_voidGoToXY(0,11);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(0,11);
					CLCD_voidSendString("ADJ");
				}
				else if(strcmp(strdata,"door open")==0)
				{
					t1.CompOutMode = OC1B_CCST;
					TIMER1_voidCompOutModeChange(&t1);
					SERVO_voidSetAngle(180);
					CLCD_voidGoToXY(0,3);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(0,3);
					CLCD_voidSendString("ON");
				}
				else if(strcmp(strdata,"door close")==0)
				{
					t1.CompOutMode = OC1B_CCST;
					TIMER1_voidCompOutModeChange(&t1);
					SERVO_voidSetAngle(0);
					CLCD_voidGoToXY(0,3);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(0,3);
					CLCD_voidSendString("OFF");
				}
				else if(strcmp(strdata,"fan on")==0)
				{
					notifyFlag2 = NO_NOTE;
					t0.CompOutMode = OC0_DIS;
					TIMER0_voidCompOutModeChange(&t0);
					DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
					CLCD_voidGoToXY(1,3);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(1,3);
					CLCD_voidSendString("ON");
				}
				else if(strcmp(strdata,"fan off")==0)
				{
					notifyFlag2 = NO_NOTE;
					t0.CompOutMode = OC0_DIS;
					TIMER0_voidCompOutModeChange(&t0);
					DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
					CLCD_voidGoToXY(1,3);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(1,3);
					CLCD_voidSendString("OFF");
				}
				else if(strcmp(strdata,"fan adjust")==0)
				{
					notifyFlag2 = LM35_NOTE;
					DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
					t0.CompOutMode = OC0_CCST;
					TIMER0_voidCompOutModeChange(&t0);
					CLCD_voidGoToXY(1,3);
					CLCD_voidSendString("   ");
					CLCD_voidGoToXY(1,3);
					CLCD_voidSendString("ADJ");
				}
				else if(strcmp(strdata,"music play")==0)
				{
					BuzzerSound();
					CLCD_voidGoToXY(1,11);
					CLCD_voidSendString(" ");
					CLCD_voidGoToXY(1,11);
					CLCD_voidSendString("P");
				}
				else if(strcmp(strdata,"music stop")==0)
				{
					CLCD_voidGoToXY(1,11);
					CLCD_voidSendString(" ");
					CLCD_voidGoToXY(1,11);
					CLCD_voidSendString("S");
				}
				ADC_u8StartChainConvAsynch(&adc1);
			}
		}
		else
		{
			if(trials==0)
			{
				break;
			}
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("trials : ");
			CLCD_voidSendData(trials+'0');
			trials--;
			_delay_ms(500);
			CLCD_voidSendCommand(1);
			USART_u8SendStringPoll("Try again!...");
			_delay_ms(500);
			CLCD_voidSendCommand(1);
			password=0;
			multi=1;
			curserPos = 11;
		}
		while(1);
	}
}
void BuzzerSound()
{
	/* Diaphragm */
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	_delay_ms(100);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
	_delay_ms(100);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	_delay_ms(50);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
	_delay_ms(50);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
	_delay_ms(1);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	_delay_ms(100);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
	_delay_ms(100);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_HIGH);
	_delay_ms(50);
	DIO_u8SetPinValue(DIO_PORTB,DIO_PIN0,DIO_PIN_LOW);
	_delay_ms(50);

}

void LedAdjustMotorAdjust()
{
	if(notifyFlag1 == LDR_NOTE)
	{
		LdrVal = (u16)(((u32)(ResultArr[1]*5000UL))/256UL);
		LdrVal /=10;
		LdrVal = AppMap(48 ,474,2000,5000,LdrVal);
		TIMER1_voidSetChannelACompMatch(7000-LdrVal);
	}
	if(notifyFlag2 == LM35_NOTE)
	{
		Lm35Val = (u16)(((u32)(ResultArr[0]*5000UL))/256UL);
		Lm35Val /=10;

		Lm35Val = AppMap(27,42,0,90,Lm35Val);
		CompPWM = (u16)((((u32)Lm35Val)*255UL)/100UL);
		CLCD_voidGoToXY(1,6);
		if(255>CompPWM)
			TIMER0_voidSetCompMatchValue(CompPWM);

	}
}

u32 AppMap(u32 InMin,u32 InMax,u32 OutMin,u32 OutMax,u32 InVal)
{
	u32 Local=0;
	Local = (((InVal-InMin)*(OutMax-OutMin))/(InMax-InMin))+OutMin;
	return Local;
}
