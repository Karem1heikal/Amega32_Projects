/*
 * ADC_program.c
 *
 *  Created on: Jul 27, 2024
 *      Author: user
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/ADC_private.h"
#include "../MCAL/ADC_config.h"
#include "../MCAL/ADC_interface.h"
#include "../MCAL/ADC_register.h"

static u8 Global_u8BusyFlag = IDLE;
static void (*Global_vCallBackFunc)() = NULL;
static u16 *Global_pu8Read = NULL;

static u8 ADC_u8DirectionOfConvFunc = SINGLE_CONVERISION;
static u8 ADC_u8ChainIndex = 0;
static u8 * ADC_pu8ChannelNum = NULL;
static u8 ADC_u8ChannelSize ;
static void (*Global_vChainCallBackFunc)() = NULL;
static u16 * ADC_pu16ChannelReading = NULL;
void ADC_voidInit()
{
	ADMUX &= MASK_AREF;
	ADMUX |= ADC_REF_VOLT<<ADMUX_REFS0;
#if ADC_ADJUST_BIT == LEFT_ADJUST
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_ADJUST_BIT == RIGHT_ADJUST
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "Wrong in choosing configuration of ADC_ADJUST_BIT "
#endif
	ADCSRA &= MASK_CLK_RATE;
	ADCSRA |= ADC_CLK_RATE<<ADCSRA_ADPS0;
#if	ADC_AUTO_TRIGGER_MODE == ENABLE

#if ADC_INTERRUPT_EN == ENABLE
	SET_BIT(ADCSRA,ADCSRA_ADIE);
#elif ADC_INTERRUPT_EN == DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
#endif
	SET_BIT(ADCSRA,ADCSRA_ADATE);

	SFIOR &= MASK_AUTO_TRIGGER;
	SFIOR |= ADC_AUTO_TRIGGER_SRC << SFIOR_ADTS0;

	SET_BIT(ADCSRA,ADCSRA_ADSC);
#elif ADC_AUTO_TRIGGER_MODE == DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
#else
#error "Wrong in choosing configuration of ADC_AUTO_TRIGGER_MODE "
#endif
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}
// Synch applay Busy Flag For reenterrant
u8 ADC_u8StartSingleConvPoll(u8 Copy_u8Channel,u16 *Copy_pu16Read)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32Counter = 0;
	if(Global_u8BusyFlag==IDLE)
	{
		Global_u8BusyFlag = BUSY;
		if(Copy_pu16Read != NULL)
		{
				if(Copy_u8Channel<=MAX_OPTION_CHANNEL)
				{
					ADMUX &= MASK_CHANNEL;
					ADMUX |= Copy_u8Channel<<ADMUX_MUX0;
					SET_BIT(ADCSRA,ADCSRA_ADSC);
					while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(Local_u32Counter<ADC_U32_TIMEOUT))
					{
						Local_u32Counter++;
					}
					if(Local_u32Counter==ADC_U32_TIMEOUT)
					{
						Local_u8ErrorState = NOTOK;
					}
					else{

						CLR_BIT(ADCSRA,ADCSRA_ADIF);
						if(ADC_ADJUST_BIT == LEFT_ADJUST)
							*Copy_pu16Read = ADC_REG>>8;
						else if(ADC_ADJUST_BIT == RIGHT_ADJUST)
							*Copy_pu16Read = ADC_REG;
						Global_u8BusyFlag = IDLE;
					}
				}
				else
					Local_u8ErrorState = NOTOK;
			}
			else
				Local_u8ErrorState = NULL_POINTER;
	}
	else
		Local_u8ErrorState = BUSY_FUNC;
	return Local_u8ErrorState;
}

u8 ADC_u8StartSingleConvInt(u8 Copy_u8Channel,u16 *Copy_pu16Read,void (*Notifiction)())
{
	u8 Local_u8ErrorState = OK;
	if(Global_u8BusyFlag==IDLE)
	{
		Global_u8BusyFlag = BUSY;
		ADC_u8DirectionOfConvFunc = SINGLE_CONVERISION;
		if((Copy_pu16Read != NULL)||(Notifiction != NULL))
		{

				if(Copy_u8Channel<=MAX_OPTION_CHANNEL)
				{
					ADMUX &= MASK_CHANNEL;
					ADMUX |= Copy_u8Channel<<ADMUX_MUX0;
					Global_vCallBackFunc = Notifiction;
					Global_pu8Read = Copy_pu16Read;
					SET_BIT(ADCSRA,ADCSRA_ADSC);
					SET_BIT(ADCSRA,ADCSRA_ADIE);
				}
				else
					Local_u8ErrorState = NOTOK;
		}
		else
			Local_u8ErrorState = NULL_POINTER;
	}
	else
		Local_u8ErrorState = BUSY_FUNC;
	return Local_u8ErrorState;
}
u8 ADC_u8StartChainConvAsynch(ADC_Chain *Copy_Chain)
{
	u8 Local_u8ErrorState = OK;
	if(Global_u8BusyFlag==IDLE)
	{
		Global_u8BusyFlag = BUSY;
		ADC_u8DirectionOfConvFunc = CHAIN_CONVERISION;
		if((Copy_Chain->ChainId != NULL)||(Copy_Chain->Notifction != NULL)||(Copy_Chain->Result != NULL))
		{
			if(Copy_Chain->ChainId[ADC_u8ChainIndex]<=MAX_OPTION_CHANNEL)
			{
				ADMUX &= MASK_CHANNEL;
				ADMUX |= Copy_Chain->ChainId[ADC_u8ChainIndex]<<ADMUX_MUX0;
				ADC_pu8ChannelNum = Copy_Chain->ChainId;
				Global_vChainCallBackFunc = Copy_Chain->Notifction;
				ADC_pu16ChannelReading = Copy_Chain->Result;
				ADC_u8ChannelSize = Copy_Chain->ChannelSize;
				SET_BIT(ADCSRA,ADCSRA_ADSC);
				SET_BIT(ADCSRA,ADCSRA_ADIE);
			}
			else
				Local_u8ErrorState = NOTOK;
		}
		else
			Local_u8ErrorState = NULL_POINTER;
	}
	else
		Local_u8ErrorState = BUSY_FUNC;
	return Local_u8ErrorState;

}
void __vector_16 (void)	__attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8DirectionOfConvFunc == SINGLE_CONVERISION)
	{
		if(ADC_ADJUST_BIT == LEFT_ADJUST)
			*Global_pu8Read = ADC_REG>>8;
		else if(ADC_ADJUST_BIT == RIGHT_ADJUST)
			*Global_pu8Read = ADC_REG;

		Global_u8BusyFlag = IDLE;

		Global_vCallBackFunc();

		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8DirectionOfConvFunc == CHAIN_CONVERISION)
	{
		if(ADC_ADJUST_BIT == LEFT_ADJUST)
			ADC_pu16ChannelReading[ADC_u8ChainIndex] = ADC_REG>>8;
		else if(ADC_ADJUST_BIT == RIGHT_ADJUST)
			ADC_pu16ChannelReading[ADC_u8ChainIndex] = ADC_REG;

		ADC_u8ChainIndex++;
		if(ADC_u8ChainIndex==ADC_u8ChannelSize)
		{
			Global_u8BusyFlag = IDLE;

			Global_vChainCallBackFunc();

			CLR_BIT(ADCSRA,ADCSRA_ADIE);

			ADC_u8ChainIndex = 0;
		}
		else
		{
			ADMUX &= MASK_CHANNEL;
			ADMUX |= ADC_pu8ChannelNum[ADC_u8ChainIndex]<<ADMUX_MUX0;
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}

	}
}
