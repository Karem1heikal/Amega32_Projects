/*
 * main.c
 *
 *  Created on: Jun 28, 2024
 *      Author: user
 */

#include <util/delay.h>


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/PORT_interface.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/semphr.h"


void Led1Tog(void *Copy_pvSt);
void Led2Tog(void *Copy_pvSt);
void Led3Tog(void *Copy_pvSt);

void main(){
	PORT_voidInit();

	xTaskCreate(&Led1Tog,NULL,100,NULL,0,NULL);
	xTaskCreate(&Led2Tog,NULL,100,NULL,1,NULL);
	xTaskCreate(&Led3Tog,NULL,100,NULL,3,NULL);

	vTaskStartScheduler();

	while(1);
}
void Led1Tog(void *Copy_pvSt)
{
	//LED_u8TogLed(&led[0]);

	static u8 Local_u8State = 0;
	while(1)
	{
		TOG_BIT(Local_u8State,0);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN5,Local_u8State);
		vTaskDelay(1000);
	}
}

void Led2Tog(void *Copy_pvSt)
{
	//LED_u8TogLed(&led[1]);
	static u8 Local_u8State = 0;
	while(1)
	{
		TOG_BIT(Local_u8State,0);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN6,Local_u8State);
		vTaskDelay(2000);
	}
}
void Led3Tog(void *Copy_pvSt)
{
	//LED_u8TogLed(&led[2]);
	static u8 Local_u8State = 0;
	while(1)
	{
		TOG_BIT(Local_u8State,0);
		DIO_u8SetPinValue(DIO_PORTA,DIO_PIN7,Local_u8State);
		vTaskDelay(3000);
	}

}
