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

#include "../MCAL/ADC_interface.h"
#include "../MCAL/GIE_interface.h"

#include "../HAL/CLCD_interface.h"

#define straightAngle  		0 		// Angle corresponding to straight position (in degrees)
#define bentAngle  			90		// Angle corresponding to fully bent position (in degrees)


u8 ChannelId[5]={
		ADC0,
		ADC1,
		ADC2,
		ADC3,
		ADC4
};

u16 ReadSensors[5];
u8 angle[5];

void SignCheck();
void NotifyFunc();
u32 AppMap(u32 InMin,u32 InMax,u32 OutMin,u32 OutMax,u32 InVal);

void DispNum();

void main()
{
	PORT_voidInit();
	CLCD_voidInit();
	ADC_voidInit();
	GIE_voidEnable();
	ADC_Chain adc1 = {ChannelId,5,NotifyFunc,ReadSensors};
	u8 state = 0;

	while(1)
	{
		ADC_u8StartChainConvAsynch(&adc1);
		DIO_u8GetPinValue(DIO_PORTA,DIO_PIN7,&state);
		DispNum();
		if(state == 0)
		{
			_delay_ms(200);
			SignCheck();
		}
	}

	while(1);
}
void SignCheck()
{
	static u8 count = 0;
	CLCD_voidGoToXY(1,count);
	count++;
	if((angle[4]==0)&&(angle[3]==0)&&(angle[2]==0)&&(angle[1]==0)&&(angle[0]==0))
	{
		// Nothing
	}
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==90)&&(angle[0]==0))
		CLCD_voidSendData('A');
	else if((angle[4]==0)&&(angle[3]==0)&&(angle[2]==0)&&(angle[1]==0)&&(angle[0]==90))
		CLCD_voidSendData('B');
	else if((angle[4]==82)&&(angle[3]==82)&&(angle[2]==82)&&(angle[1]==82)&&(angle[0]==82))
		CLCD_voidSendData('C');
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==77)&&(angle[1]==0)&&(angle[0]==77))
		CLCD_voidSendData('D');
	else if((angle[4]==45)&&(angle[3]==45)&&(angle[2]==45)&&(angle[1]==45)&&(angle[0]==45))
		CLCD_voidSendData('E');
	else if((angle[4]==0)&&(angle[3]==0)&&(angle[2]==0)&&(angle[1]==77)&&(angle[0]==0))
		CLCD_voidSendData('F');
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==0)&&(angle[0]==77))
		CLCD_voidSendData('G');
	else if((angle[4]==0)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==0)&&(angle[0]==90))
		CLCD_voidSendData('H');
	else if((angle[4]==0)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==90)&&(angle[0]==90))
		CLCD_voidSendData('I');
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==0)&&(angle[1]==0)&&(angle[0]==0))
		CLCD_voidSendData('K');
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==0)&&(angle[0]==0))
		CLCD_voidSendData('L');
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==90)&&(angle[0]==90))
		CLCD_voidSendData('O');
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==90)&&(angle[0]==77))
		CLCD_voidSendData('S');
	else if((angle[4]==0)&&(angle[3]==0)&&(angle[2]==0)&&(angle[1]==90)&&(angle[0]==0))
		CLCD_voidSendData('T');
	else if((angle[4]==90)&&(angle[3]==90)&&(angle[2]==0)&&(angle[1]==0)&&(angle[0]==90))
		CLCD_voidSendData('U');
	else if((angle[4]==90)&&(angle[3]==0)&&(angle[2]==0)&&(angle[1]==0)&&(angle[0]==90))
		CLCD_voidSendData('W');
	else if((angle[4]==90)&&(angle[3]==0)&&(angle[2]==71)&&(angle[1]==71)&&(angle[0]==90))
		CLCD_voidSendData('X');
	else if((angle[4]==0)&&(angle[3]==90)&&(angle[2]==90)&&(angle[1]==90)&&(angle[0]==0))
		CLCD_voidSendData('Y');
}

void NotifyFunc()
{
	// sensor1
	ReadSensors[0] = (u16)(((u32)(ReadSensors[0]*5000UL))/256UL);
	angle[0] = AppMap(2421, 3496, straightAngle, bentAngle, ReadSensors[0]);
	angle[0]=90-angle[0];

	// sensor2
	ReadSensors[1] = (u16)(((u32)(ReadSensors[1]*5000UL))/256UL);
	angle[1] = AppMap(2421, 3496, straightAngle, bentAngle, ReadSensors[1]);
	angle[1]=90-angle[1];

	// sensor3
	ReadSensors[2] = (u16)(((u32)(ReadSensors[2]*5000UL))/256UL);
	angle[2] = AppMap(2421, 3496, straightAngle, bentAngle, ReadSensors[2]);
	angle[2]=90-angle[2];

	// sensor4
	ReadSensors[3] = (u16)(((u32)(ReadSensors[3]*5000UL))/256UL);
	angle[3] = AppMap(2421, 3496, straightAngle, bentAngle, ReadSensors[3]);
	angle[3]=90-angle[3];

	// sensor5
	ReadSensors[4] = (u16)(((u32)(ReadSensors[4]*5000UL))/256UL);
	angle[4] = AppMap(2421, 3496, straightAngle, bentAngle, ReadSensors[4]);
	angle[4]=90-angle[4];


}
void DispNum()
{
	CLCD_voidGoToXY(0,0);
	CLCD_voidWriteNumber(angle[0]);
	CLCD_voidGoToXY(0,3);
	CLCD_voidWriteNumber(angle[1]);
	CLCD_voidGoToXY(0,6);
	CLCD_voidWriteNumber(angle[2]);
	CLCD_voidGoToXY(0,9);
	CLCD_voidWriteNumber(angle[3]);
	CLCD_voidGoToXY(0,12);
	CLCD_voidWriteNumber(angle[4]);
}
u32 AppMap(u32 InMin,u32 InMax,u32 OutMin,u32 OutMax,u32 InVal)
{
	u32 Local=0;
	Local = (((InVal-InMin)*(OutMax-OutMin))/(InMax-InMin))+OutMin;
	return Local;
}
