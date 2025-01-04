/*
 * USART_program.c
 *
 *  Created on: Jun 23, 2024
 *      Author: user
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/USART_private.h"
#include "../MCAL/USART_config.h"
#include "../MCAL/USART_register.h"
#include "../MCAL/USART_interface.h"


static void (*Global_pvCallBackFuncSend)() = NULL;
static u8 Global_u8SendChar;
static u8 Global_u8BusyFlag = IDLE;
static u8 Global_u8DirectionSend = SINGLE_CHER_SEND;
static char *Global_pcByteString = NULL ;

static u16 *Global_u16ReceiveChar = NULL;
static void (*Global_pvCallBackFuncRecv)() = NULL;
static u8 Global_u8DirectionRecv = SINGLE_CHER_RECV;
static u8 Global_u8RecvCharSize;
void USART_init()
{
	u8 Local_u8UCSRC_Value = 0;
	u16 Local_u16BaudValue;
	// set character size of the frame
	Local_u8UCSRC_Value &= CHAR_SIZE_MASK;
#if(CHARACTER_SIZE <= CHAR_SIZE_8_bit)
		// by default 8-bit data size
		CLR_BIT(UCSRB,UCSRB_UCSZ2);
		Local_u8UCSRC_Value |= CHARACTER_SIZE<<UCSRC_UCSZ0;
#elif(CHARACTER_SIZE == CHAR_SIZE_9_bit)
		SET_BIT(UCSRB,UCSRB_UCSZ2);
		Local_u8UCSRC_Value |= CHAR_SIZE_8_bit<<UCSRC_UCSZ0;
#endif
	// set parity bit of the frame
	Local_u8UCSRC_Value &= PARITY_MASK;
	Local_u8UCSRC_Value |= PARITY_MODE<<UCSRC_UPM0;
	// set stop bit of the frame
	STOP_MODE?SET_BIT(Local_u8UCSRC_Value,UCSRC_USBS):CLR_BIT(Local_u8UCSRC_Value,UCSRC_USBS);
#if SYNCH_MODE == ASYNCH
	// set synchronous mode
	CLR_BIT(Local_u8UCSRC_Value,UCSRC_UMSEL);
	// set speed mode and calculate Baud rate
	#if SPEED_MODE == NORMAL_SPEED
		CLR_BIT(UCSRA,UCSRA_U2X);
		Local_u16BaudValue = (u16)((CLOCK_SOURCE/(16UL*BAUD_RATE))-1UL);
	#elif SPEED_MODE == DOUBLE_SPEED
		SET_BIT(UCSRA,UCSRA_U2X);
		Local_u16BaudValue = (u16)((CLOCK_SOURCE/(8UL*BAUD_RATE))-1UL);
	#endif

#elif SYNCH_MODE == SYNCH
	SET_BIT(Local_u8UCSRC_Value,UCSRC_UMSEL);

	// set clock polarity
	CLK_POLARITY?SET_BIT(Local_u8UCSRC_Value,UCSRC_UCPOL):CLR_BIT(Local_u8UCSRC_Value,UCSRC_UCPOL);
	// calculate Baud rate
	#if SPEED_MODE == SYNCH_MASTER_SPEED
		Local_u16BaudValue = (u16)((CLOCK_SOURCE/(2UL*BAUD_RATE))-1UL);
	#endif
#else

#endif

	// select UCSRC register
	SET_BIT(Local_u8UCSRC_Value,UCSRC_URSEL);
	// set UCSRC register with current value
	UCSRC = Local_u8UCSRC_Value;
	// select UDRRH register
	CLR_BIT(Local_u8UCSRC_Value,UCSRC_URSEL);
	UBRRL = Local_u16BaudValue & 0xff;
	UBRRH = Local_u16BaudValue >> 8;
	// transmit and receive option
	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);

	/*
	SET_BIT(Local_u8UCSRC_Value,UCSRC_URSEL);


	// by default 8- bit data size
	Local_u8UCSRC_Value &= CHAR_SIZE_MASK;
	Local_u8UCSRC_Value |= CHARACTER_SIZE<<UCSRC_UCSZ0;

	UCSRC = Local_u8UCSRC_Value;

	UBRRL = 51;

	SET_BIT(UCSRB,UCSRB_TXEN);
	SET_BIT(UCSRB,UCSRB_RXEN);
	*/
}

u8 USART_u8SendPolling(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32counter = 0;

	// wait until trans buffer is empty
	while((GET_BIT(UCSRA,UCSRA_UDRE)==0)&&(Local_u32counter<USART_u32TIMEOUT))
	{
		Local_u32counter++;
	}
	if(Local_u32counter==USART_u32TIMEOUT)
	{
		Local_u8ErrorState =NOTOK;
	}
	else
	{
		CLR_BIT(UCSRB,UCSRB_TXB8);
		if(CHARACTER_SIZE == CHAR_SIZE_9_bit)
			SET_BIT(UCSRB,UCSRB_TXB8);
		UDR = Copy_u8Data;
	}
	return Local_u8ErrorState;
}

u8 USART_u8ReceivePolling(u16 *Copy_pu16Read)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32counter = 0;
	if(Copy_pu16Read==NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		while((GET_BIT(UCSRA,UCSRA_RXC)==0)&&(Local_u32counter<USART_u32TIMEOUT))
		{
			Local_u32counter++;
		}
		if(Local_u32counter==USART_u32TIMEOUT)
		{
			Local_u8ErrorState = NOTOK;
		}
		else{
			*Copy_pu16Read = UDR;
			if(GET_BIT(UCSRB,UCSRB_RXB8))
				*Copy_pu16Read |= 1<<8;
		}
	}
	return Local_u8ErrorState;
}

u8 USART_u8ReceivePollingWithOut(u16 *Copy_pu16Read)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_pu16Read==NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		while((GET_BIT(UCSRA,UCSRA_RXC)==0));
		*Copy_pu16Read = UDR;
		if(GET_BIT(UCSRB,UCSRB_RXB8))
			*Copy_pu16Read |= 1<<8;
	}
	return Local_u8ErrorState;
}

u8 USART_u8SendStringPoll(const char* Copy_pcString)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8counter = 0;
	if(Copy_pcString==NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		while(Copy_pcString[Local_u8counter]!='\0')
		{
			USART_u8SendPolling(Copy_pcString[Local_u8counter]);
			Local_u8counter++;
		}
	}
	return Local_u8ErrorState;
}
u8 USART_u8ReceiveBufferPollWithOut(char* Copy_pcString,u8 Copy_u8BufferSize)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8counter = 0;
	if(Copy_pcString==NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		for(Local_u8counter=0;Local_u8counter<Copy_u8BufferSize;Local_u8counter++)
		{
			USART_u8ReceivePollingWithOut((u16*)(Copy_pcString+Local_u8counter));
			if(Local_u8counter>=2)
			{
			//if(('e'==Copy_pcString[Local_u8counter])&&('n'==Copy_pcString[Local_u8counter-1])&&('o'==Copy_pcString[Local_u8counter-2])&&('d'==Copy_pcString[Local_u8counter-3]))
			//	break;
			if(('n'==Copy_pcString[Local_u8counter])&&('o'==Copy_pcString[Local_u8counter-1]))
				break;
			else if(('f'==Copy_pcString[Local_u8counter])&&('f'==Copy_pcString[Local_u8counter-1])&&('o'==Copy_pcString[Local_u8counter-2]))
				break;
			else if(('y'==Copy_pcString[Local_u8counter])&&('a'==Copy_pcString[Local_u8counter-1])&&('l'==Copy_pcString[Local_u8counter-2])&&('p'==Copy_pcString[Local_u8counter-3]))
				break;
			else if(('p'==Copy_pcString[Local_u8counter])&&('o'==Copy_pcString[Local_u8counter-1])&&('t'==Copy_pcString[Local_u8counter-2])&&('s'==Copy_pcString[Local_u8counter-3]))
				break;
			else if(('t'==Copy_pcString[Local_u8counter])&&('s'==Copy_pcString[Local_u8counter-1])&&('u'==Copy_pcString[Local_u8counter-2])&&('j'==Copy_pcString[Local_u8counter-3])&&('d'==Copy_pcString[Local_u8counter-4])&&('a'==Copy_pcString[Local_u8counter-5]))
				break;
			else if(('e'==Copy_pcString[Local_u8counter])&&('s'==Copy_pcString[Local_u8counter-1])&&('o'==Copy_pcString[Local_u8counter-2])&&('l'==Copy_pcString[Local_u8counter-3])&&('c'==Copy_pcString[Local_u8counter-4]))
				break;
			else if(('n'==Copy_pcString[Local_u8counter])&&('e'==Copy_pcString[Local_u8counter-1])&&('p'==Copy_pcString[Local_u8counter-2])&&('o'==Copy_pcString[Local_u8counter-3]))
				break;
			}

		}
		Copy_pcString[Local_u8counter+1]='\0';
	}
	return Local_u8ErrorState;

}
u8 USART_u8ReceiveBufferPoll(char* Copy_pcString,u8 Copy_u8BufferSize)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8counter = 0;
	if(Copy_pcString==NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		for(Local_u8counter=0;Local_u8counter<Copy_u8BufferSize;Local_u8counter++)
		{
			USART_u8ReceivePolling((u16*)(Copy_pcString+Local_u8counter));
			if(0x0D==Copy_pcString[Local_u8counter])
				break;
		}
		Copy_pcString[Local_u8counter]='\0';
	}
	return Local_u8ErrorState;
}

u8 USART_u8SendCharInt(u8 Copy_u8Data,void(*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if(Notification==NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		if(Global_u8BusyFlag==IDLE)
		{
			Global_u8BusyFlag = BUSY;
			Global_u8DirectionSend = SINGLE_CHER_SEND;
			Global_u8SendChar = Copy_u8Data;
			Global_pvCallBackFuncSend = Notification;
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_FUNC;
		}
	}
	return Local_u8ErrorState;

}
u8 USART_u8SendStringInt(char* Copy_pcString,void(*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if((Notification==NULL)||(Copy_pcString==NULL))
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		if(Global_u8BusyFlag==IDLE)
		{
			Global_u8BusyFlag = BUSY;
			Global_u8DirectionSend = MULTI_CHER_SEND;
			Global_pcByteString = Copy_pcString;
			Global_pvCallBackFuncSend = Notification;
			SET_BIT(UCSRB,UCSRB_UDRIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_FUNC;
		}
	}
	return Local_u8ErrorState;
}
u8 USART_u8ReceiveCharInt(u16 *Copy_pu16Read,void(*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if((Notification==NULL)||(Copy_pu16Read==NULL))
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		if(Global_u8BusyFlag==IDLE)
		{
			Global_u8BusyFlag = BUSY;
			Global_u8DirectionRecv = SINGLE_CHER_RECV;
			Global_u16ReceiveChar = Copy_pu16Read;
			Global_pvCallBackFuncRecv = Notification;
			SET_BIT(UCSRB,UCSRB_RXCIE);
		}
		else
			Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
u8 USART_u8ReceiveBufferInt(char *Copy_pcString,u8 Copy_u8BufferSize,void(*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if((Notification==NULL)||(Copy_pcString==NULL))
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		if(Global_u8BusyFlag==IDLE)
		{
			Global_u8BusyFlag = BUSY;
			Global_u8DirectionRecv = MULTI_CHER_RECV;
			Global_u8RecvCharSize = Copy_u8BufferSize;
			Global_pcByteString = Copy_pcString;
			Global_pvCallBackFuncRecv = Notification;
			SET_BIT(UCSRB,UCSRB_RXCIE);
		}
		else
			Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
void __vector_14 (void)	__attribute__((signal));
void __vector_14 (void)
{
	if(SINGLE_CHER_SEND==Global_u8DirectionSend)
	{

		CLR_BIT(UCSRB,UCSRB_TXB8);
		if(CHARACTER_SIZE == CHAR_SIZE_9_bit)
			SET_BIT(UCSRB,UCSRB_TXB8);
		UDR = Global_u8SendChar;
		Global_pvCallBackFuncSend();
		Global_u8BusyFlag = IDLE;
	}
	else if(MULTI_CHER_SEND==Global_u8DirectionSend)
	{
		static u8 Local_u8Counter = 0;
		if(Global_pcByteString[Local_u8Counter]=='\0')
		{
			Global_pvCallBackFuncSend();
			Global_u8BusyFlag = IDLE;
			CLR_BIT(UCSRB,UCSRB_UDRIE);
			Local_u8Counter = 0;
		}
		else
		{
			CLR_BIT(UCSRB,UCSRB_TXB8);
			if(CHARACTER_SIZE == CHAR_SIZE_9_bit)
				SET_BIT(UCSRB,UCSRB_TXB8);
			UDR = Global_pcByteString[Local_u8Counter];
			Local_u8Counter++;
		}

	}

}

void __vector_13 (void)	__attribute__((signal));
void __vector_13 (void)
{
	if(SINGLE_CHER_RECV == Global_u8DirectionRecv)
	{
		*Global_u16ReceiveChar = UDR;
		if(GET_BIT(UCSRB,UCSRB_RXB8))
			*Global_u16ReceiveChar |= 1<<8;
			Global_pvCallBackFuncRecv();
	}
	else if(MULTI_CHER_RECV == Global_u8DirectionRecv)
	{
		static u8 Local_u8Counter = 0;
		if((Global_u8RecvCharSize-1)==Local_u8Counter)
		{
			Global_pvCallBackFuncRecv();
			Global_u8BusyFlag = IDLE;
			CLR_BIT(UCSRB,UCSRB_RXCIE);
			Local_u8Counter = 0;
		}
		else
		{
			Global_pcByteString[Local_u8Counter] = UDR;
			if(GET_BIT(UCSRB,UCSRB_RXB8))
				Global_pcByteString[Local_u8Counter] |= 1<<8;
			Local_u8Counter++;
		}
	}
}

