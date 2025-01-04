/*
 * EXTI_private.h
 *
 *  Created on: Jul 23, 2024
 *      Author: user
 */

#ifndef MCAL_EXTI_PRIVATE_H_
#define MCAL_EXTI_PRIVATE_H_


#define MASK_SENCE_INT0		0xFC
#define MASK_SENCE_INT1		0xF3
#define MASK_SENCE_INT2		0xBF

#define EXTI0_LOW_LEVEL 		0
#define EXTI0_ON_CHANGE 		1
#define EXTI0_FALLING_ADGE      2
#define EXTI0_RISING_ADGE       3

#define EXTI1_LOW_LEVEL 		0
#define EXTI1_ON_CHANGE 		1
#define EXTI1_FALLING_ADGE      2
#define EXTI1_RISING_ADGE       3

#define EXTI2_FALLING_ADGE      0
#define EXTI2_RISING_ADGE       1



#define EXTI0		0
#define EXTI1		1
#define EXTI2       2
#endif /* MCAL_EXTI_PRIVATE_H_ */
