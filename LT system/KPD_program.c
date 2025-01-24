/*********************************************************************************/
/*********************************************************************************/
/************************* Author : karem heikal *********************************/
/************************* layer  : HAL          *********************************/
/************************* SWC    : KPD         *********************************/
/************************* Version: 1.00         *********************************/
/*********************************************************************************/
/*********************************************************************************/
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"
#include "KPD_interface.h"


u8 KPD_u8Key_pressed()
{
	u8 Local_u8RowItrator;
	u8 Local_u8ColItrator;
	u8 Local_u8GetState;
	u8 Local_u8KeyPressed = KPD_NO_PRESSED_KEY;
	static u8 Local_u8KPD_ROW_PINS[Max_Rows] = { KPD_ROW_PIN0, KPD_ROW_PIN1,
			KPD_ROW_PIN2, KPD_ROW_PIN3 };
	static u8 Local_u8KPD_COL_PINS[Max_Cols] = { KPD_COL_PIN0, KPD_COL_PIN1,
			KPD_COL_PIN2, KPD_COL_PIN3 };
	static u8 Local_u8KPD_Nums[Max_Rows][Max_Cols] = KPD_u8ARR;
	for (Local_u8ColItrator = 0; Local_u8ColItrator < Max_Cols;
			Local_u8ColItrator++) {
		DIO_u8SetPinValue(KPD_INPUT_PORT,
				Local_u8KPD_COL_PINS[Local_u8ColItrator], DIO_PIN_LOW);
		/*Read the current Row*/
		for (Local_u8RowItrator = 0; Local_u8RowItrator < Max_Rows;
				Local_u8RowItrator++) {
			DIO_u8GetPinValue(KPD_INPUT_PORT,
					Local_u8KPD_ROW_PINS[Local_u8RowItrator],
					&Local_u8GetState);
			/*chick switch id pressed */
			if (Local_u8GetState == DIO_PIN_LOW) {
				Local_u8KeyPressed =
						Local_u8KPD_Nums[Local_u8RowItrator][Local_u8ColItrator];
				/*polling busy waiting until the key is released*/
				while (Local_u8GetState == DIO_PIN_LOW) {
					DIO_u8GetPinValue(KPD_INPUT_PORT,
							Local_u8KPD_ROW_PINS[Local_u8RowItrator],
							&Local_u8GetState);
				}
				return Local_u8KeyPressed;
			}
		}
		DIO_u8SetPinValue(KPD_INPUT_PORT,
				Local_u8KPD_COL_PINS[Local_u8ColItrator], DIO_PIN_HIGH);
	}
	return Local_u8KeyPressed;
}



