/*
 * LED_interface.h
 *
 *  Created on: Jul 16, 2024
 *      Author: user
 */

#ifndef HAL_LED_INTERFACE_H_
#define HAL_LED_INTERFACE_H_


#define LED_SOUCE	1
#define LED_SINK	0

typedef struct
{
	u8 Port;
	u8 Pin;
	u8 ConnType;
}LED_t;

u8 LED_u8TurnOn(LED_t * Copy_LED);
u8 LED_u8TurnOff(LED_t * Copy_LED);
u8 LED_u8TogLed(LED_t *Copy_LED);



#endif /* HAL_LED_INTERFACE_H_ */
