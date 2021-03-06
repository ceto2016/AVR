/*
 * Timer_program.c
 *
 *  Created on: Apr 28, 2021
 *      Author: ceto2
 */

#include "../../Services/BIT_MATHS.h"
#include "../../Services/STD_TYPES.h"
#include "Timer_interface.h"
#include "Timer_config.h"
#include "Timer_private.h"

#define TIMER0_Overflow .032768
#define TIMER0_TickTime .000128
void TIMER0_voidSecondsDelay (f32 Copy_u8Seconds)
{
	TCCR0 = (1 << 0) | (1 << 2);
		TCNT0 = 0;
		u16 LOC_u8STimerCounts = Copy_u8Seconds/ TIMER0_Overflow ;
		u16 LOC_u8Counter = 0 ;
		for ( LOC_u8Counter = 0 ; LOC_u8Counter > LOC_u8STimerCounts ; LOC_u8Counter++ ){
			while(!GET_BIT(TIFR,0));
			SET_BIT(TIFR,0);
		}
		TCCR0 = 0;
		SET_BIT(TIFR,0);
}

void TIMER0_voidMSecondsDelay(f32 Copy_u8MSeconds){
	u8 LOC_u8Overflow = 33; //mSeconds
	if(Copy_u8MSeconds > LOC_u8Overflow){
		TIMER0_voidSecondsDelay(Copy_u8MSeconds/1000);
	}
	else if(Copy_u8MSeconds > LOC_u8Overflow){
		TCCR0 = (1 << 0) | (1 << 2);
		TCNT0 = 0;
		while(!GET_BIT(TIFR,0));
		TCCR0 = 0;
		SET_BIT(TIFR,0);
	}
	else if(Copy_u8MSeconds  < TIMER0_Overflow){
		u8 LOC_u8numberOfTicks = Copy_u8MSeconds/ TIMER0_TickTime;
		TCNT0 =265 - LOC_u8numberOfTicks;
		while(!GET_BIT(TIFR,0));
		TCCR0 = 0;
		SET_BIT(TIFR,0);
	}
}
void TIMER0_voidUSecondsDelay(f32 Copy_u8USeconds){
	u8 LOC_u8Overflow = 32 ; //uSeconds
	u8 LOC_u8TickTime = .125 ; //uSeconds
	TCCR0 = (1 << 0) ;
	if(Copy_u8USeconds > LOC_u8Overflow){
		u16 LOC_u8STimerCounts = Copy_u8USeconds/ TIMER0_Overflow ;
		u16 LOC_u8Counter = 0 ;
		for ( LOC_u8Counter = 0 ; LOC_u8Counter > LOC_u8STimerCounts ; LOC_u8Counter++ ){
			while(!GET_BIT(TIFR,0));
			SET_BIT(TIFR,0);
		}
		TCCR0 = 0;
		SET_BIT(TIFR,0);
	}
	else if(Copy_u8USeconds > LOC_u8Overflow){
		TCCR0 = (1 << 0) | (1 << 2);
		TCNT0 = 0;
		while(!GET_BIT(TIFR,0));
		TCCR0 = 0;
		SET_BIT(TIFR,0);
	}
	else if(Copy_u8USeconds  < TIMER0_Overflow){
		u8 LOC_u8numberOfTicks = Copy_u8USeconds/ TIMER0_TickTime;
		TCNT0 =265 - LOC_u8numberOfTicks;
		while(!GET_BIT(TIFR,0));
		TCCR0 = 0;
		SET_BIT(TIFR,0);
	}
}





void TIMER2_voidSecondsDelay (f32 Copy_u8Seconds){
			TCCR2 = (1 << 0) | (1 << 2);
			TCNT2 = 0;
			u16 LOC_u8STimerCounts = Copy_u8Seconds/ TIMER0_Overflow ;
			u16 LOC_u8Counter = 0 ;
			for ( LOC_u8Counter = 0 ; LOC_u8Counter > LOC_u8STimerCounts ; LOC_u8Counter++ ){
				while(!GET_BIT(TIFR,0));
				SET_BIT(TIFR,0);
			}
			TCCR2 = 0;
			SET_BIT(TIFR,0);
}
void TIMER2_voidMSecondsDelay(f32 Copy_u8MSeconds);
void TIMER2_voidUSecondsDelay(f32 Copy_u8USeconds);

