/*
 * TIMER_program.c
 *
 *  Created on: Aug 7, 2024
 *      Author: user
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/TIMER_private.h"
#include "../MCAL/TIMER_config.h"
#include "../MCAL/TIMER_interface.h"
#include "../MCAL/TIMER_register.h"

static void (*TIMER_pvCallBackFunc[8])() = {NULL};

static u32 Global_u32CounterOvf = 0;

static u16 Global_u16Preload = 0;


static u8 TIMER_u8Direction = TIMER1_SCHEDULER;

static u8 Global_u8Preiodic = 0;

void TIMER_voidInit(Timer_t* Copy_Timer)
{
	switch(Copy_Timer->TimerNum)
	{
		case TIMER0:
		switch(Copy_Timer->TimerMode)
		{
		case TIMER0_NORMAL:CLR_BIT(TCCR0,TCCR0_WGM01);CLR_BIT(TCCR0,TCCR0_WGM00);
		Copy_Timer->IntEnable?SET_BIT(TIMSK,TIMSK_TOIE0):CLR_BIT(TIMSK,TIMSK_TOIE0);
		break;
		case TIMER0_PHASE_CORRECT_PWM:CLR_BIT(TCCR0,TCCR0_WGM01);SET_BIT(TCCR0,TCCR0_WGM00);break;
		case TIMER0_CTC:SET_BIT(TCCR0,TCCR0_WGM01);CLR_BIT(TCCR0,TCCR0_WGM00);
		Copy_Timer->IntEnable?SET_BIT(TIMSK,TIMSK_OCIE0):CLR_BIT(TIMSK,TIMSK_OCIE0);
		break;
		case  TIMER0_FAST_PWM:SET_BIT(TCCR0,TCCR0_WGM01);SET_BIT(TCCR0,TCCR0_WGM00);break;
		}
		TCCR0 &= MASK_COMP_MATCH_MODE;
		TCCR0 |= Copy_Timer->CompOutMode<<TCCR0_COM00;
		TCCR0 &= MASK_CLOCK_MODE;
		TCCR0 |= Copy_Timer->ClockSel<<TCCR0_CS00;
		break;
		case TIMER1:
			TCCR1A &= MASK_TIMER1A_MODE;
			TCCR1A |= (Copy_Timer->TimerMode&(~(MASK_TIMER1A_MODE)));
			TCCR1B &= MASK_TIMER1B_MODE;
			TCCR1B |= ((Copy_Timer->TimerMode&(~(MASK_TIMER1B_MODE_VAL)))<<1);
			// set channel A , channel B
			TCCR1A &=MASK_COMP_MATCH1A_MODE;
			TCCR1A |= Copy_Timer->CompOutMode<<TCCR1A_COM1B0;

			TCCR1B &= MASK_CLOCK_MODE;
			TCCR1B |= Copy_Timer->ClockSel<<TCCR1B_CS10;

			Copy_Timer->ICU_EdgeSel?SET_BIT(TCCR1B,TCCR1B_ICES1):CLR_BIT(TCCR1B,TCCR1B_ICES1);


			TIMSK &= MASK_TIMER1_INTS;
			TIMSK |= Copy_Timer->IntEnable<<TIMSK_TOIE1;
			break;
		case TIMER2:
			switch(Copy_Timer->TimerMode)
			{
			case TIMER2_NORMAL:CLR_BIT(TCCR2,TCCR2_WGM21);CLR_BIT(TCCR2,TCCR2_WGM20);
			Copy_Timer->IntEnable?SET_BIT(TIMSK,TIMSK_TOIE2):CLR_BIT(TIMSK,TIMSK_TOIE2);
			break;
			case TIMER2_PHASE_CORRECT_PWM:CLR_BIT(TCCR2,TCCR2_WGM21);SET_BIT(TCCR2,TCCR2_WGM20);break;
			case TIMER2_CTC:SET_BIT(TCCR2,TCCR2_WGM21);CLR_BIT(TCCR2,TCCR2_WGM20);
			Copy_Timer->IntEnable?SET_BIT(TIMSK,TIMSK_OCIE2):CLR_BIT(TIMSK,TIMSK_OCIE2);
			break;
			case  TIMER2_FAST_PWM:SET_BIT(TCCR2,TCCR2_WGM21);SET_BIT(TCCR2,TCCR2_WGM20);break;
			}
			TCCR2 &= MASK_COMP_MATCH_MODE;
			TCCR2 |= Copy_Timer->CompOutMode<<TCCR2_COM20;
			TCCR2 &= MASK_CLOCK_MODE;
			TCCR2 |= Copy_Timer->ClockSel<<TCCR2_CS20;
			break;
	}
}

void TIMER0_voidSetPreloadValue(u8 Copy_u8PreloadValue)
{
	TCNT0 = Copy_u8PreloadValue;
}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8CompVal)
{
	OCR0 = Copy_u8CompVal;
}

u8 TIMER0_u8SetCallBack(Timer_t *Copy_Timer,void (*Notifiction)())
{
	u8 Local_u8ErrorState = OK;
	if((Copy_Timer!=NULL)||(Notifiction !=NULL))
	{

		switch(Copy_Timer->TimerMode)
		{
		case TIMER0_NORMAL:TIMER_pvCallBackFunc[TIMER0_OVF] = Notifiction;
		break;
		case TIMER0_CTC:TIMER_pvCallBackFunc[TIMER0_CMV] = Notifiction;
		break;
		}

	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}
/*
void  TIMER0_voidSetPWMFixedTop(u8 Copy_u8DutyCycle)
{
	Timer_t t0 = {TIMER0,TIMER0_FAST_PWM,OC0_CCST,TIMER_DIV_64,TIMER0_INT_DISABLE};
	TIMER_voidInit(&t0);
	TIMER0_voidSetCompMatchValue((u8)((256UL*Copy_u8DutyCycle)/100UL));
}
*/
void TIMER1_voidSetICR(u16 Copy_u16Top)
{
	ICR1 = Copy_u16Top;
}
void TIMER1_voidSetPreloadValue(u16 Copy_u16PreloadValue)
{
	TCNT1 = Copy_u16PreloadValue;
}
u16 TIMER1_u16ReadTimerValue()
{
	return TCNT1;
}

void TIMER1_voidSetChannelACompMatch(u16 Copy_u16CompVal)
{
	OCR1A = Copy_u16CompVal;
}
void TIMER1_voidSetChannelBCompMatch(u16 Copy_u16CompVal)
{
	OCR1B = Copy_u16CompVal;
}
u8 TIMER1_u8SetCallBack(Timer_t *Copy_Timer,void(*Notifiction)())
{
	u8 Local_u8ErrorState = OK;
	if((Copy_Timer!=NULL)||(Notifiction !=NULL))
	{
		switch(Copy_Timer->TimerMode)
		{
		case TIMER1_NORMAL:TIMER_pvCallBackFunc[TIMER1_OVF] = Notifiction;
		TIMER_u8Direction = TIMER1_ORDINARY;
		break;
		case TIMER1_CTC:
			switch(Copy_Timer->CompOutMode)
			{
			case OC1A_DIS:case OC1A_TOG:case OC1A_CLR:case OC1A_SET:
				TIMER_pvCallBackFunc[TIMER1A_CMV] = Notifiction;
				break;
			}
			switch(Copy_Timer->CompOutMode)
			{
			case OC1B_DIS:case OC1B_TOG:case OC1B_CLR:case OC1B_SET:
				TIMER_pvCallBackFunc[TIMER1B_CMV] = Notifiction;
				break;
			}
			break;
		case TIMER1_IC_CTC:
			TIMER_pvCallBackFunc[TIMER1_CAPT] = Notifiction;
			break;

		}
	}
	else
		Local_u8ErrorState = NULL_POINTER;

	return Local_u8ErrorState;
}

void TIMER1_voidDisableOvfInterrupt()
{
	CLR_BIT(TIMSK,TIMSK_TOIE1);
}
void ICU_voidInit()
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
	SET_BIT(TCCR1B,TCCR1B_ICES1);
}

u16 ICU_u16ReadInputCapture()
{
	return ICR1;
}

u8 ICU_u8CaptureEdgeSelect(u8 Copy_u8CapEdge)
{
	u8 Local_u8ErrorState = OK;
	switch(Copy_u8CapEdge)
	{
	case ICU_FALLING_EDGE: CLR_BIT(TCCR1B,TCCR1B_ICES1);break;
	case ICU_RISING_EDGE: SET_BIT(TCCR1B,TCCR1B_ICES1);break;
	default:Local_u8ErrorState = NOTOK;
	}
	return Local_u8ErrorState;
}

void ICU_voidInterruptEnable()
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void ICU_voidInterruptDisable()
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u8 ICU_u8SetCallBack(void (*Notifiction)())
{
	u8 Local_u8ErrorState = OK;
	if(Notifiction != NULL)
	{
		TIMER_pvCallBackFunc[TIMER1_CAPT] = Notifiction;
	}
	else
		Local_u8ErrorState = NULL_POINTER;

	return Local_u8ErrorState;
}

void TIMER2_voidSetPreloadValue(u8 Copy_u8PreloadValue)
{
	TCNT2 = Copy_u8PreloadValue;
}
void TIMER2_voidSetCompMatchValue(u8 Copy_u8CompVal)
{
	OCR2 = Copy_u8CompVal;
}
u8 TIMER2_u8SetCallBack(Timer_t *Copy_Timer,void (*Notifiction)())
{
	u8 Local_u8ErrorState = OK;
	if((Copy_Timer!=NULL)||(Notifiction !=NULL))
	{
		switch(Copy_Timer->TimerMode)
		{
		case TIMER2_NORMAL:TIMER_pvCallBackFunc[TIMER2_OVF] = Notifiction;
		break;
		case TIMER2_CTC:TIMER_pvCallBackFunc[TIMER2_CMV] = Notifiction;
		break;
		}

	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}

u8 TIMER_u8Scheduler(u16 Copy_u16Delay_ms,void  (*Notifiction)(),u8 Copy_u8Periodic)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32CounterOvf = 0;
	u16 Local_u16PreloadVal = 0;
	u32 Local_u32Delay_us = 0;
	Timer_t t1 = {TIMER1,TIMER1_NORMAL,OC1A_DIS,TIMER10_DIV_8,TIMER1_OVF_INT_ENABLE,ICU_FALLING_EDGE};
	if(Notifiction!=NULL)
	{
		TIMER_u8Direction = TIMER1_SCHEDULER;
		Local_u32Delay_us = ((u32)(Copy_u16Delay_ms))*1000UL;

		if(Local_u32Delay_us<= 65535)
		{
			Local_u16PreloadVal = (u16)(65536UL-Local_u32Delay_us);
			TIMER1_voidSetPreloadValue(Local_u16PreloadVal);
			Global_u32CounterOvf = 1;
		}
		else
		{
			Local_u32CounterOvf = Local_u32Delay_us/65536UL;
			if(Local_u32Delay_us%65536UL==0)
			{
				Global_u32CounterOvf = Local_u32CounterOvf;
				Local_u16PreloadVal = 0;
				TIMER1_voidSetPreloadValue(0);

			}
			else
			{
				//Calc_dicmal(Local_u32Delay_us,65536)
				Local_u16PreloadVal = (u16)(((Calc_dicmal(Local_u32Delay_us,65536))*65536UL)/1000UL);
				//Local_u16PreloadVal = (u16)((f32)((f32)(((f32)(Local_u32Delay_us))/65536.0)-Local_u32CounterOvf))*1000UL;
				//CLCD_voidWriteNumber(Local_u16PreloadVal);
				Global_u32CounterOvf = Local_u32CounterOvf + 1;
				TIMER1_voidSetPreloadValue(Local_u16PreloadVal);

			}
		}
		Global_u16Preload = Local_u16PreloadVal;
		TIMER_pvCallBackFunc[TIMER1_OVF]=Notifiction;
		Global_u8Preiodic = Copy_u8Periodic;
		TIMER_voidInit(&t1);
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}

// CTC timer/counter0
void __vector_10 (void)	__attribute__((signal));
void __vector_10 (void)
{
	TIMER_pvCallBackFunc[TIMER0_CMV]();

}
// OVF timer/counter0
void __vector_11 (void)	__attribute__((signal));
void __vector_11 (void)
{
	TIMER_pvCallBackFunc[TIMER0_OVF]();

}
// CTC timer/counter1A
void __vector_7 (void)	__attribute__((signal));
void __vector_7 (void)
{
	TIMER_pvCallBackFunc[TIMER1A_CMV]();
}
// CTC timer/counter1B
void __vector_8 (void)	__attribute__((signal));
void __vector_8 (void)
{
	TIMER_pvCallBackFunc[TIMER1B_CMV]();
}
// OVF timer/counter1
void __vector_9 (void)	__attribute__((signal));
void __vector_9 (void)
{
	if(TIMER_u8Direction == TIMER1_SCHEDULER)
	{
		static u32 Local_u32Counter = 0;
		Local_u32Counter++;
		if(Global_u32CounterOvf == Local_u32Counter)
		{

			if(Global_u8Preiodic == TIMER_DELAY_PERIODIC)
			{
				TIMER_pvCallBackFunc[TIMER1_OVF]();
				TIMER1_voidSetPreloadValue(Global_u16Preload);
				Local_u32Counter = 0;
			}
			else if(Global_u8Preiodic == TIMER_DELAY_NOT_PERIODIC)
			{
				TIMER_pvCallBackFunc[TIMER1_OVF]();
				TIMER1_voidDisableOvfInterrupt();
				Local_u32Counter = 0;
			}

		}
	}
	else if(TIMER_u8Direction == TIMER1_ORDINARY)
		TIMER_pvCallBackFunc[TIMER1_OVF]();


}


// Capture CTC Event timer/counter1
void __vector_6 (void)	__attribute__((signal));
void __vector_6 (void)
{
	TIMER_pvCallBackFunc[TIMER1_CAPT]();
}

// OVF timer/counter2
void __vector_5 (void)	__attribute__((signal));
void __vector_5 (void)
{
	TIMER_pvCallBackFunc[TIMER2_OVF]();
}
// CTC timer/counter2
void __vector_4 (void)	__attribute__((signal));
void __vector_4 (void)
{
	TIMER_pvCallBackFunc[TIMER2_CMV]();
}
static u16 Calc_dicmal(u32 x,u32 y)
{
	u32 e=x/y;
	u32 s=x%y;
	u8 count = 0;
	u32 n1,trens=0;
	u8 multi=1;
	if(s==0)
	{
		//CLCD_voidWriteNumber(e);
	}
	else{
		//CLCD_voidWriteNumber(e);
		//CLCD_voidSendData('.');
		do{
			n1 = (x % y);
			n1 *= 10;
			s=(n1/y);
			e=(n1%y);
			trens = multi*trens + s ;
			x=n1;
			multi = 10;
			count++;
		}while((e!=0)&&(count!=3));
	}
	return trens;
}
