/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : MCAL         **********************************/
/************************* SWC    : PORT          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/PORT_private.h"
#include "../MCAL/PORT_config.h"
#include "../MCAL/PORT_register.h"
#include "../MCAL/PORT_interface.h"

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
