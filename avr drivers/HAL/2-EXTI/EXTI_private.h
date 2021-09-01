/*
 * EXTI_private.h
 *
 *  Created on: Apr 15, 2021
 *      Author: ceto2
 */

#ifndef MCAL_2_EXTI_EXTI_PRIVATE_H_
#define MCAL_2_EXTI_EXTI_PRIVATE_H_


/* EXTERNAL INTERRUPT 0 BITS*/
#define GICR_INT0_BIT	6
#define MCUCR_ISC00_BIT	0
#define MCUCR_ISC01_BIT	1
#define GIFR_INTF0_BIT	6

/* EXTERNAL INTERRUPT 1 BITS*/
#define GICR_INT1_BIT	7
#define MCUCR_ISC10_BIT	2
#define MCUCR_ISC11_BIT	3
#define GIFR_INTF1_BIT	7

/* EXTERNAL INTERRUPT 2 BITS*/
#define GICR_INT2_BIT	5
#define MCUCSR_ISC2_BIT	2
#define GIFR_INTF2_BIT	5

#define GIFR_REG *((volatile u8 *)0X5A)
// enable PIE for certain interrupt
#define GICR_REG *((volatile u8 *)0x5B)
// CONTROLE Sense for INT0 AND INT1
#define MCUCR_REG *((volatile u8 *)0x55)
// CONTROLE Sense for INT2
#define MCUCSR_REG *((volatile u8 *)0x54)

#define NULL 0
void __vector_1(void) __attribute__((signal));
void __vector_2(void) __attribute__((signal));
void __vector_3(void) __attribute__((signal));

void EXTI_voidChangeSense(u8 Copy_u8SenseMode, u8 Copy_u8Pin1, u8 Copy_u8Pin2);
void EXTI_voidChangeSenseInt2(u8 Copy_u8SenseMode, u8 Copy_u8Pin);
#endif /* MCAL_2_EXTI_EXTI_PRIVATE_H_ */
