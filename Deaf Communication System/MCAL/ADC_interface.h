/*
 * ADC_interface.h
 *
 *  Created on: Jul 27, 2024
 *      Author: user
 */

#ifndef MCAL_ADC_INTERFACE_H_
#define MCAL_ADC_INTERFACE_H_


/*
 * Analog Channel and Gain Selection Bits
 * 	Single ended Channel options :
 * 00000 ADC0
 * 00001 ADC1
 * 00010 ADC2
 * 00011 ADC3
 * 00100 ADC4
 * 00101 ADC5
 * 00110 ADC6
 * 00111 ADC7
 *  Differential Channel options :
 * 01000 ADC0 ADC0 10x
 * 01001 ADC1 ADC0 10x
 * 01010 ADC0 ADC0 200x
 * 01011 ADC1 ADC0 200x
 * 01100 ADC2 ADC2 10x
 * 01101 ADC3 ADC2 10x
 * 01110 ADC2 ADC2 200x
 * 01111 ADC3 ADC2 200x
 * 10000 ADC0 ADC1 1x
 * 10001 ADC1 ADC1 1x
 * ----
 * other option in data sheet
 * */

#define ADC0              0
#define ADC1              1
#define ADC2              2
#define ADC3              3
#define ADC4              4
#define ADC5              5
#define ADC6              6
#define ADC7              7
#define ADC0_ADC0_10x     8
#define ADC1_ADC0_10x     9
#define ADC0_ADC0_200x    10
#define ADC1_ADC0_200x    11
#define ADC2_ADC2_10x     12
#define ADC3_ADC2_10x     13
#define ADC2_ADC2_200x    14
#define ADC3_ADC2_200x    15
#define ADC0_ADC1_1x      16
#define ADC1_ADC1_1x      17

typedef struct
{
	u8* ChainId;
	u8 ChannelSize;
	void (* Notifction)();
	u16* Result;
} ADC_Chain;

void ADC_voidInit();

u8 ADC_u8StartSingleConvPoll(u8 Copy_u8Channel,u16 *Copy_pu16Read);

u8 ADC_u8StartSingleConvInt(u8 Copy_u8Channel,u16 *Copy_pu16Read,void (*Notifiction)());

u8 ADC_u8StartChainConvAsynch(ADC_Chain *Copy_ADC);
#endif /* MCAL_ADC_INTERFACE_H_ */
