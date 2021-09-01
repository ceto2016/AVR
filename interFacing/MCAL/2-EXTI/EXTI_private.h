/*
 * EXTI_private.h
 *
 *  Created on: Apr 15, 2021
 *      Author: ceto2
 */

#ifndef MCAL_2_EXTI_EXTI_PRIVATE_H_
#define MCAL_2_EXTI_EXTI_PRIVATE_H_

#define GIFR *((volatile u8 *)0X5A)
// enable PIE for certain interrupt
#define GICR *((volatile u8 *)0x5B)
// CONTROLE Sense for INT0 AND INT1
#define MCUCR *((volatile u8 *)0x55)
// CONTROLE Sense for INT2
#define MCUCSR *((volatile u8 *)0x54)

#define NULL 0
void __vector_1(void) __attribute__((signal));
void __vector_2(void) __attribute__((signal));
void __vector_3(void) __attribute__((signal));
void EXTI_voidChangeSense(EXTISense Copy_u8SenseMode, u8 Copy_u8Pin1, u8 Copy_u8Pin2);
void EXTI_voidChangeSenseInt2(EXTISense Copy_u8SenseMode, u8 Copy_u8Pin);
#endif /* MCAL_2_EXTI_EXTI_PRIVATE_H_ */

