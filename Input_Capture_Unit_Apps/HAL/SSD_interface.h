/*
 * SSD_interface.h
 *
 *  Created on: Jul 16, 2024
 *      Author: user
 */

#ifndef HAL_SSD_INTERFACE_H_
#define HAL_SSD_INTERFACE_H_

typedef struct
{
	u8 ComType;
	u8 Port;
	u8 EnablePort;
	u8 EnablePin;
} SSD_t;

#define ANODE		0
#define CATHODE		1

u8 SSD_u8SetNumber(u8 Copy_u8Number,SSD_t *Copy_SSD);
u8 SSD_u8Enable(SSD_t *Copy_SSD);
u8 SSD_u8Disable(SSD_t *Copy_SSD);

#endif /* HAL_SSD_INTERFACE_H_ */
