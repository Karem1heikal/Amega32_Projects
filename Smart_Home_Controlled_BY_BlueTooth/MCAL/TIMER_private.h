/*
 * TIMER_private.h
 *
 *  Created on: Aug 7, 2024
 *      Author: user
 */

#ifndef MCAL_TIMER_PRIVATE_H_
#define MCAL_TIMER_PRIVATE_H_


#define MASK_COMP_MATCH_MODE	0xCF

#define MASK_CLOCK_MODE	0xF8

#define TIMER0_OVF		0
#define TIMER0_CMV		1
#define TIMER1_OVF		2
#define TIMER1A_CMV		3
#define TIMER1B_CMV		4
#define TIMER1_CAPT		5
#define TIMER2_OVF		6
#define TIMER2_CMV		7

#define MASK_TIMER1A_MODE	0xFC
#define MASK_TIMER1B_MODE	0xE7

#define MASK_TIMER1B_MODE_VAL	0xF3


#define MASK_COMP_MATCH1A_MODE	0x0F


#endif /* MCAL_TIMER_PRIVATE_H_ */
