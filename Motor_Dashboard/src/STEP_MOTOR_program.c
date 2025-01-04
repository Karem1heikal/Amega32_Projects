/*
 * STEP_MOTOR_program.c
 *
 *  Created on: Jul 19, 2024
 *      Author: user
 */

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_interface.h"
#include "../HAL/STEP_MOTOR_config.h"
#include "../HAL/STEP_MOTOR_private.h"
#include "../HAL/STEP_MOTOR_interface.h"
#include "../HAL/CLCD_interface.h"
u8 STEP_MOTORu8StartFullMode(STEP_t *Copy_pStep)
{
	u8 Local_u8ErrorState = OK;
	u16 Local_u16NumOfSteps = (u16)((((f32)Copy_pStep->AngleDegree)/11.2)*64.0);
	u16 Local_u16MaxItration = (Local_u16NumOfSteps/MAX_FULL_STEP );
	u16 Local_u16Counter = 0;
	u8 Local_u8ItrateStep = 0;
	if(STEP_LOWER_NIBBLE == Copy_pStep->Nibble)
	{
		if(Copy_pStep->Diraction == STEP_CLOCKWISE)
		{
			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				for(Local_u8ItrateStep = 0;Local_u8ItrateStep<MAX_FULL_STEP ;Local_u8ItrateStep++)
				{
					DIO_u8SetLowNibbleValue(Copy_pStep->Port,(MASK_CW<<Local_u8ItrateStep));
					_delay_ms(2);
				}
			}
		}
		else if(Copy_pStep->Diraction == STEP_COUNTER_CLOCKWISE)
		{
			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				for(Local_u8ItrateStep = 0;Local_u8ItrateStep<MAX_FULL_STEP ;Local_u8ItrateStep++)
				{
					DIO_u8SetLowNibbleValue(Copy_pStep->Port,(MASK_CCW>>Local_u8ItrateStep));
					_delay_ms(2);
				}
			}
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else if(STEP_UPPER_NIBBLE == Copy_pStep->Nibble)
	{
		if(Copy_pStep->Diraction == STEP_CLOCKWISE)
		{
			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				for(Local_u8ItrateStep = 0;Local_u8ItrateStep<MAX_FULL_STEP ;Local_u8ItrateStep++)
				{
					DIO_u8SetHighNibbleValue(Copy_pStep->Port,(MASK_CW<<Local_u8ItrateStep));
					_delay_ms(2);
				}
			}
		}
		else if(Copy_pStep->Diraction == STEP_COUNTER_CLOCKWISE)
		{
			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				for(Local_u8ItrateStep = 0;Local_u8ItrateStep<MAX_FULL_STEP ;Local_u8ItrateStep++)
				{
					DIO_u8SetHighNibbleValue(Copy_pStep->Port,(MASK_CCW>>Local_u8ItrateStep));
					_delay_ms(2);
				}
			}
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}

u8 STEP_MOTORu8StartHalfMode(STEP_t *Copy_pStep)
{
	u8 Local_u8ErrorState = OK;
	u16 Local_u16Counter=0;
	u16 Local_u16NumOfSteps = (u16)((((f32)Copy_pStep->AngleDegree)/5.625)*64.0);
	u16 Local_u16MaxItration = Local_u16NumOfSteps/8;
	u8 Local_u8ItrateStep = 0,con1,con2 ;
	if(STEP_LOWER_NIBBLE == Copy_pStep->Nibble)
	{
		if(Copy_pStep->Diraction == STEP_CLOCKWISE)
		{

			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				con1 = 0x01;
				con2 = 0x03;
				for(Local_u8ItrateStep = 1;Local_u8ItrateStep<=MAX_HALF_STEP;Local_u8ItrateStep++)
				{

					if(Local_u8ItrateStep%2==1)
					{
						DIO_u8SetLowNibbleValue(Copy_pStep->Port,con1);
						con1<<=1;
					}
					else
					{
						DIO_u8SetLowNibbleValue(Copy_pStep->Port,con2);
						con2 = RotateLeftLowNibble(con2);
					}
					_delay_ms(2);
				}
			}
		}
		else if(Copy_pStep->Diraction == STEP_COUNTER_CLOCKWISE)
		{

			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				con1 = 0x08;
				con2 = 0x0c;
				for(Local_u8ItrateStep = 1;Local_u8ItrateStep<=MAX_HALF_STEP;Local_u8ItrateStep++)
				{

					if(Local_u8ItrateStep%2==1)
					{
						DIO_u8SetLowNibbleValue(Copy_pStep->Port,con1);
						con1>>=1;
					}
					else
					{
						DIO_u8SetLowNibbleValue(Copy_pStep->Port,con2);
						con2 = RotateRightLowNibble(con2);
					}
					_delay_ms(2);
				}
			}
		}

	}
	else if(STEP_UPPER_NIBBLE == Copy_pStep->Nibble)
	{

		if(Copy_pStep->Diraction == STEP_CLOCKWISE)
		{

			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				con1 = 0x01;
				con2 = 0x03;
				for(Local_u8ItrateStep = 1;Local_u8ItrateStep<=MAX_HALF_STEP;Local_u8ItrateStep++)
				{

					if(Local_u8ItrateStep%2==1)
					{
						DIO_u8SetHighNibbleValue(Copy_pStep->Port,con1);
						con1<<=1;
					}
					else
					{
						DIO_u8SetHighNibbleValue(Copy_pStep->Port,con2);
						CLCD_voidWriteNumber(con2);
						CLCD_voidSendData(' ');
						con2 = RotateLeftLowNibble(con2);

					}
					_delay_ms(2);
				}
			}
		}
		else if(Copy_pStep->Diraction == STEP_COUNTER_CLOCKWISE)
		{

			for(Local_u16Counter = 0; Local_u16Counter<Local_u16MaxItration;Local_u16Counter++)
			{
				con1 = 0x08;
				con2 = 0x0c;
				for(Local_u8ItrateStep = 1;Local_u8ItrateStep<=MAX_HALF_STEP;Local_u8ItrateStep++)
				{

					if(Local_u8ItrateStep%2==1)
					{
						DIO_u8SetHighNibbleValue(Copy_pStep->Port,con1);
						con1>>=1;
					}
					else
					{
						DIO_u8SetHighNibbleValue(Copy_pStep->Port,con2);
						con2 = RotateRightLowNibble(con2);
					}
					_delay_ms(2);
				}
			}
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}

void STEP_MOTORvStop(STEP_t *Copy_pStep)
{
	if(STEP_LOWER_NIBBLE == Copy_pStep->Nibble)
	{
		DIO_u8SetLowNibbleValue(Copy_pStep->Port,0);
	}
	else if(STEP_UPPER_NIBBLE == Copy_pStep->Nibble)
	{
		DIO_u8SetHighNibbleValue(Copy_pStep->Port,0);
	}
}


static u8 RotateRightLowNibble(u8 Val)
{
	u8 Local_xVal = 0;
	Local_xVal = GET_BIT(Val,0);
	Val>>=1;
	Local_xVal?SET_BIT(Val,3):CLR_BIT(Val,3);
	return Val;
}

static u8 RotateLeftLowNibble(u8 Val)
{
	u8 Local_xVal = 0;
	Local_xVal = GET_BIT(Val,3);
	Val<<=1;
	Local_xVal?SET_BIT(Val,0):CLR_BIT(Val,0);
	return Val;
}
