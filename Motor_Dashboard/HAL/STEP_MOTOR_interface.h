/*
 * STEP_MOTOR_interface.h
 *
 *  Created on: Jul 19, 2024
 *      Author: user
 */

#ifndef HAL_STEP_MOTOR_INTERFACE_H_
#define HAL_STEP_MOTOR_INTERFACE_H_

#define STEP_UPPER_NIBBLE		1
#define STEP_LOWER_NIBBLE		0

#define STEP_CLOCKWISE				0
#define STEP_COUNTER_CLOCKWISE		1

typedef struct
{
	u8 Port;
	u8 Nibble;
	u8 Diraction;
	u16 AngleDegree;
} STEP_t;
u8 STEP_MOTORu8StartHalfMode(STEP_t *Copy_pStep);
u8 STEP_MOTORu8StartFullMode(STEP_t *Copy_pStep);

void STEP_MOTORvStop(STEP_t *Copy_pStep);
#endif /* HAL_STEP_MOTOR_INTERFACE_H_ */
