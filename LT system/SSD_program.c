/*********************************************************************************/
/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : HAL          **********************************/
/************************* SWC    : SSD          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"
#include "SSD_interface.h"

u8 SSD_u8Enable(SSD_t* SSD) {
	u8 Local_u8ErrorState = 0;
	if (CATHODE == SSD->ComType) {
			DIO_u8SetPinValue(SSD->EnablePort, SSD->EnablePin, DIO_PIN_LOW);
	} else if (ANODE == SSD->ComType) {
			DIO_u8SetPinValue(SSD->EnablePort, SSD->EnablePin, DIO_PIN_HIGH);
	} else
		Local_u8ErrorState = 1;
	return Local_u8ErrorState;
}
u8 SSD_u8Disable(SSD_t* SSD) {
	u8 Local_u8ErrorState = 0;
	if (CATHODE == SSD->ComType) {
			DIO_u8SetPinValue(SSD->EnablePort, SSD->EnablePin, DIO_PIN_HIGH);
	} else if (ANODE == SSD->ComType) {
			DIO_u8SetPinValue(SSD->EnablePort, SSD->EnablePin, DIO_PIN_LOW);
	} else
		Local_u8ErrorState = 1;
	return Local_u8ErrorState;
}
u8 SSD_u8SetNumber(SSD_t* SSD, u8 Copy_u8Number) {
	u8 Local_u8ErrorState = 0;
	u8 Local_u8EnableState;
	static u8 Local_u8Segmantarr[10] = SEGMANT_ARR;
	if (CATHODE == SSD->ComType) {
		DIO_u8GetPinValue(SSD->EnablePort, SSD->EnablePin,
				&Local_u8EnableState);
		if (Enable_LOW == Local_u8EnableState) {
				DIO_u8SetPortValue(SSD->Port,Local_u8Segmantarr[Copy_u8Number]);
		}
	} else if (ANODE == SSD->ComType) {
		DIO_u8GetPinValue(SSD->EnablePort, SSD->EnablePin,
				&Local_u8EnableState);
		if (Enable_HIGH == Local_u8EnableState) {
			DIO_u8SetPortValue(SSD->Port, ~(Local_u8Segmantarr[Copy_u8Number]));
		}
	} else
		Local_u8ErrorState = 1;
	return Local_u8ErrorState;
}
