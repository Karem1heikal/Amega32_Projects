/*
 * SW_interface.h
 *
 *  Created on: Jul 16, 2024
 *      Author: user
 */

#ifndef HAL_SW_INTERFACE_H_
#define HAL_SW_INTERFACE_H_
typedef struct
{
	u8 Port;
	u8 Pin;
	u8 Pulltype;
	u8 SelfLockType;
	void (*Notification)();
} SW_t;


#define SW_PULL_UP			0
#define SW_PULL_DOWN		1

#define SW_NOT_SELF_LOCK	0
#define SW_SELF_LOCK		1
u8 SW_u8GetState(SW_t* Copy_SW,u8 *Copy_u8State);
u8 SW_u8GetState2(SW_t* Copy_SW,u8 *Copy_u8State);
#define SW_PRESSED			0
#define SW_NOT_PRESSED		1

#endif /* HAL_SW_INTERFACE_H_ */
