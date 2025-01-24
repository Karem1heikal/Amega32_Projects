/*
 * imp_priavte.c
 *
 *  Created on: Jul 14, 2023
 *      Author: user
 */
#include "STD_TYPES.h"
#include "CLCD_private.h"

u8 Num_length(u16 num) {
	u8 Local_u8Cnt = 0;
	while (num != 0) {
		num /= 10;
		Local_u8Cnt++;
	}
	return Local_u8Cnt;
}
u16 Multi_N_10(u8 N) {
	u8 Local_u8Cnt;
	u16 p = 1;
	for (Local_u8Cnt = 0; Local_u8Cnt < N; Local_u8Cnt++)
		p *= 10;
	return p;
}
