/*
 * WDT_program.c
 *
 *  Created on: Aug 14, 2024
 *      Author: user
 */



#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/WDT_private.h"
#include "../MCAL/WDT_config.h"
#include "../MCAL/WDT_interface.h"
#include "../MCAL/WDT_register.h"


void WDT_voidEnable()
{
	SET_BIT(WDTCR,WDTCR_WDE);
}
void WDT_voidDisable()
{
	WDTCR |= (1<<WDTCR_WDTOE)|(1<<WDTCR_WDE);
	WDTCR = 0;
}
u8 WDT_u8Sleep(u8 Copy_u8TimerSleep)
{
	u8 Local_u8ErrorState =OK;

	if(Copy_u8TimerSleep<8)
	{
		WDTCR &= MASK_SLEEP_TIME;
		WDTCR |= Copy_u8TimerSleep;
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}
