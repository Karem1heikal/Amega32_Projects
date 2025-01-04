/*
 * USART_config.h
 *
 *  Created on: Jun 23, 2024
 *      Author: user
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#define CLOCK_SOURCE  8000000UL
/*
 * COMMUNICATION _ MODE
 * 	1-  ASYNCH
 * 	2-  SYNCH
 * */
#define SYNCH_MODE 		ASYNCH

/*
 * Clock Polarization
 * options :
 * 		1- TxRising_RxFalling
 * 		2- TxFalling_RxRising
 *
 * */
#define CLK_POLARITY  TxRising_RxFalling

/*
 * parity check mode
 * 	1-NO_PARITY
 * 	2-EVEN_PARITY
 * 	3-ODD_PARITY
 *
 * */

#define	PARITY_MODE  	NO_PARITY

/*
 * STOP MODE
 * 	1- 	_1_BIT
 * 	2-	_2_BIT
 *
 * */

#define	STOP_MODE  		_1_BIT

/* Character size of frame
 * options:
 *  1-  CHAR_SIZE_5_bit
 *  2-  CHAR_SIZE_6_bit
 *  3-  CHAR_SIZE_7_bit
 *  4-  CHAR_SIZE_8_bit
 *  5-  CHAR_SIZE_9_bit
 *
 * */

#define CHARACTER_SIZE 	CHAR_SIZE_8_bit

/*
 * Baud Rate options:
 *   1-  BR_2400
 *   2-  BR_4800
 *   3-  BR_9600
 *   4-  BR_14_4k
 * 	 5-	 BR_19_2k
 * 	 6-  BR_28_8k
 *
 * */

#define BAUD_RATE	BR_9600

/*
 * Double Or NOrmal Speed:
 * 	 1- NORMAL_SPEED
 * 	 2- DOUBLE_SPEED
 *	 3- SYNCH_MASTER_SPEED
 * */

#define SPEED_MODE	NORMAL_SPEED


#define USART_u32TIMEOUT 50000

#endif /* USART_CONFIG_H_ */
