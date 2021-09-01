/*
 * EXTI_interface.c
 *
 *  Created on: Apr 15, 2021
 *      Author: ceto2
 */

#ifndef MCAL_2_EXTI_EXTI_INTERFACE_C_
#define MCAL_2_EXTI_EXTI_INTERFACE_C_

#define EXTI_FALLING_EDGE	0
#define EXTI_RISING_EDGE	1
#define EXTI_LOW_LEVEL		2
#define EXTI_ON_CHANGE		3

#define EXTI_LINE0 0
#define EXTI_LINE1 1
#define EXTI_LINE2 2

void EXTI_voidInit        	  (void);
void EXTI_voidEnable      	  (u8 Copy_u8EXTILine , u8 Copy_EXTISense);
void EXTI_voidDisable         (u8 Copy_u8EXTILine);
void EXTI_voidClearFlag       (u8 Copy_u8EXTILine);

void EXTI_voidSetCallBack     (void (* Copy_pvoidCallBack)(void), u8 Copy_u8EXTILine);

#endif /* MCAL_2_EXTI_EXTI_INTERFACE_C_ */
