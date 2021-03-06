/*
 * Timer_config.h
 *
 *  Created on: Apr 28, 2021
 *      Author: ceto2
 */

#ifndef HAL_TIMER_TIMER_CONFIG_H_
#define HAL_TIMER_TIMER_CONFIG_H_

/*
 * options:-
 *       Normal
 *       PWM Phase Correct
 *       CTC
 *		 Fast PwM
 * */

#define Timer0_WaveFormMode Normal
/*
 * options:-
 *       Normal
 *		 Toggle
 *       Clear
 *		 Set
 * */

#define Timer0_CompareOutputMode Normal
/*
 * options:-
 *       NoClock
 *		 CLK
 *		 CLK8
 *		 CLK64
 *		 CLK5265
 *		 CLK1024
 *		 EXTF
 *		 EXTR
 * */

#define Timer0_ClockMode Normal
/*
 * options:-
 *		 Overflow
 *		 OCR
 * */
#define TIMER0_IntrrupMode Overflow
#endif /* HAL_TIMER_TIMER_CONFIG_H_ */
