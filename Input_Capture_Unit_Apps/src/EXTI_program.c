/*
 * EXTI_program.c
 *
 *  Created on: Jul 23, 2024
 *      Author: user
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/EXTI_interface.h"

#include "../MCAL/EXTI_private.h"
#include "../MCAL/EXTI_config.h"
#include "../MCAL/EXTI_register.h"

static void (*EXTI_voidCallBack[3])() = {NULL};


void EXTI_voidInt0Init()
{
	MCUCR &= MASK_SENCE_INT0;
	MCUCR |= EXTI0_SENCECONTROL<<MCUCR_ISC00;

	SET_BIT(GICR,GICR_INT0);
}

u8 EXTI_u8Int0CallBack(void (*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if(Notification != NULL )
	{
		EXTI_voidCallBack[EXTI0] = Notification;
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}

u8 EXTI_u8Int0ChangeSence(u8 Copy_u8Sence)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_u8Sence<=EXTI0_RISING_ADGE)
	{
		MCUCR &= MASK_SENCE_INT0;
		MCUCR |= Copy_u8Sence<<MCUCR_ISC00;
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}
void EXTI_voidInt1Init()
{
	MCUCR &= MASK_SENCE_INT1;
	MCUCR |= EXTI1_SENCECONTROL<<MCUCR_ISC10;

	SET_BIT(GICR,GICR_INT1);
}

u8 EXTI_u8Int1CallBack(void (*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if(Notification != NULL )
	{
		EXTI_voidCallBack[EXTI1] = Notification;
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}
u8 EXTI_u8Int1ChangeSence(u8 Copy_u8Sence)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_u8Sence<=EXTI1_RISING_ADGE)
	{
		MCUCR &= MASK_SENCE_INT1;
		MCUCR |= Copy_u8Sence<<MCUCR_ISC10;
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}
void EXTI_voidInt2Init()
{
	MCUCSR &= MASK_SENCE_INT2;
	MCUCSR |= EXTI2_SENCECONTROL<<MCUCSR_ISC2;

	SET_BIT(GICR,GICR_INT2);
}

u8 EXTI_u8Int2CallBack(void (*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if(Notification != NULL )
	{
		EXTI_voidCallBack[EXTI2] = Notification;
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}

u8 EXTI_u8Int2ChangeSence(u8 Copy_u8Sence)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_u8Sence<=EXTI2_RISING_ADGE)
	{
		MCUCSR &= MASK_SENCE_INT2;
		MCUCSR |= Copy_u8Sence<<MCUCSR_ISC2;
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}

u8 EXTI_u8IntDisable(u8 Copy_u8IntID)
{
	u8 Local_u8ErrorState = OK;
	switch(Copy_u8IntID)
	{
	case EXTI0:CLR_BIT(GICR,GICR_INT0);break;
	case EXTI1:CLR_BIT(GICR,GICR_INT1);break;
	case EXTI2:CLR_BIT(GICR,GICR_INT2);break;
	default: Local_u8ErrorState = NOTOK;
	}
	return Local_u8ErrorState;

}
u8 EXTI_u8IntEnable(u8 Copy_u8IntID)
{
	u8 Local_u8ErrorState = OK;
	switch(Copy_u8IntID)
	{
	case EXTI0:SET_BIT(GICR,GICR_INT0);break;
	case EXTI1:SET_BIT(GICR,GICR_INT1);break;
	case EXTI2:SET_BIT(GICR,GICR_INT2);break;
	default: Local_u8ErrorState = NOTOK;
	}
	return Local_u8ErrorState;

}

void __vector_1 (void)	__attribute__((signal));
void __vector_1 (void)
{
	EXTI_voidCallBack[EXTI0]();
}

void __vector_2 (void)	__attribute__((signal));
void __vector_2 (void)
{
	EXTI_voidCallBack[EXTI1]();
}

void __vector_3 (void)	__attribute__((signal));
void __vector_3 (void)
{
	EXTI_voidCallBack[EXTI2]();
}
