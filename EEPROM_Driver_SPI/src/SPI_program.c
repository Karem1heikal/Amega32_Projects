/*
 * SPI_program.c
 *
 *  Created on: Jul 10, 2024
 *      Author: user
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/SPI_register.h"
#include "../MCAL/SPI_private.h"
#include "../MCAL/SPI_config.h"
#include "../MCAL/SPI_interface.h"


static u8 SPI_u8BusyFlag = IDLE;

static void (*SPI_CallBackFunc)() = NULL;
static void (*SPI_CallBackBuffFunc)() = NULL;

static u8 *SPI_u8RecvData = NULL ;
static u8 SPI_u8Index = 0 ;
static u8 *SPI_u8SendDataBuff = NULL ;
static u8 *SPI_u8RecvDataBuff = NULL ;
static u8 SPI_u8BufferSize;
static u8 SPI_u8Direction = SPI_SINGLE_CHAR;

void SPI_voidMasterInit()
{
	// Set master mode
	SET_BIT(SPCR,SPCR_MSTR);
	// Set Order of data bits
	SPI_DATA_ORDER?SET_BIT(SPCR,SPCR_DORD):CLR_BIT(SPCR,SPCR_DORD);
	// Set Clk polarity and Clk Phase
	SPCR &= CLK_POL_PHA_MASK;
	SPCR |=	SPI_MODE << SPCR_CPHA;
	// prescaler of Clock
	SPCR &= CLK_PRE_MASK;
	((CLK_2<=SPI_CLOCK_PRE)&&(SPI_CLOCK_PRE<=CLK_32))?SET_BIT(SPSR,SPSR_SPI2X):CLR_BIT(SPSR,SPSR_SPI2X);
	SPCR |= (SPI_CLOCK_PRE & (~CLK_PRE_MASK));
	// Enable SPI
	SET_BIT(SPCR,SPCR_SPE);
}

void SPI_voidSlaveInit()
{
	// Set slave mode
	CLR_BIT(SPCR,SPCR_MSTR);
	// Enable SPI
	SET_BIT(SPCR,SPCR_SPE);
}

u8 SPI_u8MasterSendPolling(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32Counter = 0;
	if(SPI_u8BusyFlag == IDLE)
	{
		SPI_u8BusyFlag = BUSY;
		SPDR = Copy_u8Data;
		while((GET_BIT(SPSR,SPSR_SPIF)==0)&&(Local_u32Counter<SPI_u32TIMEOUT))
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter==SPI_u32TIMEOUT)
		{
			// Nothing
			Local_u8ErrorState = NOTOK;
		}
		SPI_u8BusyFlag = IDLE;
	}
	else {
		Local_u8ErrorState = BUSY_FUNC;
	}

	return Local_u8ErrorState;
}

u8 SPI_u8TransceivePolling(u8 Copy_u8Data,u8* Copy_pu8Read)
{
	u8 Local_u8ErrorState = 0;
	u32 Local_u32counter = 0;
	if(Copy_pu8Read!=NULL)
	{
		if(SPI_u8BusyFlag == IDLE)
		{
			SPI_u8BusyFlag = BUSY;
			SPDR = Copy_u8Data;
			while(((GET_BIT(SPSR,SPSR_SPIF)==0))&&(Local_u32counter<SPI_u32TIMEOUT))
			{
				Local_u32counter++;
			}
			if(Local_u32counter==SPI_u32TIMEOUT)
			{
				Local_u8ErrorState = NOTOK;
			}
			else
				*Copy_pu8Read = SPDR;
			SPI_u8BusyFlag = IDLE;
		}
		else
			Local_u8ErrorState = BUSY_FUNC;
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}
u8 SPI_u8MasterRecvPolling(u8 *Copy_pu8Read)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32Counter = 0;
	if(Copy_pu8Read != NULL)
	{
		if(SPI_u8BusyFlag == IDLE)
		{
			SPI_u8BusyFlag = BUSY;
			SPDR = SPI_DUMY_VALUE;
			while((GET_BIT(SPSR,SPSR_SPIF)==0)&&(Local_u32Counter<SPI_u32TIMEOUT));
			if(Local_u32Counter==SPI_u32TIMEOUT)
			{
				// Nothing
				Local_u8ErrorState =NOTOK;
			}
			else
			{
				*Copy_pu8Read = SPDR;
			}
			SPI_u8BusyFlag = IDLE;
		}
		else
			Local_u8ErrorState = BUSY_FUNC;
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}

u8 SPI_u8BufferTransceiveSynch(u8* Copy_u8Data,u8* Copy_pu8Read,u8 Copy_u8BufferSize)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8Counter = 0;
	if((Copy_pu8Read != NULL)&&(Copy_u8Data!=NULL))
	{
		while(Local_u8Counter<Copy_u8BufferSize)
		{
			SPI_u8TransceivePolling(Copy_u8Data[Local_u8Counter],&Copy_pu8Read[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}

u8 SPI_u8TransceiveInt(u8 Copy_u8Data,u8* Copy_pu8Read,void (*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if((Copy_pu8Read != NULL)&&(Notification!=NULL))
	{
		if(SPI_u8BusyFlag == IDLE)
		{
			SPI_u8BusyFlag = BUSY;
			SPI_u8Direction = SPI_SINGLE_CHAR;
			SPI_CallBackFunc = Notification;
			SPI_u8RecvData = Copy_pu8Read;
			SET_BIT(SPCR,SPCR_SPIE);
			SPDR = Copy_u8Data;
		}
		else
			Local_u8ErrorState = BUSY_FUNC;
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}

u8 SPI_u8BufferTransceiveAsynch(u8 *Copy_u8Data,u8* Copy_pu8Read,u8 Copy_u8BufferSize,void (*Notification)())
{
	u8 Local_u8ErrorState = OK;
	if((Copy_pu8Read != NULL)&&(Copy_u8Data!=NULL)&&((Notification!=NULL)))
	{
		if(SPI_u8BusyFlag == IDLE)
		{
			SPI_u8BusyFlag = BUSY;
			SPI_u8Direction = SPI_MULTI_CHAR;
			SPI_CallBackBuffFunc = Notification;
			SPI_u8SendDataBuff = Copy_u8Data;
			SPI_u8RecvDataBuff = Copy_pu8Read;
			SPI_u8BufferSize = Copy_u8BufferSize;
			SET_BIT(SPCR,SPCR_SPIE);
			SPI_u8Index = 0;
			SPDR = Copy_u8Data[SPI_u8Index];
		}
		else
			Local_u8ErrorState = BUSY_FUNC;
	}
	else
		Local_u8ErrorState = NULL_POINTER;
	return Local_u8ErrorState;
}
void __vector_12 (void)	__attribute__((signal));
void __vector_12 (void)
{

	if(SPI_SINGLE_CHAR==SPI_u8Direction)
	{
		*SPI_u8RecvData = SPDR;
		SPI_CallBackFunc();
		SPI_u8BusyFlag = IDLE;
	}
	else if(SPI_MULTI_CHAR==SPI_u8Direction)
	{
		SPI_u8RecvDataBuff[SPI_u8Index] = SPDR;
		SPI_u8Index++;
		if(SPI_u8Index==SPI_u8BufferSize)
		{
			SPI_u8BusyFlag = IDLE;
			CLR_BIT(SPCR,SPCR_SPIE);
			SPI_CallBackBuffFunc();
		}
		else
		{
			SPDR = SPI_u8SendDataBuff[SPI_u8Index];
		}
	}



}
