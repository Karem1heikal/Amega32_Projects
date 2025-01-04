/*
 * EXTI_interface.h
 *
 *  Created on: Jul 23, 2024
 *      Author: user
 */

#ifndef MCAL_EXTI_INTERFACE_H_
#define MCAL_EXTI_INTERFACE_H_

#define EXTI0		0
#define EXTI1		1
#define EXTI2       2

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

void EXTI_voidInt0Init();
void EXTI_voidInt1Init();
void EXTI_voidInt2Init();

u8 EXTI_u8Int0CallBack(void (*Notification)());
u8 EXTI_u8Int1CallBack(void (*Notification)());
u8 EXTI_u8Int2CallBack(void (*Notification)());

u8 EXTI_u8Int0ChangeSence(u8 Copy_u8Sence);
u8 EXTI_u8Int1ChangeSence(u8 Copy_u8Sence);
u8 EXTI_u8Int2ChangeSence(u8 Copy_u8Sence);

u8 EXTI_u8IntDisable(u8 Copy_u8IntID);
u8 EXTI_u8IntEnable(u8 Copy_u8IntID);


#endif /* MCAL_EXTI_INTERFACE_H_ */
