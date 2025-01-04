/*********************************************************************************/
/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : MCAL         **********************************/
/************************* SWC    : DIO          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_interface.h"
#include "../MCAL/DIO_register.h"




u8 DIO_u8SetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	u8 Local_u8ErrorState=0;
	if(DIO_PIN_HIGH==Copy_u8Value)
	{
		if((0<=Copy_u8Pin)&&(Copy_u8Pin<=7))
		{
			switch(Copy_u8Port)
			{
				case DIO_PORTA:SET_BIT(PORTA,Copy_u8Pin);break;
				case DIO_PORTB:SET_BIT(PORTB,Copy_u8Pin);break;
				case DIO_PORTC:SET_BIT(PORTC,Copy_u8Pin);break;
				case DIO_PORTD:SET_BIT(PORTD,Copy_u8Pin);break;
				default: Local_u8ErrorState=1;				
			}
		}
		else
			Local_u8ErrorState=1;
	}
	else if(DIO_PIN_LOW==Copy_u8Value)
	{
		if((0<=Copy_u8Pin)&&(Copy_u8Pin<=7))
		{
			switch(Copy_u8Port)
			{
				case DIO_PORTA:CLR_BIT(PORTA,Copy_u8Pin);break;
				case DIO_PORTB:CLR_BIT(PORTB,Copy_u8Pin);break;
				case DIO_PORTC:CLR_BIT(PORTC,Copy_u8Pin);break;
				case DIO_PORTD:CLR_BIT(PORTD,Copy_u8Pin);break;
				default: Local_u8ErrorState=1;	
			}
		}
		else
			Local_u8ErrorState=1;	
	}
	else
		Local_u8ErrorState=1;	
	return Local_u8ErrorState;
}
u8 DIO_u8SetPortValue(u8 Copy_u8Port,u8 Copy_u8Value)
{
	u8 Local_u8ErrorState=0;
	if(Copy_u8Port<=7)
	{
		switch(Copy_u8Port)
		{
			case DIO_PORTA:PORTA=Copy_u8Value;break;
			case DIO_PORTB:PORTB=Copy_u8Value;break;
			case DIO_PORTC:PORTC=Copy_u8Value;break;
			case DIO_PORTD:PORTD=Copy_u8Value;break;
			default: Local_u8ErrorState=1;
		}
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 *Copy_pu8Value)
{
	u8 Local_u8ErrorState=0;
	if((0<=Copy_u8Pin)&&(Copy_u8Pin<=7))
	{
		switch(Copy_u8Port)
		{
			case DIO_PORTA:*Copy_pu8Value=GET_BIT(PINA,Copy_u8Pin);break;
			case DIO_PORTB:*Copy_pu8Value=GET_BIT(PINB,Copy_u8Pin);break;
			case DIO_PORTC:*Copy_pu8Value=GET_BIT(PINC,Copy_u8Pin);break;
			case DIO_PORTD:*Copy_pu8Value=GET_BIT(PIND,Copy_u8Pin);break;
			default: Local_u8ErrorState=1;	
		}
	}
	else
		Local_u8ErrorState=1;	
	return Local_u8ErrorState;
}
u8 DIO_u8TogglePinValue(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_u8ErrorState=0;
	if((0<=Copy_u8Pin)&&(Copy_u8Pin<=7))
	{
		switch(Copy_u8Port)
		{
			case DIO_PORTA:TOG_BIT(PORTA,Copy_u8Pin);break;
			case DIO_PORTB:TOG_BIT(PORTB,Copy_u8Pin);break;
			case DIO_PORTC:TOG_BIT(PORTC,Copy_u8Pin);break;
			case DIO_PORTD:TOG_BIT(PORTD,Copy_u8Pin);break;
			default: Local_u8ErrorState=1;
		}
	}
	else
		Local_u8ErrorState=1;
	return Local_u8ErrorState;
}

