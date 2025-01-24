/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : MCAL         **********************************/
/************************* SWC    : ADC          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
/*	ADC reference
 * CHIOCES				DESCRIPTION
 * ---------------------------------------------------------
 * AREF				| AREF, Internal Vref turned off
 * AVCC				| AVCC with external capacitor at AREF pin
 * Internal_HALF	| Internal 2.56V Voltage Reference with external capacitor at AREF pin
*/

#define ADC_INITAL_REF	AVCC

/* Receiving ADC values in Data register
 * Option  :
 * 			1-Right_adjust	for 10 Bit RESOLUTION
 * 			2-left_adjust	for 8 Bit RESOLUTION
 * */
#define ADC_ADJUST_DATA		left_adjust

/*  ADC Prescaler
 * -----------------------------------
 *  1-	DivBy_2
 *  2-	DivBy_2
 *  3-	DivBy_4
 *  4-	DivBy_8
 *  5-	DivBy_16
 *  6-	DivBy_32
 *  7-	DivBy_64
 *  8-	DivBy_128
 * */

#define ADC_DIV_FACTOR	DivBy_128


#define ADC_U32TIMEOUT		50000
//-----------------------------------
//-----------------------------------

#define ADC_AUTO_Channel	ADC1
#if ADC_Analog_Channel == ADC_AUTO_Channel
#error	"Don't make two mode of ADC in one channel"
#endif
/*
 * To Active auto trigger mode
 * Options :
 * 			1-Enable
 * 			2-Disable
 *
 * */

#define ADC_AUTO_TRIGGER		Disable
/*
 *   Free_Running_mode
 *   Analog_Comparator
 *   External_Interrupt_0
 *   Timer_Counter0_Compare_Match
 *   Timer_Counter0_Overflow
 *   Timer_Counter_Compare_Match_B
 *   Timer_Counter1_Overflow
 *   Timer_Counter1_Capture_Event
 * */

#define ADC_AUTO_TRIG_SOURCE	Free_Running_mode
#endif
