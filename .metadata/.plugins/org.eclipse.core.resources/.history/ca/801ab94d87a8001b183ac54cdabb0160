/*
 * TIMER_interface.h
 *
 *  Created on: Mar 11, 2018
 *  Author    : Ahmed Abdel-shafy
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_
#include "types.h"

//************************************************
//********** TIMER0 FUNCTIONS ********************
//************************************************

/*  SYNCH */
void T0_sec_delay(f32 seconds);
void T0_msec_delay(f32 mseconds);
void T0_usec_delay(f32 useconds);


void T0_WaveGen_FDP(f32 frequency, f32 duty, f32 period);   // without pwm modes
void T0_WaveGen_FD(f32 frequency, f32 duty);                // without pwm modes

void T0_FastPwm(f32 duty, u32 frequency, u8 comp);
void T0_PhaseCorrectPwm(f32 duty, u32 frequency, u8 comp);



//************************************************
//********** TIMER2 FUNCTIONS ********************
//************************************************
void T2_sec_delay(f32 seconds);
void T2_msec_delay(f32 mseconds);
void T2_usec_delay(f32 useconds);

void T2_WaveGen_FDP(f32 frequency, f32 duty, f32 period);   // without pwm modes
void T2_WaveGen_FD(f32 frequency, f32 duty);                // without pwm modes

void T2_FastPwm(f32 duty, u32 frequency, u8 comp);
void T2_PhaseCorrectPwm(f32 duty, u32 frequency, u8 comp);


//***********************************************
//********** TIMER1 FUNCTIONS *******************
//***********************************************
void T1_sec_delay(f32 seconds);
void T1_msec_delay(f32 mseconds);
void T1_usec_delay(f32 useconds);

void T1_FastPwm(f32 duty, u32 frequency, u8 comp, u8 mode, u8 OC_Pin);  // modes 5, 6, 7
void T1_FastPwmMode14(f32 duty, f32 frequency, u8 comp, u8 OC_Pin);     //mode 14  ICR1_TOP
void T1_FastPwmMode15(f32 duty, f32 frequency, u8 comp);                //mode 15 OCR1A_TOP

void T1_PhaseCorrectPwm(f32 duty, u32 frequency, u8 comp, u8 mode, u8 OC_Pin);  //modes 1, 2, 3
void T1_PhaseCorrectPwmMode10(f32 duty, f32 frequency, u8 comp, u8 OC_Pin);     //mode 10 ICR1_TOP
void T1_PhaseCorrectPwmMode11(f32 duty, f32 frequency, u8 comp);                //mode 11 OCR1A_TOP

void T1_PhaseAndFrequencyCorrectMode8(f32 duty, f32 frequency, u8 comp, u8 OC_Pin); //mode 8 ICR1_TOP
void T1_PhaseAndFrequencyCorrectMode9(f32 duty, f32 frequency, u8 comp);            //mode 9 OCR1A_TOP


//***********************************************
//*********** INPUT CAPTURE UNIT ****************
//***********************************************
void ICU_Start(void);


//***********************************************
//********** WATCH DOG TIMER ********************
//***********************************************
void WatchDog_on(f32 TimeOut_Sec);
void WatchDog_off(void);

#endif /* TIMER_INTERFACE_H_ */
