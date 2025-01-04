/*
 * TIMER_register.h
 *
 *  Created on: Aug 7, 2024
 *      Author: user
 */

#ifndef MCAL_TIMER_REGISTER_H_
#define MCAL_TIMER_REGISTER_H_

#define OCR0			*((volatile u8*)0x5C)

#define TCNT0			*((volatile u8*)0x52)

#define TCCR0			*((volatile u8*)0x53)
#define TCCR0_FOC0		7
#define TCCR0_WGM00		6
#define TCCR0_COM00		4
#define TCCR0_WGM01		3
#define TCCR0_CS00		0

#define TIFR			*((volatile u8*)0x58)
#define TIFR_OCF0		1
#define TIFR_TOV0		0

#define TIMSK			*((volatile u8*)0x59)
#define TIMSK_OCIE2		7
#define TIMSK_TOIE2		6
#define TIMSK_TICIE1	5
#define TIMSK_OCIE1A	4
#define TIMSK_OCIE1B	3
#define TIMSK_TOIE1		2
#define TIMSK_OCIE0		1
#define TIMSK_TOIE0		0

// prescaler reset register
#define SFIOR			*((volatile u8*)0x50)
#define SFIOR_PSR2		1
#define SFIOR_PSR10		0


#define TCCR1A					*((volatile u8*)0x4F)
#define TCCR1A_COM1A0			6
#define TCCR1A_COM1B0			4
#define TCCR1A_FOC1A			3
#define TCCR1A_FOC1B			2
#define TCCR1A_WGM10			0


#define TCCR1B					*((volatile u8*)0x4E)
#define TCCR1B_ICNC1			7
#define TCCR1B_ICES1			6
#define TCCR1B_WGM12			3
#define TCCR1B_CS10				0

#define TCNT1					*((volatile u16*)0x4C)
#define OCR1A					*((volatile u16*)0x4A)
#define OCR1B					*((volatile u16*)0x48)
#define ICR1					*((volatile u16*)0x46)


#define TCCR2					*((volatile u8*)0x45)
#define TCCR2_FOC2				7
#define TCCR2_WGM20				6
#define TCCR2_COM20				4
#define TCCR2_WGM21				3
#define TCCR2_CS20				0


#define TCNT2					*((volatile u8*)0x44)
#define OCR2					*((volatile u8*)0x43)


#define ASSR					*((volatile u8*)0x42)
#define ASSR_AS2                3
#define ASSR_TCN2UB             2
#define ASSR_OCR2UB             1
#define ASSR_TCR2UB				0

#endif /* MCAL_TIMER_REGISTER_H_ */
