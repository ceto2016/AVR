/*
 * EXTI_config.h
 *
 *  Created on: Apr 15, 2021
 *      Author: ceto2
 */

#ifndef MCAL_2_EXTI_EXTI_CONFIG_H_
#define MCAL_2_EXTI_EXTI_CONFIG_H_
#define EXTI_LINE_Pin

/*
 * OPTIONS:-
 * 		EXTI_FALLING_EDGE
 * 		EXTI_RISING_EDGE
 *		EXTI_LOW_LEVEL
 *		EXTI_ON_CHANGE
 */
#define EXTI_u8Line0_Mode			EXTI_RISING_EDGE
#define EXTI_u8Line1_Mode			EXTI_RISING_EDGE

/*
 * OPTIONS:-
 * 		EXTI_FALLING_EDGE
 * 		EXTI_RISING_EDGE
 */

#define EXTI_u8Line2_Mode			EXTI_RISING_EDGE


#endif /* MCAL_2_EXTI_EXTI_CONFIG_H_ */
