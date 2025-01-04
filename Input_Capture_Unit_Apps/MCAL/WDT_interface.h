/*
 * WDT_interface.h
 *
 *  Created on: Aug 14, 2024
 *      Author: user
 */

#ifndef MCAL_WDT_INTERFACE_H_
#define MCAL_WDT_INTERFACE_H_

void WDT_voidEnable();
void WDT_voidDisable();

/*
 * Watchdog Timer Prescale Select
 * options:
 * 			Typical Time-out|  Typical Time-out
 *          at VCC = 3.0V   |  at VCC = 5.0V
 *
 *         0-    17.1 ms 	|    16.3 ms
 *         1-    34.3 ms 	|    32.5 ms
 *         2-    68.5 ms 	|    65   ms
 *         3-    0.14 s     |    0.13 s
 *         4-    0.27 s 	|    0.26 s
 *         5-    0.55 s 	|    0.52 s
 *         6-    1.1 s 		|    1.0 s
 *         7-    2.2 s 		|    2.1 s
 *
 * */
u8 WDT_u8Sleep(u8 Copy_u8TimerSleep);

#endif /* MCAL_WDT_INTERFACE_H_ */
