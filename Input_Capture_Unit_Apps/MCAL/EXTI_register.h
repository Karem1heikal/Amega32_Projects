/*
 * EXTI_register.h
 *
 *  Created on: Jul 23, 2024
 *      Author: user
 */

#ifndef MCAL_EXTI_REGISTER_H_
#define MCAL_EXTI_REGISTER_H_


#define MCUCR 			*((volatile u8*)0x55)
#define MCUCR_ISC11		3
#define MCUCR_ISC10		2
#define MCUCR_ISC01     1
#define MCUCR_ISC00		0


#define MCUCSR 			*((volatile u8*)0x54)
#define MCUCSR_ISC2		6

//$5B) GICR INT1 INT0 INT2

#define GICR 			*((volatile u8*)0x5B)
#define GICR_INT1 		7
#define GICR_INT0 		6
#define GICR_INT2		5

#define GIFR  			*((volatile u8*)0x5A)



#endif /* MCAL_EXTI_REGISTER_H_ */
