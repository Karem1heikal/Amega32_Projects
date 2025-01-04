/*
 * STEP_MOTOR_private.h
 *
 *  Created on: Jul 19, 2024
 *      Author: user
 */

#ifndef HAL_STEP_MOTOR_PRIVATE_H_
#define HAL_STEP_MOTOR_PRIVATE_H_

#define MAX_FULL_STEP 4
#define MAX_HALF_STEP 8

#define MASK_CW 	0X01
#define MASK_CCW 	0X08

static u8 RotateRightLowNibble(u8 Val);

static u8 RotateLeftLowNibble(u8 Val);





#endif /* HAL_STEP_MOTOR_PRIVATE_H_ */
