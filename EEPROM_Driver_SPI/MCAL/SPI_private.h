/*
 * SPI_private.h
 *
 *  Created on: Jul 10, 2024
 *      Author: user
 */

#ifndef MCAL_SPI_PRIVATE_H_
#define MCAL_SPI_PRIVATE_H_

#define LSB 	1
#define MSB 	0

#define MODE_0   0
#define MODE_1   1
#define MODE_2   2
#define MODE_3   3

#define CLK_POL_PHA_MASK  0xf3
#define CLK_PRE_MASK	  0xfc

#define CLK_4     0
#define CLK_16    1
#define CLK_64    2
#define CLK_128   3
#define CLK_2     4
#define CLK_8     5
#define CLK_32    6

#define SPI_DUMY_VALUE 0xff


#define IDLE    	0
#define BUSY		1

#define SPI_SINGLE_CHAR    	0
#define SPI_MULTI_CHAR    	1



#endif /* MCAL_SPI_PRIVATE_H_ */
