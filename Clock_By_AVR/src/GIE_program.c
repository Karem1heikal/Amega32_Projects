/*
 * GIE_program.c
 *
 *  Created on: Jul 23, 2024
 *      Author: user
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/GIE_interface.h"
#include "../MCAL/GIE_register.h"


void GIE_voidEnable()
{
	SET_BIT(SREG,SREG_I);
}

void GIE_voidDisable()
{
	CLR_BIT(SREG,SREG_I);
}
