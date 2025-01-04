/*
 * TIMER_interface.h
 *
 *  Created on: Aug 7, 2024
 *      Author: user
 */

#ifndef MCAL_TIMER_INTERFACE_H_
#define MCAL_TIMER_INTERFACE_H_

typedef struct
{
	u8 TimerNum;
	u8 TimerMode;
	u8 CompOutMode;
	u8 ClockSel;
	u8 IntEnable;
	u8 ICU_EdgeSel;
	//void (* Notifiction)();
} Timer_t;
#define TIMER0		0
#define TIMER1		1
#define TIMER2		2

#define TIMER0_NORMAL				0
#define TIMER0_CTC					1
#define TIMER0_FAST_PWM				2
#define TIMER0_PHASE_CORRECT_PWM	3


/**  Compare Output Mode, non-PWM Mode Description
 *   option:
 *    1- Normal port operation, OC0 disconnected.
 *    2- Toggle OC0 on compare match
 *    3- Clear OC0 on compare match
 *    4- Set OC0 on compare match
 *
 */

#define OC0_DIS					0
#define OC0_TOG					1
#define OC0_CLR					2
#define OC0_SET					3

#define TIMER10_NO_CLK			    0
#define TIMER10_DIV_1			    1
#define TIMER10_DIV_8			    2
#define TIMER10_DIV_64			    3
#define TIMER10_DIV_256			    4
#define TIMER10_DIV_1024			5
#define TIMER10_EXT_FALLING_EDGE	6
#define TIMER10_EXT_RISING_EDGE	    7

#define TIMER0_INT_ENABLE		   	1
#define TIMER0_INT_DISABLE			0


/*
 * fast PWM mode
 *  options:
 *	1-OC0 Disconnect
 *	2-OC0_CLR_ON_COMP_SET_AT_TOP
 *  3-OC0_SET_ON_COMP_CLR_AT_TOP
 * */

#define OC0_CCST		2
#define OC0_SCCT		3


/*
 * Compare Output Mode, Phase Correct PWM Mode
 *   options:
 *		1- Normal port operation, OC0 disconnected.
 *
 *		2- Clear OC0 on compare match when up-counting. Set OC0 on compare
 *		   match when downcounting.
 *      3- Set OC0 on compare match when up-counting. Clear OC0 on compare
 *         match when downcounting.
 *
 * */

#define OC0_CLR_UP_SET_DOWN		2
#define OC0_SET_UP_CLR_DOWN		3

void TIMER_voidInit(Timer_t* Copy_Timer);

void TIMER0_voidSetPreloadValue(u8 Copy_u8PreloadValue);

void TIMER0_voidSetCompMatchValue(u8 Copy_u8CompVal);

u8 TIMER0_u8SetCallBack(Timer_t *Copy_Timer,void (*Notifiction)());

//void  TIMER0_voidSetPWMFixedTop(u8 Copy_u8DutyCycle);


/* TIMER1_NORMAL 			==>  Normal
 * TIMER1_PHASE_CORR_8BIT   ==>  PWM, Phase Correct, 8-bit
 * TIMER1_PHASE_CORR_9BIT   ==>  PWM, Phase Correct, 9-bit
 * TIMER1_PHASE_CORR_10BIT  ==>  PWM, Phase Correct, 10-bit
 * TIMER1_CTC 				==>  CTC
 * TIMER1_FAST_PWM_8        ==>  Fast PWM, 8-bit
 * TIMER1_FAST_PWM_9        ==>  Fast PWM, 9-bit
 * TIMER1_FAST_PWM_10	    ==>  Fast PWM, 10-bit
 * TIMER1_IC_FREQ_CORR      ==>  PWM, Phase and Frequency Correct
 * TIMER1_CM_FREQ_CORR      ==>  PWM, Phase and Frequency Correct
 * TIMER1_IC_PHASE_CORR     ==>  PWM, Phase Correct
 * TIMER1_CM_PHASE_CORR     ==>  PWM, Phase Correct
 * TIMER1_IC_CTC            ==>  CTC
 * TIMER1_ 					==>  Reserved
 * TIMER1_IC_FAST_PWM       ==>  Fast PWM
 * TIMER1_CM_FAST_PWM       ==>  Fast PWM
 *
 *
 *
 * */


#define TIMER1_NORMAL 			     0
#define TIMER1_PHASE_CORR_8BIT       1
#define TIMER1_PHASE_CORR_9BIT       2
#define TIMER1_PHASE_CORR_10BIT      3
#define TIMER1_CTC 				     4
#define TIMER1_FAST_PWM_8            5
#define TIMER1_FAST_PWM_9            6
#define TIMER1_FAST_PWM_10	         7
#define TIMER1_IC_FREQ_CORR          8
#define TIMER1_CM_FREQ_CORR          9
#define TIMER1_IC_PHASE_CORR         10
#define TIMER1_CM_PHASE_CORR         11
#define TIMER1_IC_CTC                12

#define TIMER1_IC_FAST_PWM           14
#define TIMER1_CM_FAST_PWM           15


/**  Compare Output Mode, non-PWM Mode Description
 *   option:
 *    1- Normal port operation, OC1A/OC1B disconnected.
 *    2- Toggle OC1A/OC1B on compare match
 *    3- Clear OC1A/OC1B on compare match (Set
 *       output to low level)
 *    4- Set OC1A/OC1B on compare match (Set
 *       output to high level)
 *
 *
 */

#define OC1A_DIS    (0<<2)
#define OC1A_TOG    (1<<2)
#define OC1A_CLR    (2<<2)
#define OC1A_SET    (3<<2)

#define OC1B_DIS     0
#define OC1B_TOG     1
#define OC1B_CLR     2
#define OC1B_SET     3

/*
 * Compare Output Mode, Fast PWM
 * options:
 * 		1- Normal port operation, OC1A/OC1B disconnected.
 *
 * 		2- WGM13:0 = 15: Toggle OC1A on Compare
 * 		  Match, OC1B disconnected (normal port
 *        operation).
 *        For all other WGM13:0 settings, normal port
 *        operation, OC1A/OC1B disconnected.
 *      3- Clear OC1A/OC1B on compare match, set
 *        OC1A/OC1B at TOP
 *      4- Set OC1A/OC1B on compare match, clear
 *        OC1A/OC1B at TOP
 * */
#define OC1A_CCST    (2<<2)
#define OC1A_SCCT    (3<<2)

#define OC1B_CCST    2
#define OC1B_SCCT    3


/*
 * Compare Output Mode, Phase Correct and Phase and Frequency Correct PWM
 *  options:
 *  	1- Normal port operation, OC1A/OC1B disconnected.
 *
 * 		2- WGM13:0 = 9 or 14: Toggle OC1A on
 * 		  Compare Match, OC1B disconnected (normal
 *        port operation).
 *        For all other WGM13:0 settings, normal port
 *        operation, OC1A/OC1B disconnected.
 *      3- Clear OC1A/OC1B on compare match when
 *        up-counting. Set OC1A/OC1B on compare
 *        match when downcounting.
 *      4- Set OC1A/OC1B on compare match when upcounting.
 *        Clear OC1A/OC1B on compare
 *        match when downcounting.
 * */

#define OC1A_SET_UP_CLR_DOWN	(3<<2)
#define OC1A_CLR_UP_SET_DOWN	(2<<2)
#define OC1B_SET_UP_CLR_DOWN 	3
#define OC1B_CLR_UP_SET_DOWN 	2

#define TIMER1_IC_INT_ENABLE		(1<<3)
#define TIMER1_IC_INT_DISABLE		(0<<3)

#define TIMER1A_INT_ENABLE		   	(1<<2)
#define TIMER1A_INT_DISABLE			(0<<2)

#define TIMER1B_INT_ENABLE			(1<<1)
#define TIMER1B_INT_DISABLE			(0<<1)

#define TIMER1_OVF_INT_ENABLE			1
#define TIMER1_OVF_INT_DISABLE			0

#define ICU_FALLING_EDGE 				0
#define ICU_RISING_EDGE 				1

void TIMER1_voidSetICR(u16 Copy_u16Top);

void TIMER1_voidSetPreloadValue(u16 Copy_u16PreloadValue);

u16 TIMER1_u16ReadTimerValue();

void TIMER1_voidSetChannelACompMatch(u16 Copy_u16CompVal);

void TIMER1_voidSetChannelBCompMatch(u16 Copy_u16CompVal);

u8 TIMER1_u8SetCallBack(Timer_t *Copy_Timer,void(*Notifiction)());

void TIMER1_voidDisableOvfInterrupt();

void ICU_voidInit();

u16 ICU_u16ReadInputCapture();

u8 ICU_u8CaptureEdgeSelect(u8 Copy_u8CapEdge);

void ICU_voidInterruptEnable();

void ICU_voidInterruptDisable();

u8 ICU_u8SetCallBack(void (*Notifiction)());


#define TIMER2_NORMAL				0
#define TIMER2_CTC					1
#define TIMER2_FAST_PWM				2
#define TIMER2_PHASE_CORRECT_PWM	3


/**  Compare Output Mode, non-PWM Mode Description
 *   option:
 *    1- Normal port operation, OC2 disconnected.
 *    2- Toggle OC2 on compare match
 *    3- Clear OC2 on compare match
 *    4- Set OC2 on compare match
 *
 */

#define OC2_DIS					0
#define OC2_TOG					1
#define OC2_CLR					2
#define OC2_SET					3

#define TIMER2_NO_CLK			    0
#define TIMER2_DIV_1			    1
#define TIMER2_DIV_8			    2
#define TIMER2_DIV_32			    3
#define TIMER2_DIV_64			    4
#define TIMER2_DIV_128			    5
#define TIMER2_DIV_256			    6
#define TIMER2_DIV_1024			    7

#define TIMER2_INT_ENABLE		   	1
#define TIMER2_INT_DISABLE			0


/*
 * fast PWM mode
 *  options:
 *	1-OC2 Disconnect
 *	2-OC2_CLR_ON_COMP_SET_AT_TOP
 *  3-OC2_SET_ON_COMP_CLR_AT_TOP
 * */

#define OC2_CCST		2
#define OC2_SCCT		3


/*
 * Compare Output Mode, Phase Correct PWM Mode
 *   options:
 *		1- Normal port operation, OC2 disconnected.
 *
 *		2- Clear OC2 on compare match when up-counting. Set OC2 on compare
 *		   match when downcounting.
 *      3- Set OC2 on compare match when up-counting. Clear OC2 on compare
 *         match when downcounting.
 *
 * */

#define OC2_CLR_UP_SET_DOWN		2
#define OC2_SET_UP_CLR_DOWN		3

#define TIMER_DELAY_PERIODIC		1
#define TIMER_DELAY_NOT_PERIODIC	2

void TIMER2_voidSetPreloadValue(u8 Copy_u8PreloadValue);

void TIMER2_voidSetCompMatchValue(u8 Copy_u8CompVal);

u8 TIMER2_u8SetCallBack(Timer_t *Copy_Timer,void (*Notifiction)());

/*
 * Function Name : 	TIMER_u8Scheduler
 * Input Parameters:	Copy_u16Delay_ms, pointer to Notifiction,  Copy_u8Periodic
 * return : 	Local_ErrorState
 * Function Use: function to time delay asynchronously without polling
 *
 * Note : before calling this function, Enable global interrupt
 * */

u8 TIMER_u8Scheduler(u16 Copy_u16Delay_ms,void  (*Notifiction)(),u8 Copy_u8Periodic);

#endif /* MCAL_TIMER_INTERFACE_H_ */
