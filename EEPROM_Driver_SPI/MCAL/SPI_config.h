/*
 * SPI_config.h
 *
 *  Created on: Jul 13, 2024
 *      Author: user
 */

#ifndef MCAL_SPI_CONFIG_H_
#define MCAL_SPI_CONFIG_H_


/* initialize pin of SPI
 * 				master  		slave
 * 		sck 	out				in
 * 		MOSI	OUT				IN
 * 		MISO	IN				OUT
 * 		SS		IN(POLLUP)		IN
 * */
/*
 * Set Order of data bits
 * option :
 * 		1-LSB
 *  	2-MSB
 * */

#define SPI_DATA_ORDER		MSB
/*
 * Set clock polarity and clock phase
 * 		Leading Edge        Trailing Edge      	SPI Mode
 * 		------------------------------------------------
 * 		Sample (Rising)    	Setup (Falling)     MODE_0
 * 		Setup (Rising)     	Sample (Falling)	MODE_1
 * 		Sample (Falling)   	Setup (Rising) 		MODE_2
 * 		Setup (Falling) 	Sample (Rising) 	MODE_3
 *
 * */
#define SPI_MODE	MODE_0

/*
 * Clock Prescaler
 *  option:
 *      1- CLK_4
 *      2- CLK_16
 *      3- CLK_64
 *      4- CLK_128
 *      5- CLK_2
 *      6- CLK_8
 *      7- CLK_32
 * */

#define SPI_CLOCK_PRE	CLK_16


#define SPI_u32TIMEOUT 500000
#endif /* MCAL_SPI_CONFIG_H_ */
