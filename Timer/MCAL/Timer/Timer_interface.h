/*
 * Timer_interface.h
 *
 *  Created on: Apr 28, 2021
 *      Author: ceto2
 */

#ifndef HAL_TIMER_TIMER_INTERFACE_H_
#define HAL_TIMER_TIMER_INTERFACE_H_

/*      TIMER 0 FUNCTIONS	 			     */
void TIMER0_voidSecondsDelay (f32 Copy_u8Seconds);
void TIMER0_voidMSecondsDelay(f32 Copy_u8MSeconds);
void TIMER0_voidUSecondsDelay(f32 Copy_u8USeconds);

/*      TIMER 2 FUNCTIONS     			     */
void TIMER2_voidSecondsDelay (f32 Copy_u8Seconds);
void TIMER2_voidMSecondsDelay(f32 Copy_u8MSeconds);
void TIMER2_voidUSecondsDelay(f32 Copy_u8USeconds);

#endif /* HAL_TIMER_TIMER_INTERFACE_H_ */
