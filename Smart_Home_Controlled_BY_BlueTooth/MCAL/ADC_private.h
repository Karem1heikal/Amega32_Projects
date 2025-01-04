/*
 * ADC_private.h
 *
 *  Created on: Jul 27, 2024
 *      Author: user
 */

#ifndef MCAL_ADC_PRIVATE_H_
#define MCAL_ADC_PRIVATE_H_

#define AREF 				0
#define AVCC 				1
#define HALF_AVCC			3

#define MASK_AREF			0x3f

#define MASK_CHANNEL		0xe0

#define MAX_OPTION_CHANNEL 31

#define LEFT_ADJUST 		1
#define RIGHT_ADJUST		0

#define DIV_2               1
#define DIV_4               2
#define DIV_8               3
#define DIV_16              4
#define DIV_32              5
#define DIV_64              6
#define DIV_128             7

#define MASK_CLK_RATE		0xf8

#define ENABLE 		1
#define DISABLE		2

#define FREE_RUNNING_MODE     0
#define ANALOG_COMPARATOR     1
#define EXT_INT0  		      2
#define TIMER0_COMP_MATCH     3
#define TIMER0_OVF            4
#define TIMER1_COMP_MATCH_B   5
#define TIMER1_OVF            6
#define TIMER1_CAPT_EVENT	  7

#define MASK_AUTO_TRIGGER  0X1F

#define IDLE	0
#define BUSY	1

#define SINGLE_CONVERISION		0
#define CHAIN_CONVERISION		1
#endif /* MCAL_ADC_PRIVATE_H_ */
