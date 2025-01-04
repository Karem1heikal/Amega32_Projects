/*********************************************************************************/
/*********************************************************************************/
/*************************      Auther: karem heikal     *************************/
/*************************      layer : HAL              *************************/
/*************************      SWC :   CLCD             *************************/
/*************************      Version:1.00             *************************/
/*********************************************************************************/
/*********************************************************************************/

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include <util/delay.h>
#include "../MCAL/DIO_interface.h"
#include "../HAL/CLCD_config.h"
#include "../HAL/CLCD_interface.h"
#include "../HAL/CLCD_private.h"

static u8 iniIsFinich=0;
void CLCD_voidSendCommand(u8 Copy_u8Command)//math
{

#if CLCD_CHIOCE_MODE==_8_BIT_MODE
	/*PIN RS SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_PIN_LOW);
	/*PIN RW SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_PIN_LOW);
	/*PORT SET COMMAND*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	/*PIN SET  send pulse (E) */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_PIN_LOW);
#elif CLCD_CHIOCE_MODE==_4_BIT_MODE
	u8 Local_u8Mask = 0b11110000;
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_PIN_LOW);
	/*PIN RW SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_PIN_LOW);
	/*PORT SET COMMAND*/
	Local_u8Mask &= Copy_u8Command;
	DIO_u8SetPortValue(CLCD_DATA_PORT, Local_u8Mask);
	/*PIN SET  send pulse (E) */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_LOW);
	if(iniIsFinich)
	{
		Local_u8Mask = 0b11110000;
		Local_u8Mask = ~(Local_u8Mask) & Copy_u8Command;
		DIO_u8SetPortValue(CLCD_DATA_PORT, (Local_u8Mask << 4));
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_LOW);
	}
	_delay_ms(2);
#else
#error "In correct cconfigrtion of LCD_MODE"
#endif

}
u8 CLCD_Read_BF_AC() {
	u8 Local_u8Address = 0;
	/*PIN RS SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_PIN_LOW);
	/*PIN RW SET HIGH  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_PIN_HIGH);
	/*PIN SET  send pulse (E) */
	for (u8 i = 0; i < 7; i++) {
		DIO_u8GetPinValue(CLCD_DATA_PORT, i, &Local_u8Address);
		Local_u8Address += Local_u8Address << i;
	}
	return Local_u8Address;
}

void CLCD_voidSendData(u8 Copy_u8Data)
{

#if CLCD_CHIOCE_MODE==_8_BIT_MODE
	u8 Local_u8Address;
	/*PIN RS SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_PIN_HIGH);
	/*PIN RW SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_PIN_LOW);
	/*PORT SET COMMAND*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	/*PIN SET  send pulse (E) */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_PIN_LOW);
	Local_u8Address = CLCD_Read_BF_AC();
	if (Local_u8Address > 0x0f)
		CLCD_voidSendCommand(0x0C);
	else
		CLCD_voidSendCommand(0x06);
#elif CLCD_CHIOCE_MODE==_4_BIT_MODE
	u8 Local_u8Mask = 0b11110000;
	/*PIN RS SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_PIN_HIGH);
	/*PIN RW SET LOW  */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_PIN_LOW);
	/*PORT SET COMMAND*/
	Local_u8Mask &= Copy_u8Data;
	DIO_u8SetPortValue(CLCD_DATA_PORT,Local_u8Mask);
	/*PIN SET send pulse (E) */
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_LOW);
	Local_u8Mask=0b11110000;
	Local_u8Mask = ~(Local_u8Mask) & Copy_u8Data;
	DIO_u8SetPortValue(CLCD_DATA_PORT, (Local_u8Mask << 4));
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_PIN_LOW);
	_delay_ms(2);
	CLCD_voidSendCommand(0x06);
#else
#error "In correct cconfigrtion of LCD_MODE"
#endif
}

void CLCD_voidInit(void)
{
#if CLCD_CHIOCE_MODE==_8_BIT_MODE
	/*WAIT FOR MORE THEN 30 MS*/
	_delay_ms(40);
	/*function set command: 2 Lines 5*8 font */
	CLCD_voidSendCommand(0b00111000);

	/*Display No/00f ctrl :display enable , disable cursor ,no blink cursor */
	CLCD_voidSendCommand(0b00001100);
	/*Display Clear */
	CLCD_voidSendCommand(0b00000001);
#elif CLCD_CHIOCE_MODE==_4_BIT_MODE
	/*WAIT FOR MORE THEN 30 MS*/
	_delay_ms(40);
	/*function set command: Set Bit 5 */
	CLCD_voidSendCommand(0b00100000);
	CLCD_voidSendCommand(0b00100000);

	/*function set command:(7_Bit) N --> Lines,(6_Bit) F --> 5*8 font */
	CLCD_voidSendCommand(0b10000000);
	_delay_ms(1);
	CLCD_voidSendCommand(0b0000);
	/*Display No/00f ctrl  */
	/*Set Bit 7 ,(6_Bit) D --> display enable ,C --> disable cursor ,B --> no blink cursor*/
	CLCD_voidSendCommand(0b011000000);
	_delay_ms(1);
	CLCD_voidSendCommand(0b0000);
	/*Display Clear */
	CLCD_voidSendCommand(0b00010000);
	_delay_ms(2);

	iniIsFinich=1;
#else
#error "In correct cconfigrtion of LCD_MODE"
#endif
}
void CLCD_voidSendString(const char* Copy_pcString)//char ASCII Value Constant not allow the func to change the sent string
{
	u8 Local_u8cnt=0;
	while(Copy_pcString[Local_u8cnt]!='\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8cnt]);
		Local_u8cnt++;
	}
}

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8Address;
	if(Copy_u8XPos==0)
	{
		if (Copy_u8YPos > 15) {
			Local_u8Address = 0x40 + Copy_u8YPos;
		} else {
			Local_u8Address = Copy_u8YPos;
		}
	}
	else if(Copy_u8XPos==1)
	{
		Local_u8Address=0x40+Copy_u8YPos;
	}
	//put command from data sheet
	CLCD_voidSendCommand(Local_u8Address+128);
}

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNmber,u8 Copy_u8XPos,u8 Copy_u8Ypos)
{
	u8 Local_u8CGRAMAddress=0;
	u8 Local_u8iterator;
	/*Calculate the CGRAM address whose each block is 8 bytes */
	Local_u8CGRAMAddress= Copy_u8PatternNmber*8;

	/*Send CGRAM address command to LCD, with setting bit 6 , clear bit 7 */
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);

	/*Write the pattern into CGRAM */
	for(Local_u8iterator=0;Local_u8iterator<8;Local_u8iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8iterator]);
	}
	/* Go back to DDRAM to display the pattern */
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8Ypos);

	/* Display the pattern written  in the CGRAM */
	CLCD_voidSendData(Copy_u8PatternNmber);

}

void CLCD_voidWriteNumber(u16 Copy_u16Number)
{

	u8 Max_Digits = Num_length(Copy_u16Number);
	for (s8 i = Max_Digits; i > 0; i--) {
		CLCD_voidSendData((Copy_u16Number / Multi_N_10(i - 1)) + '0');
		Copy_u16Number = (Copy_u16Number % Multi_N_10(i - 1));
	}
}


static u8 Num_length(u16 num) {
	u8 Local_u8Cnt = 0;
	if(num == 0)
		return 0;
	while (num != 0) {
		num /= 10;
		Local_u8Cnt++;
	}
	return Local_u8Cnt;
}
static u16 Multi_N_10(u8 N) {
	u8 Local_u8Cnt;
	u16 p = 1;
	for (Local_u8Cnt = 0; Local_u8Cnt < N; Local_u8Cnt++)
		p *= 10;
	return p;
}
