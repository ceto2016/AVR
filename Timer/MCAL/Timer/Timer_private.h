/*
 * Timer_private.h
 *
 *  Created on: Apr 28, 2021
 *      Author: ceto2
 */

#ifndef HAL_TIMER_TIMER_PRIVATE_H_
#define HAL_TIMER_TIMER_PRIVATE_H_
/*             TIMER 0  REG        */
#define TCCR0 *((volatile u8* ) (0x53)) // Configuration REG
#define TCNT0 *((volatile u8* ) (0x52)) // Counter REG
#define OCR0  *((volatile u8* ) (0x5C)) // Compare REG
#define TIMSK *((volatile u8* ) (0x59)) // Enable interrupt REG PIN0 for Overflow and PIN1for OCR
#define TIFR  *((volatile u8 *) (0x58)) // Interrupt Flag PIN0 for Overflow and PIN1for OCR reset by SETBIT

/*             TIMER 0  REG        */


/*             TIMER 2  REG        */
#define TCCR2 *((volatile u8*) (0x45))
#define TCNT2 *((volatile u8*) (0x44))
#define OCR2  *((volatile u8*) (0x43))

#endif /* HAL_TIMER_TIMER_PRIVATE_H_ */
