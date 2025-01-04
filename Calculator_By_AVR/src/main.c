/*
 * main.c
 *
 *  Created on: Jun 28, 2024
 *      Author: user
 */

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/PORT_interface.h"
#include "../HAL/KPD_interface.h"
#include "../HAL/CLCD_interface.h"


u8 CheckOperation(u8 op);
u8 checkDoubleOper(u8 par1,u8 par2,u8 *MultiSign);
void ResultOfOperations(u16 x,u16 y,u8 op);
u8 signOfDigit2;
void main()
{
	PORT_voidInit();
	CLCD_voidInit();

	u8 multi=1;
	u16 op1=0;
	u16 op2=0;
	char oper=0;
	u8 key=0,operOfDigit2=0,frist = 0,ErrorFlag = 0;
	while(1)
	{
		do{
			key = KPD_u8Key_pressed();
			if((0<=key)&&(key<=9))
			{
				CLCD_voidWriteNumber(key);
				op1 =multi*op1 +key;
				multi = 10;
			}
			else if(key == 'C') {CLCD_voidSendCommand(1);multi=1; op1 = 0;}
		}while(CheckOperation(key)==0);
		multi=1;
		oper=key;
		CLCD_voidSendData(key);
		do{
			key = KPD_u8Key_pressed();
			if(key=='=') {CLCD_voidSendData('=');break;}
			if((0<=key)&&(key<=9))
			{
				frist=1;
				CLCD_voidWriteNumber(key);
				op2 =multi*op2 +key;
				multi = 10;
				key = KPD_NO_PRESSED_KEY;
			}
			else if(CheckOperation(key))
			{
				signOfDigit2 = 1;
				operOfDigit2 = checkDoubleOper(oper,key,&signOfDigit2);
				CLCD_voidSendData(key);
				if(operOfDigit2==0)
				{
					ErrorFlag = 1;
				}
				else
				{
					oper = operOfDigit2;
					key = KPD_NO_PRESSED_KEY;
				}
			}
			else if(key == 'C') {CLCD_voidSendCommand(1);multi=1;op2 = 0;}
		}while(key == KPD_NO_PRESSED_KEY);
		multi=1;
		if((frist==1)&&(ErrorFlag == 0))
		{
			frist=0;
			ResultOfOperations(op1,op2,oper);
		}
		else
		{
			CLCD_voidSendCommand(1);
			ErrorFlag = 0;
			CLCD_voidSendString("error");

		}
		do{
			if(key == 'C') {CLCD_voidSendCommand(1);multi=1;op2 = 0;op1 = 0;}
		}while(key == KPD_NO_PRESSED_KEY);
		op2 = 0;op1 = 0;oper=0;multi=1;
	}

}
void ResultOfOperations(u16 x,u16 y,u8 op)
{
	u16 result=0;
	u8 e;
	u8 count=0;
	u16 n1,s;
	switch(op){
	case '+':
		result = x+y;
		CLCD_voidWriteNumber(result);
		break;
	case '-':
		if(x<y)
		{
			result = (y-x);
			CLCD_voidSendData('-');
		}
		else
			result = x-y;
		CLCD_voidWriteNumber(result);
		break;
	case '*':
		result = x*y;
		if(signOfDigit2=='-')
			CLCD_voidSendData('-');
		CLCD_voidWriteNumber(result);
		signOfDigit2=1;
		break;
	case '/':
		if(y==0)
		{
			CLCD_voidSendString("inf");
			break;
		}
		if(signOfDigit2=='-')
			CLCD_voidSendData('-');
		signOfDigit2=1;
		e=x/y;
		s=x%y;
		if(s==0)
		{
			CLCD_voidWriteNumber(e);
		}
		else{
			CLCD_voidWriteNumber(e);
			CLCD_voidSendData('.');
			do{
				n1=(u16)((u16)x % (u16)y);
				n1 *= 10;
				s=(n1/(u16)y);
				e=(n1%(u16)y);
				CLCD_voidWriteNumber(s);
				x=n1;
				count++;
			}while((e!=0)&&(count!=3));
		}
		break;
	}
}

u8 checkDoubleOper(u8 par1,u8 par2,u8 *M)
{
	if(((par1=='+')&&(par2=='+'))||((par1=='-')&&(par2=='-')))
	{
		return '+';
	}
	else if(((par1=='-')&&(par2=='+'))||((par1=='+')&&(par2=='-')))
	{
		return '-';
	}
	else if(((par1=='*')&&(par2=='-')))
	{
		*M = '-';
		return '*';
	}
	else if((par1=='/')&&(par2=='-'))
	{
		*M = '-';
		return '/';
	}
	else if(((par1=='*')&&(par2=='+')))
	{
		*M = '+';
		return '*';
	}
	else if((par1=='/')&&(par2=='+'))
	{
		*M = '+';
		return '/';
	}
	return 0;
}
u8 CheckOperation(u8 op)
{
	switch(op)
	{
		case '+':
		case '-':
		case '*':
		case '/':return 1;break;
		default :return 0;
	}
}

