/*
 * ADC_register.h
 *
 *  Created on: Jul 27, 2024
 *      Author: user
 */

#ifndef MCAL_ADC_REGISTER_H_
#define MCAL_ADC_REGISTER_H_


#define ADMUX 				*((volatile u8*)0x27)
#define ADMUX_REFS1         7
#define ADMUX_REFS0         6
#define ADMUX_ADLAR         5
#define ADMUX_MUX0			0

#define ADCSRA  			*((volatile u8*)0x26)
#define ADCSRA_ADEN			7
#define ADCSRA_ADSC			6
#define ADCSRA_ADATE		5
#define ADCSRA_ADIF		    4
#define ADCSRA_ADIE			3
#define ADCSRA_ADPS0		0

#define ADC_REG				*((volatile u16*)0x24)

#define SFIOR				*((volatile u16*)0x50)
#define SFIOR_ADTS0			5
#endif /* MCAL_ADC_REGISTER_H_ */
