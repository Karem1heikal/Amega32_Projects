/*
 * SPI_interface.h
 *
 *  Created on: Jul 10, 2024
 *      Author: user
 */

#ifndef MCAL_SPI_INTERFACE_H_
#define MCAL_SPI_INTERFACE_H_

/* initialize pin of SPI
 * 				master  		slave
 * 		sck 	out				in
 * 		MOSI	OUT				IN
 * 		MISO	IN				OUT
 * 		SS		IN(POLLUP)		IN
 * */
void SPI_voidMasterInit();
void SPI_voidSlaveInit();

u8 SPI_u8TransceivePolling(u8 Copy_u8Data,u8* Copy_pu8Read);
u8 SPI_u8MasterSendPolling(u8 Copy_u8Data);
u8 SPI_u8MasterRecvPolling(u8 *Copy_pu8Read);
u8 SPI_u8BufferTransceiveSynch(u8* Copy_u8Data,u8* Copy_pu8Read,u8 Copy_u8BufferSize);


u8 SPI_u8TransceiveInt(u8 Copy_u8Data,u8* Copy_pu8Read,void (*Notification)());
u8 SPI_u8MasterSendInt(u8 Copy_u8Data,void (*Notifiction)());
u8 SPI_u8MasterRecvInt(u8 *Copy_pu8Read,void (*Notifiction)());
u8 SPI_u8BufferTransceiveAsynch(u8 *Copy_u8Data,u8* Copy_pu8Read,u8 Copy_u8BufferSize,void (*Notification)());

u8 SPI_u8SlaveSend(u8 Copy_u8Data);
u8 SPI_u8SlaveRecv(u8 *Copy_pu8Read);

// Pin connected to (ss) of Master to make it Slave and convert current slave to master
void SPI_voidConvertSlaveAccess(u8 Copy_u8Port,u8 Copy_u8Pin);


#endif /* MCAL_SPI_INTERFACE_H_ */
