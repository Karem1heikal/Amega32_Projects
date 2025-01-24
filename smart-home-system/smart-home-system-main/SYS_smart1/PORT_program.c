/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : MCAL         **********************************/
/************************* SWC    : PORT          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PORT_private.h"
#include "PORT_config.h"
#include "PORT_register.h"
#include "PORT_interface.h"

void PORT_voidInit()
{
	DDRA = PORTA_DIR;	
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;
	
	PORTA =PORTA_INIT_VALUE;
	PORTB =PORTB_INIT_VALUE;
	PORTC =PORTC_INIT_VALUE;
	PORTD =PORTD_INIT_VALUE;
	
}