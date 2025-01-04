/*********************************************************************************/
/*********************************************************************************/
/*************************      Auther: karem heikal     *************************/
/*************************      layer : HAL              *************************/
/*************************      SWC :   CLCD             *************************/
/*************************      Version:1.00             *************************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define CLCD_RS_Command 	0
#define CLCD_RS_Data 		1

void CLCD_voidSendCommand(u8 Copy_u8Command);
u8 CLCD_Read_BF_AC();
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendString(const char* Copy_u8string);

void CLCD_voidInit(void);

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);

void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNmber,u8 Copy_u8XPos,u8 Copy_u8Ypos);

void CLCD_voidWriteNumber(u16 Copy_u16Number);

#endif

