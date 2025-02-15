/*********************************************************************************/
/*********************************************************************************/
/************************* Author : karem heikal **********************************/
/************************* layer  : LIB          **********************************/
/************************* SWC    : BIT          **********************************/
/************************* Version: 1.00         **********************************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var,no) (var|=(1<<no))
#define CLR_BIT(var,no) (var&=(~(1<<no)))
#define TOG_BIT(var,no) (var^=(1<<no))
#define GET_BIT(var,no) ((var>>no)&1)


#define Map(InMin,InMax,OutMin,OutMax,InVal)	 	(((InVal-InMin)*(OutMax-OutMin))/(InMax-InMin))+OutMin
#endif
