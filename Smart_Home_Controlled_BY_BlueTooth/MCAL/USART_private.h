/*
 * USART_private.h
 *
 *  Created on: Jun 23, 2024
 *      Author: user
 */


#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

// COM MODE
#define ASYNCH 			1
#define SYNCH 			2

#define TxRising_RxFalling      0
#define TxFalling_RxRising      1

// PARITY MODE

#define NO_PARITY 		0
#define EVEN_PARITY 	2
#define ODD_PARITY 		3

#define  PARITY_MASK 	0b11001111
// STOP MODE
#define _1_BIT  		0
#define _2_BIT 			1

// Character size of frame

#define CHAR_SIZE_5_bit		0
#define CHAR_SIZE_6_bit		1
#define CHAR_SIZE_7_bit		2
#define CHAR_SIZE_8_bit		3
#define CHAR_SIZE_9_bit		7


#define  CHAR_SIZE_MASK 0xf9

// Baud rate options
#define BR_2400		2400UL
#define BR_4800		4800UL
#define BR_9600		9600UL
#define BR_14_4k	14400UL
#define BR_19_2k 	19200UL
#define BR_28_8k 	28800UL

// Double or normal speed options:
#define NORMAL_SPEED			1
#define DOUBLE_SPEED			2
#define SYNCH_MASTER_SPEED		3

#define IDLE	0
#define BUSY	1

#define SINGLE_CHER_SEND	0
#define MULTI_CHER_SEND		1

#define SINGLE_CHER_RECV	2
#define MULTI_CHER_RECV		3

#endif /* USART_PRIVATE_H_ */
