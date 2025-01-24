/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : MCAL         **********************************/
/************************* SWC    : ADC          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
#define AREF			1
#define AVCC			2
#define Internal_HALF	3

#define Right_adjust	1
#define left_adjust		2
//------------------------
#define DivBy_2    0
#define DivBy_4    2
#define DivBy_8    3
#define DivBy_16   4
#define DivBy_32   5
#define DivBy_64   6
#define DivBy_128  7

#define	ADCSRA_MASK		0b11111000
//------------------------------------
#define ADC0            0b00000
#define ADC1            0b00001
#define ADC2            0b00010
#define ADC3            0b00011
#define ADC4            0b00100
#define ADC5            0b00101
#define ADC6            0b00110
#define ADC7            0b00111
#define ADC0_ADC0_10x   0b01000
#define ADC1_ADC0_10x   0b01001
#define ADC0_ADC0_200x  0b01010
#define ADC1_ADC0_200x  0b01011
#define ADC2_ADC2_10x   0b01100
#define ADC3_ADC2_10x   0b01101
#define ADC2_ADC2_200x  0b01110
#define ADC3_ADC2_200x  0b01111
#define ADC0_ADC1_1x    0b10000
#define ADC1_ADC1_1x    0b10001
#define ADC2_ADC1_1x    0b10010
#define ADC3_ADC1_1x    0b10011
#define ADC4_ADC1_1x    0b10100
#define ADC5_ADC1_1x    0b10101
#define ADC6_ADC1_1x    0b10110
#define ADC7_ADC1_1x    0b10111
#define ADC0_ADC2_1x    0b11000
#define ADC1_ADC2_1x    0b11001
#define ADC2_ADC2_1x    0b11010
#define ADC3_ADC2_1x    0b11011
#define ADC4_ADC2_1x    0b11100
#define ADC5_ADC2_1x    0b11101
#define VBG1_22V 		0b11110
#define V_GND			0b11111

#define	ADMUX_MASK		0b11100000
//-------------------------------------

#define Free_Running_mode              0b00000000
#define Analog_Comparator              0b00100000
#define External_Interrupt_0           0b01000000
#define Timer_Counter0_Compare_Match   0b01100000
#define Timer_Counter0_Overflow        0b10000000
#define Timer_Counter_Compare_Match_B  0b10100000
#define Timer_Counter1_Overflow        0b11000000
#define Timer_Counter1_Capture_Event   0b11100000

#define SFIOR_MASK	0b00011111
#define Enable 		1
#define Disable		2

#define IDLE	0
#define Busy	1

#define SINGLE_CHANNEL_ASYNCH	0;
#define CHAIN_CHANNEL_ASYNCH	1;

#endif
