/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : MCAL         **********************************/
/************************* SWC    : ADC          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
/***********************************************************/

/*	        ---------ADC Analog Channel --------
 *  You should put ADC Channel that Value in range of (0 --> 31)
 *  mean : the bellow order (-1)
 *    1- ADC0
 *    2- ADC1
 *    3- ADC2
 *    4- ADC3
 *    5- ADC4
 *    6- ADC5
 *    7- ADC6
 *    8- ADC7
 *         	------ Gain Selection Bits ----
 *    9 - ADC0_ADC0_10x
 *    10- ADC1_ADC0_10x
 *    11- ADC0_ADC0_200x
 *    12- ADC1_ADC0_200x
 *    13- ADC2_ADC2_10x
 *    14- ADC3_ADC2_10x
 *    15- ADC2_ADC2_200x
 *    16- ADC3_ADC2_200x
 *    17- ADC0_ADC1_1x
 *    18- ADC1_ADC1_1x
 *    19- ADC2_ADC1_1x
 *    20- ADC3_ADC1_1x
 *    21- ADC4_ADC1_1x
 *    22- ADC5_ADC1_1x
 *    23- ADC6_ADC1_1x
 *    24- ADC7_ADC1_1x
 *    25- ADC0_ADC2_1x
 *    26- ADC1_ADC2_1x
 *    27- ADC2_ADC2_1x
 *    28- ADC3_ADC2_1x
 *    29- ADC4_ADC2_1x
 *    30- ADC5_ADC2_1x
 *    31- VBG1_22V
 *    32- V_GND
 **/
typedef struct
{
	u8 *ChannelID;
	u8	size;
	u16 *result;
	void(*Notifiction)();
} Chain_t;

/**************************************************************/
void ADC_voidInit();
u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16 *Copy_u16ChannelReading);
u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel,u16 *Copy_u16ChannelReading,void (*Copy_vpNotifictionFunc)());
u8 ADC_u8StartChainConvertionAsynch(Chain_t* Copy_chain);
u8 ADC_u8StartChainConvertionSynch(Chain_t* Copy_chain);
#endif
