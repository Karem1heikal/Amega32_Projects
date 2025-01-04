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
#include "../MCAL/EXTI_interface.h"
#include "../MCAL/ADC_interface.h"
#include "../MCAL/GIE_interface.h"
#include "../MCAL/TIMER_interface.h"

#include "../HAL/SERVO_interface.h"
#include "../HAL/STEP_MOTOR_interface.h"
#include "../HAL/CLCD_interface.h"
#include "../HAL/KPD_interface.h"




u32 AppMap(u32 InMin,u32 InMax,u32 OutMin,u32 OutMax,u32 InVal)
{
	u32 Local=0;
	Local = (((InVal-InMin)*(OutMax-OutMin))/(InMax-InMin))+OutMin;
	return Local;
}

#define DC_MOTOR		1
#define STEPPER_MOTOR	2
#define SERVO_MOTOR		3

void main()
{
	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	u16 Local_data;
	u16 mapVal = 0;
	u8 Keypress=0;
	s8 trials = 3,count=0,multi = 1 ,BackSpace = 12;
	//voltage in milli ,password Storage variable
	u16  Angle1=0,Enter_password=0,defult_pass=1234,multiplier=1;
	CLCD_voidSendCommand(1);
	CLCD_voidSendString("Welcome Sr");
	_delay_ms(500);
	STEP_t step1 ={DIO_PORTA,STEP_UPPER_NIBBLE,STEP_COUNTER_CLOCKWISE,180};
	Timer_t t0={
			TIMER0,TIMER0_PHASE_CORRECT_PWM,OC0_DIS,TIMER10_DIV_1024,TIMER0_INT_DISABLE
	};
	Timer_t t2={
			TIMER2,TIMER2_PHASE_CORRECT_PWM,OC2_DIS,TIMER2_DIV_1024,TIMER2_INT_DISABLE
	};
	TIMER_voidInit(&t2);
	TIMER_voidInit(&t0);
	while(1)
	{
		CLCD_voidSendCommand(1);
		CLCD_voidSendString("Enter pass:"); // 4 Digit for password
		do{
			do{
				Keypress=KPD_u8Key_pressed();
			}while(Keypress==0xff);
			if((0<=Keypress)&&(Keypress<=9)){
				CLCD_voidWriteNumber(Keypress);
				_delay_ms(100);
				CLCD_voidGoToXY(0,BackSpace-1);
				BackSpace++;
				CLCD_voidSendData('*');
				Enter_password=Enter_password*multiplier+Keypress;
				multiplier=10;
			}
		}while(Keypress!='C');
		if(Enter_password==defult_pass) // pass
		{
			CLCD_voidSendCommand(1);
			CLCD_voidSendString("welcome to Motor");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("  Dashbroad ");
			_delay_ms(500);
			CLCD_voidSendCommand(1);
			while(1)
			{
				CLCD_voidGoToXY(0,0);
				CLCD_voidSendString(" Choose Motor");
				_delay_ms(500);
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("1-DC 2- Stepper");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("3- Servo");
				do{
					Keypress = KPD_u8Key_pressed();
					if((1<=Keypress)&&(Keypress<=3))
					{
						break;
					}
					else
						Keypress = KPD_NO_PRESSED_KEY;

				}while(Keypress == KPD_NO_PRESSED_KEY);

				switch(Keypress)
				{
				case DC_MOTOR:
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("Choose Direct");
					_delay_ms(500);
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("1-Rotate CCW");
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("2-Rotate CW");
					do{
						Keypress = KPD_u8Key_pressed();
						if((1<=Keypress)&&(Keypress<=2))
						{
							break;
						}
						else
							Keypress = KPD_NO_PRESSED_KEY;

					}while(Keypress == KPD_NO_PRESSED_KEY);
					if(1==Keypress)  // Rotate CCW
					{
						CLCD_voidSendCommand(1);
						CLCD_voidSendString("Speed Control");
						_delay_ms(500);
						CLCD_voidSendCommand(1);
						CLCD_voidSendString("  1-FullSpeed");
						CLCD_voidGoToXY(1,0);
						CLCD_voidSendString("2- POT 3- LM35");

						do{
							Keypress = KPD_u8Key_pressed();
							if((1<=Keypress)&&(Keypress<=3))
							{
								break;
							}
							else
								Keypress = KPD_NO_PRESSED_KEY;
						}while(Keypress == KPD_NO_PRESSED_KEY);


						if(1==Keypress)		// FullSpeed
						{
							CLCD_voidSendCommand(1);
							CLCD_voidSendString("  1-FullSpeed");
							CLCD_voidGoToXY(1,0);
							CLCD_voidSendString("any key for out");
							do{
								Keypress= KPD_u8Key_pressed();
								DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
							}while(Keypress==KPD_NO_PRESSED_KEY);
							DIO_u8SetPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
						}
						else if(2==Keypress) // POT
						{
							t0.CompOutMode = OC0_SET_UP_CLR_DOWN;
							TIMER0_voidCompOutModeChange(&t0);
							CLCD_voidSendCommand(1);
							do{
								Keypress = KPD_u8Key_pressed();
								if(Keypress=='C')
									break;
								else
									Keypress = KPD_NO_PRESSED_KEY;
								ADC_u8StartSingleConvPoll(ADC3,&Local_data);
								CLCD_voidGoToXY(0,0);
								CLCD_voidSendString(" Speed :");
								CLCD_voidGoToXY(1,0);
								CLCD_voidWriteNumber(255-Local_data);
								CLCD_voidSendString(" RPM");
								TIMER0_voidSetCompMatchValue(Local_data);
								_delay_ms(100);
								CLCD_voidGoToXY(1,0);
								CLCD_voidSendString("       ");
							}while(Keypress == KPD_NO_PRESSED_KEY);
							t0.CompOutMode = OC0_DIS;
							TIMER0_voidCompOutModeChange(&t0);
						}
						else if(3==Keypress) // Lm35
						{
							t0.CompOutMode = OC0_SET_UP_CLR_DOWN;
							TIMER0_voidCompOutModeChange(&t0);
							CLCD_voidSendCommand(1);
							do{
								Keypress = KPD_u8Key_pressed();
								if(Keypress=='C')
									break;
								else
									Keypress = KPD_NO_PRESSED_KEY;
								ADC_u8StartSingleConvPoll(ADC1,&Local_data);
								Local_data = (u16)(((u32)(Local_data*5000UL))/256UL);
								Local_data /=100;
								CLCD_voidGoToXY(0,0);
								CLCD_voidSendString("Current Temp:");
								CLCD_voidGoToXY(1,0);
								CLCD_voidWriteNumber(Local_data);
								mapVal = AppMap(27,42,0,255,Local_data);
								CLCD_voidGoToXY(0,0);
								if((255-mapVal)<=255)
									TIMER0_voidSetCompMatchValue(255-mapVal);
								_delay_ms(100);
								CLCD_voidGoToXY(1,0);
								CLCD_voidSendString("       ");
							}while(Keypress == KPD_NO_PRESSED_KEY);
							t0.CompOutMode = OC0_DIS;
							TIMER0_voidCompOutModeChange(&t0);

						}
					}
					else if(2==Keypress)  // Rotate CW
					{
						CLCD_voidSendCommand(1);
						CLCD_voidSendString("Speed Control");
						_delay_ms(500);
						CLCD_voidSendCommand(1);
						CLCD_voidSendString("  1-FullSpeed");
						CLCD_voidGoToXY(1,0);
						CLCD_voidSendString("2- POT 3- LM35");
						do{
							Keypress = KPD_u8Key_pressed();
							if((1<=Keypress)&&(Keypress<=3))
							{
								break;
							}
							else
								Keypress = KPD_NO_PRESSED_KEY;

						}while(Keypress == KPD_NO_PRESSED_KEY);
						if(1==Keypress)		// FullSpeed
						{
							CLCD_voidSendCommand(1);
							CLCD_voidSendString("  1-FullSpeed");
							CLCD_voidGoToXY(1,0);
							CLCD_voidSendString("any key for out");
							do{
								Keypress= KPD_u8Key_pressed();
								DIO_u8SetPinValue(DIO_PORTD,DIO_PIN7,DIO_PIN_HIGH);
							}while(Keypress==KPD_NO_PRESSED_KEY);
							DIO_u8SetPinValue(DIO_PORTD,DIO_PIN7,DIO_PIN_LOW);
						}
						else if(2 == Keypress)  // POT
						{
							t2.CompOutMode = OC2_SET_UP_CLR_DOWN;
							TIMER2_voidCompOutModeChange(&t2);
							CLCD_voidSendCommand(1);
							do{
								Keypress = KPD_u8Key_pressed();
								if(Keypress=='C')
									break;
								else
									Keypress = KPD_NO_PRESSED_KEY;
								ADC_u8StartSingleConvPoll(ADC3,&Local_data);
								CLCD_voidGoToXY(0,0);
								CLCD_voidSendString(" Speed : ");
								CLCD_voidGoToXY(1,0);
								CLCD_voidWriteNumber(255 - Local_data);
								CLCD_voidSendString(" RPM");
								TIMER2_voidSetCompMatchValue(Local_data);
								_delay_ms(100);
								CLCD_voidGoToXY(1,0);
								CLCD_voidSendString("       ");
							}while(Keypress == KPD_NO_PRESSED_KEY);
							t2.CompOutMode = OC2_DIS;
							TIMER2_voidCompOutModeChange(&t2);
						}
						else if(3 == Keypress) //LM35
						{
							t2.CompOutMode = OC2_SET_UP_CLR_DOWN;
							TIMER2_voidCompOutModeChange(&t2);
							CLCD_voidSendCommand(1);
							do{
								Keypress = KPD_u8Key_pressed();
								if(Keypress=='C')
									break;
								else
									Keypress = KPD_NO_PRESSED_KEY;
								ADC_u8StartSingleConvPoll(ADC1,&Local_data);
								Local_data = (u16)(((u32)(Local_data*5000UL))/256UL);
								Local_data /=100;
								CLCD_voidGoToXY(0,0);
								CLCD_voidSendString("Current Temp: ");
								CLCD_voidGoToXY(1,0);
								CLCD_voidWriteNumber(Local_data);
								mapVal = AppMap(27,42,0,255,Local_data);
								CLCD_voidGoToXY(0,0);
								if((255-mapVal)<=255)
									TIMER2_voidSetCompMatchValue(255-mapVal);
								_delay_ms(100);
								CLCD_voidGoToXY(1,0);
								CLCD_voidSendString("       ");
							}while(Keypress == KPD_NO_PRESSED_KEY);
							t2.CompOutMode = OC2_DIS;
							TIMER2_voidCompOutModeChange(&t2);
						}
					}
					break;
				case STEPPER_MOTOR:
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("1)Rotate CCW");
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("2)Rotate CW");
					do{
						Keypress = KPD_u8Key_pressed();
						if(1==Keypress)
						{
							step1.Diraction = STEP_COUNTER_CLOCKWISE;
						}
						else if(2==Keypress)
						{
							step1.Diraction = STEP_CLOCKWISE;
						}
						else
							Keypress = KPD_NO_PRESSED_KEY;
					}while(Keypress == KPD_NO_PRESSED_KEY);
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("EnterAngle:   *C");
					CLCD_voidGoToXY(0,11);
					do{
						Keypress = KPD_u8Key_pressed();
						if((0<=Keypress)&&(Keypress<=9))
						{
							if(count<3)
							{
								CLCD_voidWriteNumber(Keypress);
								Angle1 = Angle1*multi+Keypress ;
								multi=10;
								count++;
								Keypress = KPD_NO_PRESSED_KEY;
							}
							else
								Keypress = KPD_NO_PRESSED_KEY;
						}
						if(Keypress == '=')
							break;
					}while((Keypress == KPD_NO_PRESSED_KEY));
					count=0;
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("Motor Started");
					step1.AngleDegree = Angle1;
					CLCD_voidWriteNumber(Angle1);
					if(STEP_MOTORu8StartFullMode(&step1)==0)
					{
						CLCD_voidSendCommand(1);
						CLCD_voidSendString("Angle Reached");
						_delay_ms(500);
					}
					Angle1 = 0;
					break;
				case SERVO_MOTOR:
					SERVO_voidInit();
					SERVO_voidSetAngle(0);
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("EnterAngle:   *C");
					CLCD_voidGoToXY(0,11);
					do{
						Keypress = KPD_u8Key_pressed();
						if((0<=Keypress)&&(Keypress<=9))
						{
							if(count<3)
							{
								CLCD_voidWriteNumber(Keypress);
								Angle1 = Angle1*multi+Keypress ;
								multi=10;
								count++;
								Keypress = KPD_NO_PRESSED_KEY;
							}
							else
								Keypress = KPD_NO_PRESSED_KEY;
						}
						if(Keypress == '=')
							break;
					}while((Keypress == KPD_NO_PRESSED_KEY));
					count=0;
					CLCD_voidSendCommand(1);
					CLCD_voidSendString("Motor Started");
					for(count =0; count<127;count++)
					SERVO_voidSetAngle(Angle1);
					count = 0;
					_delay_ms(100);
					CLCD_voidSendCommand(1);
					Angle1 = 0;
					break;
				}
			}
		}
		else
		{
			BackSpace=12;
			trials--;
			if(trials==0)
			{
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("    ShutDown");
				CLCD_voidGoToXY(1,9);
				CLCD_voidSendData('3');
				_delay_ms(500);
				CLCD_voidGoToXY(1,9);
				CLCD_voidSendData('2');
				_delay_ms(500);
				CLCD_voidGoToXY(1,9);
				CLCD_voidSendData('1');
				_delay_ms(500);
				CLCD_voidSendCommand(1);
				trials = 3;
				multiplier=1;
				Enter_password = 0;
				_delay_ms(500);
				break;
			}
			else{
				BackSpace = 12;
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("    Try Again!");
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Trials : ");
				CLCD_voidGoToXY(1,9);
				CLCD_voidWriteNumber(trials);
				_delay_ms(500);
				// Initial Values
				multiplier=1;
				Enter_password = 0;
			}
		}
	}
	_delay_ms(500);
	CLCD_voidSendCommand(1);


	while(1);
}


