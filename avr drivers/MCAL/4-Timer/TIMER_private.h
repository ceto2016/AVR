/*
 * TIMER_private.h
 *
 *  Created on: Mar 11, 2018
 *  Author    : Ahmed Abdel-shafy
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define PORTA  *((volatile u8*)0x3b)
#define DDRA   *((volatile u8*)0x3a)
#define PINA   *((volatile u8*)0x39)

#define PORTB  *((volatile u8*)0x38)
#define DDRB   *((volatile u8*)0x37)
#define PINB   *((volatile u8*)0x36)

#define PORTC  *((volatile u8*)0x35)
#define DDRC   *((volatile u8*)0x34)
#define PINC   *((volatile u8*)0x33)

#define PORTD  *((volatile u8*)0x32)
#define DDRD   *((volatile u8*)0x31)
#define PIND   *((volatile u8*)0x30)

#define TCCR0  *((volatile u8*)0x53)
#define TCNT0  *((volatile u8*)0x52)
#define TIFR   *((volatile u8*)0x58)
#define OCR0   *((volatile u8*)0x5c)
#define TIMSK  *((volatile u8*)0x59)

//TIMER1 REGs
#define TCCR1A  *((volatile u8*)0x4F)
#define TCCR1B  *((volatile u8*)0x4E)

#define TCNT1   *((volatile u16*)0x4C)
#define TCNT1H  *((volatile u8*)0x4D)
#define TCNT1L  *((volatile u8*)0x4C)

#define OCR1A   *((volatile u16*)0x4A)
#define OCR1AH  *((volatile u8*)0x4B)
#define OCR1AL  *((volatile u8*)0x4A)

#define OCR1B   *((volatile u16*)0x48)
#define OCR1BH  *((volatile u8*)0x49)
#define OCR1BL  *((volatile u8*)0x48)

#define ICR1    *((volatile u16*)0x46)
#define ICR1H   *((volatile u8*)0x47)
#define ICR1L   *((volatile u8*)0x46)



#define TOV0 0
#define OC1A_pin 1
#define OC1B_pin 2

//TCCR0 BITS
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7

#define toggle       0
#define clear        1
#define non_inverted 1
#define set          2
#define inverted     2

#define T0_top       255

//TIFR BITS
#define TOV0 0
#define OCF0 1
#define TOV1 2
#define OCF1B 3
#define OCF1A 4
#define ICF1  5
#define TOV2  6
#define OCF2  7

//TIMSK BITS
#define TOIE0  0
#define OCIE0  1
#define TOIE1  2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2  6
#define OCIE2  7

//TCCR1A BITS
#define WGM10  0
#define WGM11  1
#define FOC1B  2
#define FOC1A  3
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

//TCCR1B BITS
#define CS10  0
#define CS11  1
#define CS12  2
#define WGM12 3
#define WGM13 4
//BIT-5 RESERVED
#define ICES1 6
#define ICNC1 7

//watch dog timer
#define WDTCR    *((volatile u8*)0x41)
#define WDP0  0
#define WDP1  1
#define WDP2  2
#define WDE   3
#define WDTOE 4


#endif /* TIMER_PRIVATE_H_ */
