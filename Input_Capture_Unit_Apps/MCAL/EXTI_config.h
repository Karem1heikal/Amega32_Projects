/*
 * EXTI_config.h
 *
 *  Created on: Jul 23, 2024
 *      Author: user
 */

#ifndef MCAL_EXTI_CONFIG_H_
#define MCAL_EXTI_CONFIG_H_

/*
 * The External Interrupt 0 is activated by the external pin INT0
 * Options:
 *
 *   1-EXTI0_LOW_LEVEL 		=> The low level of INT0 generates an interrupt request.
 *   2-EXTI0_ON_CHANGE 		=> Any logical change on INT0 generates an interrupt request.
 *   3-EXTI0_FALLING_ADGE 	=> The falling edge of INT0 generates an interrupt request.
 *   4-EXTI0_RISING_ADGE 	=> The rising edge of INT0 generates an interrupt request.
 *
 * */

#define EXTI0_SENCECONTROL		EXTI0_RISING_ADGE

/*
 * The External Interrupt 1 is activated by the external pin INT1
 * Options:
 *
 *   1-EXTI1_LOW_LEVEL 		=> The low level of INT1 generates an interrupt request.
 *   2-EXTI1_ON_CHANGE 		=> Any logical change on INT1 generates an interrupt request.
 *   3-EXTI1_FALLING_ADGE 	=> The falling edge of INT1 generates an interrupt request.
 *   4-EXTI1_RISING_ADGE 	=> The rising edge of INT1 generates an interrupt request.
 *
 * */

#define EXTI1_SENCECONTROL		EXTI1_FALLING_ADGE


/*
 * The External Interrupt 2 is activated by the external pin INT2
 * Options:
 *
 *   3-EXTI2_FALLING_ADGE 	=> The falling edge of INT2 generates an interrupt request.
 *   4-EXTI2_RISING_ADGE 	=> The rising edge of INT2 generates an interrupt request.
 *
 * */

#define EXTI2_SENCECONTROL		EXTI2_FALLING_ADGE

#endif /* MCAL_EXTI_CONFIG_H_ */
