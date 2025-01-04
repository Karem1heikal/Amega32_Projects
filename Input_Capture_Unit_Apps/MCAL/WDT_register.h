/*
 * WDT_register.h
 *
 *  Created on: Aug 14, 2024
 *      Author: user
 */

#ifndef MCAL_WDT_REGISTER_H_
#define MCAL_WDT_REGISTER_H_

#define WDTCR 			*((volatile u8*)0x41)
#define WDTCR_WDTOE      4
#define WDTCR_WDE        3
#define WDTCR_WDP0	     0


#endif /* MCAL_WDT_REGISTER_H_ */
