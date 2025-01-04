/*
 * USART_interface.h
 *
 *  Created on: Jun 23, 2024
 *      Author: user
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_init();

u8 USART_u8SendPolling(u8 Copy_u8Data);

u8 USART_u8ReceivePolling(u16 *Copy_pu16Read);

u8 USART_u8ReceivePollingWithOut(u16 *Copy_pu16Read);

u8 USART_u8SendStringPoll(const char* Copy_pcString);

u8 USART_u8ReceiveBufferPoll(char* Copy_pcString,u8 Copy_u8BufferSize);

u8 USART_u8ReceiveBufferPollWithOut(char* Copy_pcString,u8 Copy_u8BufferSize);

u8 USART_u8SendCharInt(u8 Copy_u8Data,void(*Notification)());

u8 USART_u8SendStringInt(char* Copy_pcString,void(*Notification)());

u8 USART_u8ReceiveCharInt(u16 *Copy_pu16Read,void(*Notification)());

u8 USART_u8ReceiveBufferInt(char *Copy_pcString,u8 Copy_u8BufferSize,void(*Notification)());





#endif /* USART_INTERFACE_H_ */
