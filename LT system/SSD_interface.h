/*********************************************************************************/
/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : HAL          **********************************/
/************************* SWC    : SSD          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define CATHODE 	0
#define ANODE 		1

#define SSD_u8PORTA	0
#define SSD_u8PORTB	1
#define SSD_u8PORTC	2
#define SSD_u8PORTD	3

#define SSD_u8PIN0 	0
#define SSD_u8PIN1	1
#define SSD_u8PIN2	2
#define SSD_u8PIN3	3
#define SSD_u8PIN4	4
#define SSD_u8PIN5	5
#define SSD_u8PIN6	6
#define SSD_u8PIN7	7

#define Enable_LOW	0
#define Enable_HIGH	1

#define SSD_u8VisableNUM0	0b00111111
#define SSD_u8VisableNUM1	0b00000110
#define SSD_u8VisableNUM2	0b01011011
#define SSD_u8VisableNUM3	0b01001111
#define SSD_u8VisableNUM4	0b01100110
#define SSD_u8VisableNUM5	0b01101101
#define SSD_u8VisableNUM6	0b01111101
#define SSD_u8VisableNUM7	0b00000111
#define SSD_u8VisableNUM8	0b01111111
#define SSD_u8VisableNUM9	0b01101111

#define SEGMANT_ARR {SSD_u8VisableNUM0,SSD_u8VisableNUM1,SSD_u8VisableNUM2,SSD_u8VisableNUM3,SSD_u8VisableNUM4,SSD_u8VisableNUM5,SSD_u8VisableNUM6,SSD_u8VisableNUM7,SSD_u8VisableNUM8,SSD_u8VisableNUM9}

typedef struct {
	u8 ComType;
	u8 Port;
	u8 EnablePort;
	u8 EnablePin;
} SSD_t;

/*****************************************************************************************/
/* Function: SSD_u8SetNumber	                        				    			**/
/* I/P Parameters:struct SSD_t{ CommonType ,Port ,EnablePort ,EnablePin },Number		**/
/* Returns:it returns u8                               				    				**/
/* Desc:This Function Sets the Value to display on 7SEGMENT 				       	    **/
/*****************************************************************************************/
/* CommonType 		Options: ANODE , CATHODE											**/
/* Port 			Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD		**/
/* EnablePort 		Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD		**/
/* EnablePin  		Options: DIO_u8_PIN0 --> DIO_u8_PIN7                          		**/
/* Copy_u8Number  	Options: Value 0 --> 9                               				**/
/*****************************************************************************************/
u8 SSD_u8SetNumber(SSD_t* SSD, u8 Copy_u8Number);
/*****************************************************************************************/
/* Function: SSD_u8Enable	                        				    				**/
/* I/P Parameters:struct SSD_t{ CommonType ,Port ,EnablePort ,EnablePin }				**/
/* Returns:it returns u8                               				    				**/
/* Desc:This Function enable 7SEGMENT 				       	    						**/
/*****************************************************************************************/
/* CommonType 		Options: ANODE , CATHODE											**/
/* Port 			Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD		**/
/* EnablePort 		Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD		**/
/* EnablePin  		Options: DIO_u8_PIN0 --> DIO_u8_PIN7                          		**/
/*****************************************************************************************/
u8 SSD_u8Enable(SSD_t* SSD);
/*****************************************************************************************/
/* Function: SSD_u8Disable	                        				    				**/
/* I/P Parameters:struct SSD_t{ CommonType ,Port ,EnablePort ,EnablePin }				**/
/* Returns:it returns u8                               				    				**/
/* Desc:This Function disable 7SEGMENT 				       	    						**/
/*****************************************************************************************/
/* CommonType 		Options: ANODE , CATHODE											**/
/* Port 			Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD		**/
/* EnablePort 		Options: DIO_u8_PORTA, DIO_u8_PORTB, DIO_u8_PORTC, DIO_u8_PORTD		**/
/* EnablePin  		Options: DIO_u8_PIN0 --> DIO_u8_PIN7                          		**/
/*****************************************************************************************/
u8 SSD_u8Disable(SSD_t* SSD);





#endif
