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
#include "../MCAL/EXTI_interface.h"
#include "../MCAL/GIE_interface.h"
#include "../MCAL/TIMER_interface.h"
#include "../MCAL/WDT_interface.h"


#include "../HAL/CLCD_interface.h"



void SwICU();

void HwICU1();

void SwICU1();
void TimerOvf();

void schedFunc();

u32 Period = 0;
u32 Start = 0;
u32 End	=0;
u32 Duty = 0;

u16 ContOvf = 0;

#define HW_Ordinary			1
#define HW_Ordinary_2		6

#define SW_Ordinary			2

#define ICU_generic			3
#define ICU_SW_Generic		4
#define watch_dog_test		5

#define APP_chioce	watch_dog_test
void main()
{
	PORT_voidInit();

	//ADC_voidInit();
#if APP_chioce == HW_Ordinary
/*  HW Ordinary
	ICU_u8SetCallBack(HwICU);
	ICU_voidInit();
	Timer_t t1={TIMER1,TIMER1_NORMAL,OC1A_DIS,TIMER10_DIV_8,TIMER1A_INT_DISABLE};

	TIMER_voidInit(&t1);

	Timer_t t0={TIMER0,TIMER0_FAST_PWM,OC0_CCST,TIMER10_DIV_8,TIMER0_INT_DISABLE};

	TIMER_voidInit(&t0);

	TIMER0_voidSetCompMatchValue(64);
*/
#elif APP_chioce == SW_Ordinary
/*	SW Ordinary
	CLCD_voidInit();
	GIE_voidEnable();
	EXTI_voidInt0Init();
	Timer_t t0={TIMER0,TIMER0_FAST_PWM,OC0_CCST,TIMER10_DIV_8,TIMER0_INT_DISABLE};

	TIMER_voidInit(&t0);

	TIMER0_voidSetCompMatchValue(64);

	Timer_t t1={TIMER1,TIMER1_NORMAL,OC1A_DIS,TIMER10_DIV_8,TIMER1A_INT_ENABLE};

	TIMER_voidInit(&t1);

	EXTI_u8Int0CallBack(SwICU);

	CLCD_voidSendData('1');
	while(1)
	{
		while((Period == 0)&&(Duty==0));

		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Period : ");
		CLCD_voidWriteNumber(Period);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("Duty : ");
		CLCD_voidWriteNumber(Duty);
	}

*/
#elif APP_chioce == HW_Ordinary_2
/*	HW ordn
	Timer_t t0={TIMER0,TIMER0_FAST_PWM,OC0_CCST,TIMER10_DIV_8,TIMER0_INT_DISABLE};
	Timer_t t1={TIMER1,TIMER1_NORMAL,OC1A_DIS,TIMER10_DIV_8,TIMER1_IC_INT_ENABLE|TIMER1A_INT_DISABLE,ICU_RISING_EDGE};
	TIMER_voidInit(&t0);
	TIMER0_voidSetCompMatchValue(64);
	TIMER_voidInit(&t1);
	ICU_u8SetCallBack(HwICU);
	//ICU_voidInit();
	CLCD_voidInit();
	GIE_voidEnable();

	while(1)
	{
		while((Period == 0)&&(Duty==0));

		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Period : ");
		CLCD_voidWriteNumber(Period);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("Duty : ");
		CLCD_voidWriteNumber(Duty);
	}

*/
#elif APP_chioce == ICU_generic
	// ICU generic

	Timer_t t0={TIMER0,TIMER0_FAST_PWM,OC0_CCST,TIMER10_DIV_8,TIMER0_INT_DISABLE};
	Timer_t t1={TIMER1,TIMER1_NORMAL,OC1A_DIS,TIMER10_DIV_8,(TIMER1_IC_INT_ENABLE|TIMER1_OVF_INT_ENABLE),ICU_RISING_EDGE};

	TIMER_voidInit(&t0);
	TIMER0_voidSetCompMatchValue(64);
	CLCD_voidInit();
	TIMER_voidInit(&t1);
	TIMER1_u8SetCallBack(&t1,TimerOvf);
	ICU_u8SetCallBack(HwICU1);
	//ICU_voidInit();

	GIE_voidEnable();

	while(1)
	{
		while((Period == 0)&&(Duty==0));
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Period : ");
		CLCD_voidWriteNumber(Period);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("Duty : ");
		CLCD_voidWriteNumber(Duty);
		CLCD_voidSendData(' ');
		CLCD_voidWriteNumber(ContOvf);
	}
#elif APP_chioce == ICU_SW_Generic
	// SW Generic
	/*
	CLCD_voidInit();
	GIE_voidEnable();
	EXTI_voidInt0Init();
	Timer_t t0={TIMER0,TIMER0_FAST_PWM,OC0_CCST,TIMER10_DIV_8,TIMER0_INT_DISABLE};

	TIMER_voidInit(&t0);

	TIMER0_voidSetCompMatchValue(64);

	Timer_t t1={TIMER1,TIMER1_NORMAL,OC1A_DIS,TIMER10_DIV_8,TIMER1_OVF_INT_ENABLE};

	TIMER_voidInit(&t1);

	EXTI_u8Int0CallBack(SwICU1);

	while(1)
	{
		while((Period == 0)&&(Duty==0));

		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Period : ");
		CLCD_voidWriteNumber(Period);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("Duty : ");
		if(Duty<=100)
		CLCD_voidWriteNumber(Duty);
		else if(Duty<999)
			CLCD_voidWriteNumber(Duty/10);
		else if(Duty<9999)
			CLCD_voidWriteNumber(Duty/100);
		else if(Duty<99999)
			CLCD_voidWriteNumber(Duty/1000);
	}
*/
#elif APP_chioce == watch_dog_test
// watch dog test
	/*
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_HIGH);
	_delay_ms(1000);
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
	WDT_voidEnable();
	WDT_u8Sleep(6);*/
	/*
	CLCD_voidInit();
	GIE_voidEnable();
	TIMER_u8Scheduler(1000,schedFunc,TIMER_DELAY_NOT_PERIODIC);
	*/
#endif
	while(1);
}

void HwICU()
{
	static u8 Local_u8Cnt = 0;
	Local_u8Cnt++;
	if(Local_u8Cnt == 1)
	{
		Start = ICU_u16ReadInputCapture();
	}
	else if(Local_u8Cnt == 2)
	{
		End = ICU_u16ReadInputCapture();
		Period = End - Start;
		ICU_u8CaptureEdgeSelect(ICU_FALLING_EDGE);
	}
	else if(Local_u8Cnt == 3)
	{
		Start = ICU_u16ReadInputCapture();
		Duty = Start - End;
		ICU_voidInterruptDisable();
	}

}


void schedFunc()
{
	static u8 LocalState = 1;
	TOG_BIT(LocalState,0);
	DIO_u8SetPinValue(DIO_PORTA,DIO_PIN7,1);

}

void TimerOvf()
{
	ContOvf++;
}
void HwICU1()
{
	static u8 Local_u8Cnt = 0;
	Local_u8Cnt++;
	if(Local_u8Cnt == 1)
	{
		Start = ICU_u16ReadInputCapture();
	}
	else if(Local_u8Cnt == 2)
	{
		End = ICU_u16ReadInputCapture();
		Period = (u16)(((u32)((u32)((u32)ContOvf * 65536UL) + (u32)End)) - ((u32)Start));
		ICU_u8CaptureEdgeSelect(ICU_FALLING_EDGE);
	}
	else if(Local_u8Cnt == 3)
	{
		Start = ICU_u16ReadInputCapture();
		Duty =(u16)(((u32)((u32)((u32)ContOvf * 65536UL) + (u32)Start)) - ((u32)((u32)((u32)ContOvf * 65536UL) + (u32)End)));
		TIMER1_voidDisableOvfInterrupt();
		ICU_voidInterruptDisable();
	}
}

void SwICU1()
{

	static u8 Local_u8Counter=0;
	Local_u8Counter++;
	if(Local_u8Counter==1)
	{
		// first Rising edge
		TIMER1_voidSetPreloadValue(0);
	}
	else if(Local_u8Counter==2)
	{
		Period=TIMER1_u16ReadTimerValue();
		Period=Period+ContOvf*65536UL;
		//change triggering to Falling Edge
		EXTI_u8Int0ChangeSence(EXTI0_FALLING_ADGE);
	}
	else if(Local_u8Counter==3)
	{
		/*Timer reading Now is Period + On ticks*/
		Duty=TIMER1_u16ReadTimerValue();
		Duty=(Duty+ContOvf*65536UL);
		Duty-=(Period+ContOvf*65536UL);
		/*Disable INT0 */
		EXTI_u8IntDisable(EXTI0);
		TIMER1_voidDisableOvfInterrupt();
	}
}

void SwICU()
{
	static u8 Local_u8Cnt = 0;
	Local_u8Cnt++;
	if(Local_u8Cnt == 1)
	{
		TIMER1_voidSetPreloadValue(0);
	}
	else if(Local_u8Cnt == 2)
	{
		Period = TIMER1_u16ReadTimerValue();
		EXTI_u8Int0ChangeSence(EXTI0_FALLING_ADGE);
	}
	else if(Local_u8Cnt == 3)
	{
		Duty = TIMER1_u16ReadTimerValue();
		Duty -= Period;
		EXTI_u8IntDisable(EXTI0);

	}
}
