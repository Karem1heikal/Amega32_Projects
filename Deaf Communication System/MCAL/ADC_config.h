/*
 * ADC_config.h
 *
 *  Created on: Jul 27, 2024
 *      Author: user
 */

#ifndef MCAL_ADC_CONFIG_H_
#define MCAL_ADC_CONFIG_H_

/*
 * Voltage Reference Selections for ADC
 * Options :
 * 		1-AREF 		==> AREF, Internal Vref turned off
 * 		2-AVCC 		==> AVCC with external capacitor at AREF pin
 * 		3-HALF_AVCC ==> Internal 2.56V Voltage Reference with external capacitor at AREF pin
 *
 * */

#define ADC_REF_VOLT		AVCC

/*
 * Select ADC Left Adjust Result
 * option:
 * 		1-LEFT_ADJUST  ==> Get result for _8_BIT_RESOLUTION
 * 		2-RIGHT_ADJUST ==> Get result for _10_BIT_RESOLUTION
 * */
#define ADC_ADJUST_BIT	LEFT_ADJUST
/*
 * Select prescaler of ADC Clock
 * options:
 *      1- DIV_2
 *      2- DIV_4
 *      3- DIV_8
 *      4- DIV_16
 *      5- DIV_32
 *      6- DIV_64
 *      7- DIV_128
 * */
#define ADC_CLK_RATE	DIV_64

#define ADC_AUTO_TRIGGER_MODE	ENABLE

#if ADC_AUTO_TRIGGER_MODE == ENABLE
/*
 * Select ADC Auto Trigger Source
 * option:
 * 		1-FREE_RUNNING_MODE   ==> Free Running mode
 * 		2-ANALOG_COMPARATOR   ==> Analog Comparator
 * 		3-EXT_INT0  		  ==>External Interrupt Request 0
 * 		4-TIMER0_COMP_MATCH   ==> Timer/Counter0 Compare Match
 * 		5-TIMER0_OVF          ==> Timer/Counter0 Overflow
 * 		6-TIMER1_COMP_MATCH_B ==> Timer/Counter1 Compare Match B
 * 		7-TIMER1_OVF          ==> Timer/Counter1 Overflow
 * 		8-TIMER1_CAPT_EVENT	  ==> Timer/Counter1 Capture Event
 *
 * */
#define	ADC_AUTO_TRIGGER_SRC	EXT_INT0

#define ADC_INTERRUPT_EN		ENABLE

#endif

#define ADC_U32_TIMEOUT		50000
#endif /* MCAL_ADC_CONFIG_H_ */
