/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : MCAL         **********************************/
/************************* SWC    : ADC          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

/*single Conversion Asynchronously  */
static void (*ADC_voidCallBackNotificationFunc)()=NULL;

static u16 *Global_u16GetChannelReading = NULL;


/*Chain Global Varible initalize */
static u8 *Global_pu8ChainChannelArr=NULL;		//Global variable to carry chain channel

static u8 Global_pu8ChainSize=NULL;				//Global variable to carry chain Number

static u8 Global_u8ChannelIdx=0;			//Global variable to carry chain index

u8 ADC_u8SourceOfConv;
/*busy flag states*/
u8 ADC_u8BusyState = IDLE;
void ADC_voidInit()
{
	/*set bit ADC reference*///
#if ADC_INITAL_REF	== AREF
	CLR_BIT(ADMUX,ADMUX_REFS1);
	CLR_BIT(ADMUX,ADMUX_REFS0);
#elif	ADC_INITAL_REF	== AVCC
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#elif	ADC_INITAL_REF	== Internal_HALF
	SET_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
#else
#error "wrong in Choosing configuration of ADC reference "
#endif

	/*set bit ADC Adjust data*/
#if	ADC_ADJUST_DATA == Right_adjust
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#elif	ADC_ADJUST_DATA == left_adjust
	SET_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "wrong in Choosing configuration of ADC Data Register "
#endif

	/*Prescaler Selection ADPS By Masking Value */
	ADCSRA&=ADCSRA_MASK;
	ADCSRA|=ADC_DIV_FACTOR;
	/*Enable ADC */
	SET_BIT(ADCSRA,ADCSRA_ADEN);
#if (ADC_AUTO_TRIGGER==Enable)
	/*Enable Auto trigger mode*/
	SET_BIT(ADCSRA,ADCSRA_ADATE);
	/*set the required channel in ADMUX register */
	ADMUX&=ADMUX_MASK;
	ADMUX|=ADC_AUTO_Channel;

	SFIOR&=SFIOR_MASK;
	SFIOR|=ADC_AUTO_TRIG_SOURCE;
	/*START conversion */
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	/*the Auto Trigger source is selected By setting ADCS 3-Bit*/
	SET_BIT(ADCSRA,ADCSRA_ADIE);
#endif


}
/*convert output Values to voltage Values*/
u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16 *Copy_u16ChannelReading)
{
	u8 Local_u8ErrorState=OK;
	u32 Local_u32Counter=0;
	if(ADC_u8BusyState==IDLE){
		ADC_u8BusyState = Busy;
		if (ADC_AUTO_TRIGGER==Disable)	//( single conversion )
		{
			/*set the required channel in ADMUX register */

			ADMUX&=ADMUX_MASK;
			ADMUX|=Copy_u8Channel;
			/*START conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/*Polling (busy waiting) until the conversion complete flag is set or Counter reaches timeout Value*/
			while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0)&&(Local_u32Counter!=ADC_U32TIMEOUT))
			{
				Local_u32Counter++;
			}
			if(Local_u32Counter==ADC_U32TIMEOUT)
			{
				// loop is Broken as Time out
				Local_u8ErrorState=NOTOK;
			}
			else
			{
				// Raising the conversion complete flag
				/*clear ADC Flag */
				CLR_BIT(ADCSRA,ADCSRA_ADIF);
				/* ADC reading from data register */
				if	(ADC_ADJUST_DATA == Right_adjust)
					*Copy_u16ChannelReading= ADC_DATA_REG;
				else if	(ADC_ADJUST_DATA == left_adjust)
					*Copy_u16ChannelReading = ADCH;
				ADC_u8BusyState = IDLE;
			}
		}
		else if (ADC_AUTO_TRIGGER==Enable)
		{
			/* ADC reading from data register */
			if	(ADC_ADJUST_DATA == Right_adjust)
					*Copy_u16ChannelReading= ADC_DATA_REG;
			else if	(ADC_ADJUST_DATA == left_adjust)
				*Copy_u16ChannelReading = ADCH;
			/*adc is finished */
			ADC_u8BusyState = IDLE;
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else {
		Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}


u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16 *Copy_u16ChannelReading,void (*Copy_vpNotifictionFunc)())
{
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE){
		if((Copy_vpNotifictionFunc == NULL)||(Copy_u16ChannelReading == NULL))
		{
			Local_u8ErrorState = NULL_POINTER;
		}
		else {
			ADC_u8SourceOfConv=SINGLE_CHANNEL_ASYNCH;
			ADC_u8BusyState = Busy;
			/*Set Call Back function with the received Notification function*/
			ADC_voidCallBackNotificationFunc = Copy_vpNotifictionFunc;
			/* initialize Local Reading argument with global one  */
			Global_u16GetChannelReading = Copy_u16ChannelReading;
			/*set the required channel in ADMUX register */
			ADMUX&=ADMUX_MASK;
			ADMUX|=Copy_u8Channel;
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			SET_BIT(ADCSRA,ADCSRA_ADIE);
			}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
/*/* chick ADC_u8StartChainConvertionSynch */
u8 ADC_u8StartChainConvertionSynch(Chain_t* Copy_chain)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8Counter;
	if(Copy_chain->Notifiction!=NULL)
	{
		if(ADC_u8BusyState==IDLE)
		{
			for(Local_u8Counter=0;Local_u8Counter<Copy_chain->size;Local_u8Counter++)
			{
				ADC_u8StartConversionSynch(Copy_chain->ChannelID[Local_u8Counter],(Copy_chain->result+Local_u8Counter));
			}
			Copy_chain->Notifiction();
		}
		else
			Local_u8ErrorState=BUSY_FUNC;
	}
	else
		Local_u8ErrorState=NULL_POINTER;
	return  Local_u8ErrorState;
}
u8 ADC_u8StartChainConvertionAsynch(Chain_t* Copy_chain)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_chain->Notifiction!=NULL)
	{
		if(ADC_u8BusyState==IDLE)
		{
			/*make source of conversion CHAIN_CHANNEL_ASYNCH*/
			ADC_u8SourceOfConv=CHAIN_CHANNEL_ASYNCH;
			ADC_u8BusyState=Busy;
			/*Set Call Back function with the received Notification function*/
			ADC_voidCallBackNotificationFunc = Copy_chain->Notifiction;
			/* initialize Local channel argument with global one  */
			Global_pu8ChainChannelArr = Copy_chain->ChannelID;
			/* initialize Local chain size argument with global one  */
			Global_pu8ChainSize = Copy_chain->size;
			/* initialize Local chain index with global one  */
			Global_u8ChannelIdx = 0;
			/* initialize Local chain result with global one  */
			Global_u16GetChannelReading=Copy_chain->result;

			ADMUX&=ADMUX_MASK;
			ADMUX|=Copy_chain->ChannelID[Global_u8ChannelIdx];
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
			Local_u8ErrorState=BUSY_FUNC;
	}
	else
		Local_u8ErrorState=NULL_POINTER;

	return  Local_u8ErrorState;
}

void __vector_16 (void)	__attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8SourceOfConv==0){
		/* ADC reading from data register */
		if	(ADC_ADJUST_DATA == Right_adjust)
			*Global_u16GetChannelReading = ADC_DATA_REG;
		else if	(ADC_ADJUST_DATA == left_adjust)
			*Global_u16GetChannelReading = ADCH;
		/* ADC basy state IDLE as Conversion is finished*/
		ADC_u8BusyState = IDLE;
		/* call Notification function */
		ADC_voidCallBackNotificationFunc();
		/* Disable ADC Interrupt Enable */
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8SourceOfConv==1){
		if	(ADC_ADJUST_DATA == Right_adjust)
			Global_u16GetChannelReading[Global_u8ChannelIdx] = ADC_DATA_REG;
		else if	(ADC_ADJUST_DATA == left_adjust)
			Global_u16GetChannelReading[Global_u8ChannelIdx] = ADCH;
		Global_u8ChannelIdx++;
		if(Global_u8ChannelIdx==Global_pu8ChainSize)
		{
			/* ADC basy state IDLE as Conversion is finished*/
			ADC_u8BusyState = IDLE;
			/* call Notification function */
			ADC_voidCallBackNotificationFunc();
			/* Disable ADC Interrupt Enable */
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			ADMUX&=ADMUX_MASK;
			ADMUX|=Global_pu8ChainChannelArr[Global_u8ChannelIdx];
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}
