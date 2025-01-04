/*
 * SERVO_program.c
 *
 *  Created on: Aug 9, 2024
 *      Author: user
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/TIMER_interface.h"
#include "../HAL/SERVO_private.h"
#include "../HAL/SERVO_config.h"
#include "../HAL/SERVO_interface.h"

void SERVO_voidInit()
{
	Timer_t t1 = {TIMER1,TIMER1_IC_FAST_PWM,SERVO_CHANNAL_CON,TIMER10_DIV_8,TIMER1A_INT_DISABLE|TIMER1B_INT_DISABLE};
	TIMER1_voidSetICR(20000);
	TIMER_voidInit(&t1);
}

void SERVO_voidSetAngle(u16 Copy_u16Angle)
{
	u32 Local_u32Angle=0;
	Local_u32Angle = Map(0,180,750,2499,Copy_u16Angle);
	if(SERVO_CHANNAL_CON<=3)
	TIMER1_voidSetChannelBCompMatch(Local_u32Angle);
	else if(SERVO_CHANNAL_CON<=12)
	TIMER1_voidSetChannelACompMatch(Local_u32Angle);

}


static u32 Map(u32 InMin,u32 InMax,u32 OutMin,u32 OutMax,u32 InVal)
{
	u32 Local=0;
	Local = (((InVal-InMin)*(OutMax-OutMin))/(InMax-InMin))+OutMin;
	return Local;
}
