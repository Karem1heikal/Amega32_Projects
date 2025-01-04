/*
 * SERVO_config.h
 *
 *  Created on: Aug 9, 2024
 *      Author: user
 */

#ifndef HAL_SERVO_CONFIG_H_
#define HAL_SERVO_CONFIG_H_

/*
 * for connecting servo in channel (A) PWM
 * OC1A_CCST		* OC1A_SCCT
 * OC1A_CCST		* OC1A_SCCT
 * for connecting servo in channel (B) PWM
 * OC1B_CCST		* OC1B_SCCT
 * OC1B_CCST		* OC1B_SCCT
 * */

#define SERVO_CHANNAL_CON	OC1B_CCST


#endif /* HAL_SERVO_CONFIG_H_ */
