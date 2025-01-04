/*
 * EXTI_interface.h
 *
 *  Created on: Jul 23, 2024
 *      Author: user
 */

#ifndef MCAL_EXTI_INTERFACE_H_
#define MCAL_EXTI_INTERFACE_H_


void EXTI_voidInt0Init();
void EXTI_voidInt1Init();
void EXTI_voidInt2Init();

u8 EXTI_u8Int0CallBack(void (*Notification)());
u8 EXTI_u8Int1CallBack(void (*Notification)());
u8 EXTI_u8Int2CallBack(void (*Notification)());

u8 EXTI_voidInt0ChangeSence(u8 Copy_u8Sence);
u8 EXTI_voidInt1ChangeSence(u8 Copy_u8Sence);
u8 EXTI_voidInt2ChangeSence(u8 Copy_u8Sence);

#endif /* MCAL_EXTI_INTERFACE_H_ */
