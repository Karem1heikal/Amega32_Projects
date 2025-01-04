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

			TIMSK &= MASK_TIMER1B_MODE;
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
void TIMER0_voidCompOutModeChange(Timer_t *Copy_Timer)
{
	TCCR0 &= MASK_COMP_MATCH_MODE;
	TCCR0 |= Copy_Timer->CompOutMode<<TCCR0_COM00;
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
void TIMER1_voidCompOutModeChange(Timer_t *Copy_Timer)
{
	TCCR1A &=MASK_COMP_MATCH1A_MODE;
	TCCR1A |= Copy_Timer->CompOutMode<<TCCR1A_COM1B0;
}

void TIMER1_voidSetICR(u16 Copy_u16Top)
{
	ICR1 = Copy_u16Top;
}
void TIMER1_voidSetPreloadValue(u16 Copy_u16PreloadValue)
{
	TCNT1 = Copy_u16PreloadValue;
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
void TIMER2_voidCompOutModeChange(Timer_t *Copy_Timer)
{
	TCCR2 &= MASK_COMP_MATCH_MODE;
	TCCR2 |= Copy_Timer->CompOutMode<<TCCR2_COM20;
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
	TIMER_pvCallBackFunc[TIMER2_CTC]();
}
