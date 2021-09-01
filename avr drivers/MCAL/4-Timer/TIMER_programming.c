#include "types.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_interface.h"

#define F_CPU 8000000

#define T0_TickTime     0.000125 //ms
#define T0_OverFlowTime 0.032768
#define T1_OverFlowTime 0.008192
#define T1_TickTime     0.000000125

#define mode1_top 0xFF
#define mode2_top 0x1FF
#define mode3_top 0x3FF

#define mode5_top 0xFF
#define mode6_top 0x1FF
#define mode7_top 0x3FF

void T0_sec_delay(f32 seconds)
{
	u16 counts;
    counts = seconds / T0_OverFlowTime;

	TCCR0 = (1 << CS00) | (1 << CS02);
	TCNT0 = 0;
	u16 count;

	for(count=0 ; count<counts ; count++)
	{
		while(!(TIFR & (1<<TOV0)));
		TIFR = (1<<TOV0);
	}
	TCCR0 = 0;
	TIFR = (1 << TOV0);
}

void T0_msec_delay(f32 mseconds)
{
	u16 counts;
	counts = mseconds / T0_OverFlowTime ;
	TCCR0 = (1 << CS00);
	TCNT0 = 0;

	u16 count;
	for(count =  0; count < counts; count++)
	{
		while(!(TIFR & (1 << TOV0)));
		TIFR = (1 << TOV0);
	}
	TCCR0 = 0 ;
	TIFR = (1 << TOV0);
}

void T0_usec_delay(f32 useconds)
{
	u8 OverFlow = 32;    //Microsecond
	u8 TickTime = 0.125; //Microsecond

	if(useconds == OverFlow)
	{
		TCNT0 = 0;
		TCCR0 = (1 << CS00);
		while(!(TIFR & (1 << TOV0)));
		TCCR0 = 0;
		TIFR = (1 << TOV0);
	}
	else if(useconds > OverFlow)
	{
		u16 counts;
		counts = useconds / OverFlow;

		TCNT0 = 0;
		TCCR0 = (1 << CS00);

		u8 count;
		for(count = 0 ; count < counts ; count++)
		{
			while(!(TIFR & (1 << TOV0)));
			TIFR = (1 << TOV0);
		}
		TCCR0 = 0;
		TIFR = (1 << TOV0);
	}
	else if(useconds < OverFlow)
	{
		u16 TCNT_val;
		TCNT_val = useconds / TickTime;

		TCNT0 = 256 - TCNT_val;
		TCCR0 = (1 << CS00);

		while(!(TIFR & (1 << TOV0)));
		TCCR0 = 0;
		TIFR = (1 << TOV0);
	}
	else
	{
		//do nothing
	}
}

void T0_FastPwm(f32 duty, u32 frequency, u8 comp)
{
	DDRB = (1<<3);

	switch(comp)
	{
	case inverted : OCR0 = (T0_top) - ( (duty/100)*(T0_top+1) );
	                TCCR0 = (1 << COM00) | (1 << COM01) | (1 << WGM00) | (1 << WGM01);
	break;

	case non_inverted : OCR0 = ( (T0_top+1) * (duty/100) ) - 1 ;
	                    TCCR0 = (1 << COM01) | (1 << WGM00) | (1 << WGM01);
	break;

	default : //do nothing
		break;
	}


	u16 prescaler;
	prescaler = ( (F_CPU) / ( (T0_top+1) * frequency ) ) ;

	switch(prescaler)
	{
	      case 1 : TCCR0 |= (1 << CS00);
	      break;

	      case 8 : TCCR0 |= (1 << CS01);
	      break;

	      case 64 : TCCR0 |= (1 << CS00) | (1 << CS01);
	      break;

	      case 256 : TCCR0 |= (1 << CS02);
	      break;

	      case 1024 : TCCR0 |= (1 << CS00) | (1 << CS02);
	      break;

	      default : TCCR0 |= (1 << CS00) ;
	      break;
	}

}

void T0_PhaseCorrectPwm(f32 duty, u32 frequency, u8 comp)
{
	DDRB = (1 << 3);

	switch(comp)
	{
	case inverted : OCR0 = T0_top - ( (duty*T0_top) /100);
	                TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << COM00);
	                break;

	case non_inverted : OCR0 = (duty * T0_top)/100;
	                    TCCR0 = (1 << WGM00) | (1 << COM01);
	                    break;

	default : //do nothing
		break;
	}

	u16 prescaler;
	prescaler = F_CPU / ( 2 * T0_top * frequency);

	switch(prescaler)
	{
	      case 1 : TCCR0 |= (1 << CS00);
	      break;

	      case 8 : TCCR0 |= (1 << CS01);
	      break;

	      case 64 : TCCR0 |= (1 << CS00) | (1 << CS01);
	      break;

	      case 256 : TCCR0 |= (1 << CS02);
	      break;

	      case 1024 : TCCR0 |= (1 << CS00) | (1 << CS02);
	      break;

	      default :
	    	               TCCR0 |= (1 << CS00);
	      break;
	}
}


void T1_sec_delay(f32 seconds)
{
    u16 counts;
    counts = seconds / T1_OverFlowTime;

    TCCR1B = (1 << CS10);
    TCNT1 = 0;

    u16 count;
    for(count=0 ; count<counts ; count++)
    {
    	while(!(TIFR & (1 << TOV1)));
    	TIFR = (1 << TOV1);
    }
    TCCR1B = 0;
    TIFR = (1 << TOV1);
}

void T1_msec_delay(f32 mseconds)
{
	mseconds /= 1000;   //as the user actually enters seconds not mseconds

	if(mseconds > T1_OverFlowTime)
	{
		TCNT1 = 0;
		TCCR1B = (1 << CS10);

		u16 cycles;
		cycles = mseconds / T1_OverFlowTime;

		u16 count;
		for(count=0 ; count<cycles ; count++)
		{
			while(!(TIFR & (1 << TOV1)));
			TIFR = (1 << TOV1);
		}

		TCCR1B = 0;
		TIFR = (1 << TOV1);
	}
	else if(mseconds < T1_OverFlowTime)
	{
          u16 TCNT_value;
          TCNT_value = mseconds / T1_TickTime;
          TCNT1 = 65536 - TCNT_value;
          TCCR1B = (1 << CS10);

          while(!(TIFR & ( 1 << TOV1)));
          TCCR1B = 0;
          TIFR = (1 << TOV1);
	}
	else if(mseconds == T1_OverFlowTime)
	{
		TCNT1 = 0;
		TCCR1B = (1 << CS10);

		while(!(TIFR & ( 1 << TOV1)));

		TCCR1B = 0;
		TIFR = (1 << TOV1);
	}
	else
	{
		//do nothing
	}
}

void T1_usec_delay(f32 useconds)
{
	useconds /= 1000000;   //as the user actually enters seconds not useconds

	if(useconds > T1_OverFlowTime)
	{
		TCNT1 = 0;
		TCCR1B = (1 << CS10);

		u16 cycles;
		cycles = useconds / T1_OverFlowTime;

		u16 count;
		for(count=0 ; count<cycles ; count++)
		{
			while(!(TIFR & (1 << TOV1)));
			TIFR = (1 << TOV1);
		}

		TCCR1B = 0;
		TIFR = (1 << TOV1);
	}
	else if(useconds < T1_OverFlowTime)
	{
          u16 TCNT_value;
          TCNT_value = useconds / T1_TickTime;
          TCNT1 = 65535 - TCNT_value;
          TCCR1B = (1 << CS10);

          while(!(TIFR & ( 1 << TOV1)));
          TCCR1B = 0;
          TIFR = (1 << TOV1);
	}
	else if(useconds == T1_OverFlowTime)
	{
		TCNT1 = 0;
		TCCR1B = (1 << CS10);

		while(!(TIFR & ( 1 << TOV1)));

		TCCR1B = 0;
		TIFR = (1 << TOV1);
	}
	else
	{
		//do nothing
	}


}

void T1_FastPwm(f32 duty, u32 frequency, u8 comp, u8 mode, u8 OC_Pin)
{
	switch(OC_Pin)
	{
	case OC1A_pin :  DDRD = (1 << 5);
	                 switch(comp)
	                 {
	                 case inverted : switch(mode)
	                                 {
	                                     case 5 : OCR1A = mode5_top - (duty * (mode5_top+1) / 100);
	                                              TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1A0);
	                                              TCCR1B = (1 << WGM12) | (1 << CS10);
	                                    	 break;
	                                     case 6 : OCR1A = mode6_top - (duty * (mode6_top+1) / 100);
	                                              TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	                                              TCCR1B = (1 << WGM12) | (1 << CS10);
	                                    	 break;
	                                     case 7 : OCR1A = mode7_top - (duty * (mode7_top+1) / 100);
	                                              TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	                                              TCCR1B = (1 << WGM12) | (1 << CS10);
	                                    	 break;
	                                     default : //do nothing
	                                    	 break;
	                                 }
	                	 break;
	                 case non_inverted : switch(mode)
	                                    {
	                                       case 5 : OCR1A = ((mode5_top+1) * duty / 100) - 1;
	                                                TCCR1A = (1 << WGM10) | (1 << COM1A1);
	                                       	        TCCR1B = (1 << WGM12) | (1 << CS10);

	                                    	   break;
	                                       case 6 : OCR1A = ((mode6_top+1) * duty / 100) - 1;
	                                                TCCR1A = (1 << WGM11) | (1 << COM1A1);
	                                       	        TCCR1B = (1 << WGM12) | (1 << CS10);
	                                    	   break;
	                                       case 7 : OCR1A = ((mode7_top+1) * duty / 100) - 1;
	                                                TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1);
	                                                TCCR1B = (1 << WGM12) | (1 << CS10);
	                                    	   break;
	                                       default : //do nothing
	                                    	   break;
	                                    }

	                	 break;
	                 default : //do nothing
	                	 break;
	                 }
		break;
	case OC1B_pin :  DDRD = (1 << 5);
                     switch(comp)
                     {
                          case inverted : switch(mode)
                                          {
                                              case 5 :  OCR1B = mode5_top - (duty * (mode5_top+1) / 100);
                                                        TCCR1A = (1 << WGM10) | (1 << COM1B1) | (1 << COM1B0);
                                                        TCCR1B = (1 << WGM12) | (1 << CS10);
                       	                         break;
                                              case 6 : OCR1B = mode6_top - (duty * (mode6_top+1) / 100);
                                                       TCCR1A = (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
                                                       TCCR1B = (1 << WGM12) | (1 << CS10);
                       	                         break;
                                              case 7 : OCR1B = mode7_top - (duty * (mode7_top+1) / 100);
                                                       TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
                                                       TCCR1B = (1 << WGM12) | (1 << CS10);
                       	                         break;
                                              default : //do nothing
                       	                         break;
                                           }
   	                              break;
                         case non_inverted : switch(mode)
                                             {
                                                 case 5 : OCR1B = ((mode5_top+1) * duty / 100) - 1;
                                                           TCCR1A = (1 << WGM10) | (1 << COM1B1);
                                                           TCCR1B = (1 << WGM12) | (1 << CS10);
                       	                           break;
                                                 case 6 : OCR1B = ((mode6_top+1) * duty / 100) - 1;
	                                                      TCCR1A = (1 << WGM11) | (1 << COM1B1);
	                                       	              TCCR1B = (1 << WGM12) | (1 << CS10);
                       	                           break;
                                                 case 7 : OCR1B = ((mode7_top+1) * duty / 100) - 1;
	                                                      TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1);
	                                                      TCCR1B = (1 << WGM12) | (1 << CS10);
                       	                           break;
                                                 default : //do nothing
                       	                           break;
                                             }

   	                               break;
                        default : //do nothing
   	                         break;
                    }
                        break;
                     default : //do nothing
                    	 break;
	}
}

void T1_FastPwmMode14(f32 duty, f32 frequency, u8 comp, u8 OC_Pin)
{
	 ICR1 = (F_CPU / frequency) - 1;

	 switch(OC_Pin)
	 {
	 case OC1A_pin : DDRD = (1 << 5);
	                 switch(comp)
	                 {
	                 case inverted :  OCR1A = ICR1 - (duty * (ICR1 + 1) / 100);
	                                  TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	                                  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	                	 break;
	                 case non_inverted : OCR1A = ( (ICR1 + 1) * duty / 100) - 1;
	                                     TCCR1A = (1 << WGM11) | (1 << COM1A1);
	                                     TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	                	 break;
	                 default : // do nothing
	                	 break;
	                 }
		 break;
	 case OC1B_pin : DDRD = (1 << 4);
	                 switch(comp)
	                 {
	                 case inverted :  OCR1B = ICR1 - (duty * (ICR1 + 1) / 100);
	                                  TCCR1A = (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
	                                  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	                	 break;
	                 case non_inverted : OCR1B = ( (ICR1 + 1) * duty / 100) - 1;
	                                     TCCR1A = (1 << WGM11) | (1 << COM1B1);
	                 	                 TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	                	 break;
	                 default :
	                	 break;
	                 }
		 break;
	 default : //do nothing
		 break;
	 }
}

void T1_FastPwmMode15(f32 duty, f32 frequency, u8 comp)
{
	DDRD = (1 << 4);
	OCR1A = (F_CPU / frequency) - 1;

	switch(comp)
	{
	case inverted :  OCR1B = OCR1A - (duty * (OCR1A + 1) / 100);
			         TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
			         TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
		break;
	case non_inverted : OCR1B = ( (OCR1A + 1) * duty / 100) - 1;
			            TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1);
			            TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
		break;
	default :
		break;
	}
}

void T1_PhaseCorrectPwm(f32 duty, u32 frequency, u8 comp, u8 mode, u8 OC_Pin)
{
	switch(OC_Pin)
	{
	case OC1A_pin :  DDRD = (1 << 5);
	                 switch(comp)
	                 {
	                 case inverted : switch(mode)
	                                 {
	                                     case 1 : OCR1A = mode1_top - (duty * mode1_top / 100);
	                                              TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1A0);
	                                              TCCR1B = (1 << CS10);
	                                    	 break;
	                                     case 2 : OCR1A = mode2_top - (duty * mode2_top / 100);
	                                              TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	                                              TCCR1B = (1 << CS10);
	                                    	 break;
	                                     case 3 : OCR1A = mode3_top - (duty * mode3_top / 100);
	                                              TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	                                              TCCR1B = (1 << CS10);
	                                    	 break;
	                                     default : //do nothing
	                                    	 break;
	                                 }
	                	 break;
	                 case non_inverted : switch(mode)
	                                    {
	                                       case 1 : OCR1A = mode1_top * duty / 100;
                                                    TCCR1A = (1 << WGM10) | (1 << COM1A1);
                                                    TCCR1B = (1 << CS10);
	                                    	   break;
	                                       case 2 : OCR1A = mode2_top * duty / 100;
	                                                TCCR1A = (1 << WGM11) | (1 << COM1A1);
	                                       	        TCCR1B = (1 << CS10);
	                                    	   break;
	                                       case 3 : OCR1A = mode3_top * duty / 100;
	                                                TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A1);
	                                                TCCR1B = (1 << CS10);
	                                    	   break;
	                                       default : //do nothing
	                                    	   break;
	                                    }

	                	 break;
	                 default : //do nothing
	                	 break;
	                 }
		break;
	case OC1B_pin :  DDRD = (1 << 5);
                     switch(comp)
                     {
                          case inverted : switch(mode)
                                          {
                                              case 1 :  OCR1B = mode1_top - (duty * mode1_top / 100);
                                                        TCCR1A = (1 << WGM10) | (1 << COM1B1) | (1 << COM1B0);
                                                        TCCR1B = (1 << CS10);
                       	                         break;
                                              case 2 : OCR1B = mode2_top - (duty * mode2_top / 100);
                                                       TCCR1A = (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
                                                       TCCR1B = (1 << CS10);
                       	                         break;
                                              case 3 : OCR1B = mode3_top - (duty * mode3_top / 100);
                                                       TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
                                                       TCCR1B = (1 << CS10);
                       	                         break;
                                              default : //do nothing
                       	                         break;
                                           }
   	                              break;
                         case non_inverted : switch(mode)
                                             {
                                                 case 1 : OCR1B = mode1_top * duty / 100;
                                                           TCCR1A = (1 << WGM10) | (1 << COM1B1);
                                                           TCCR1B = (1 << CS10);
                       	                           break;
                                                 case 2 : OCR1B = mode2_top * duty / 100;
	                                                      TCCR1A = (1 << WGM11) | (1 << COM1B1);
	                                       	              TCCR1B = (1 << CS10);
                       	                           break;
                                                 case 3 : OCR1B = mode3_top * duty / 100;
	                                                      TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1);
	                                                      TCCR1B = (1 << CS10);
                       	                           break;
                                                 default : //do nothing
                       	                           break;
                                             }

   	                               break;
                        default : //do nothing
   	                         break;
                    }
                        break;
                     default : //do nothing
                    	 break;
	}
}

void T1_PhaseCorrectPwmMode10(f32 duty, f32 frequency, u8 comp, u8 OC_Pin)
{
	 ICR1 = (F_CPU / 2 * frequency);

	 switch(OC_Pin)
	 {
	 case OC1A_pin : DDRD = (1 << 5);
	                 switch(comp)
	                 {
	                 case inverted :  OCR1A = ICR1 - (duty * ICR1 / 100);
	                                  TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1A0);
	                                  TCCR1B = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 case non_inverted : OCR1A = duty * ICR1 / 100;
	                                     TCCR1A = (1 << WGM11) | (1 << COM1A1);
	                                     TCCR1A = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 default : // do nothing
	                	 break;
	                 }
		 break;
	 case OC1B_pin : DDRD = (1 << 4);
	                 switch(comp)
	                 {
	                 case inverted :  OCR1B = ICR1 - (duty * ICR1 / 100);
	                                  TCCR1A = (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
	                                  TCCR1B = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 case non_inverted : OCR1B = duty * ICR1 / 100;
	                                     TCCR1A = (1 << WGM11) | (1 << COM1B1);
	                 	                 TCCR1B = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 default : //do nothing
	                	 break;
	                 }
		 break;
	 default : //do nothing
		 break;
	 }
}

void T1_PhaseCorrectPwmMode11(f32 duty, f32 frequency, u8 comp)
{
	DDRD = (1 << 4);
	OCR1A = (F_CPU / 2 * frequency) ;

	switch(comp)
	{
	case inverted :  OCR1B = OCR1A - (duty * OCR1A / 100);
			         TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1) | (1 << COM1B0);
			         TCCR1B = (1 << WGM13) | (1 << CS10);
		break;
	case non_inverted : OCR1B = duty * OCR1A / 100;
			            TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1B1);
			            TCCR1B = (1 << WGM13) | (1 << CS10);
		break;
	default : // do thing
		break;
	}
}

void T1_PhaseAndFrequencyCorrectMode8(f32 duty, f32 frequency, u8 comp, u8 OC_Pin)
{
	 ICR1 = (F_CPU / 2 * frequency);

	 switch(OC_Pin)
	 {
	 case OC1A_pin : DDRD = (1 << 5);
	                 switch(comp)
	                 {
	                 case inverted :  OCR1A = ICR1 - (duty * ICR1 / 100);
	                                  TCCR1A = (1 << COM1A1) | (1 << COM1A0);
	                                  TCCR1B = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 case non_inverted : OCR1A = duty * ICR1 / 100;
	                                     TCCR1A = (1 << COM1A1);
	                                     TCCR1A = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 default : // do nothing
	                	 break;
	                 }
		 break;
	 case OC1B_pin : DDRD = (1 << 4);
	                 switch(comp)
	                 {
	                 case inverted :  OCR1B = ICR1 - (duty * ICR1 / 100);
	                                  TCCR1A = (1 << COM1B1) | (1 << COM1B0);
	                                  TCCR1B = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 case non_inverted : OCR1B = duty * ICR1 / 100;
	                                     TCCR1A = (1 << COM1B1);
	                 	                 TCCR1B = (1 << WGM13) | (1 << CS10);
	                	 break;
	                 default : //do nothing
	                	 break;
	                 }
		 break;
	 default : //do nothing
		 break;
	 }
}

void T1_PhaseAndFrequencyCorrectMode9(f32 duty, f32 frequency, u8 comp)
{
	DDRD = (1 << 4);
	OCR1A = (F_CPU / 2 * frequency) ;

	switch(comp)
	{
	case inverted :  OCR1B = OCR1A - (duty * OCR1A / 100);
			         TCCR1A = (1 << WGM10) | (1 << COM1B1) | (1 << COM1B0);
			         TCCR1B = (1 << WGM13) | (1 << CS10);
		break;
	case non_inverted : OCR1B = duty * OCR1A / 100;
			            TCCR1A = (1 << WGM10) | (1 << COM1B1);
			            TCCR1B = (1 << WGM13) | (1 << CS10);
		break;
	default : // do thing
		break;
	}
}

void WatchDog_on(f32 TimeOut_Sec)
{
	if(TimeOut_Sec == 0.0163)
	{
		WDTCR = (1 << WDE);
	}
	else if(TimeOut_Sec == 0.0325)
	{
		WDTCR = (1 << WDE) | (1 << WDP0);
	}
	else if(TimeOut_Sec == 0.065)
	{
		WDTCR = (1 << WDE) | (1 << WDP1) ;
	}
	else if(TimeOut_Sec == 0.13)
	{
		WDTCR = (1 << WDE) | (1 << WDP0) | (1 << WDP1);
	}
	else if(TimeOut_Sec == 0.26)
	{
		WDTCR = (1 << WDE) | (1 << WDP2);
	}
	else if(TimeOut_Sec == 0.52)
	{
		WDTCR = (1 << WDE) | (1 << WDP0) | (1 << WDP2);
	}
	else if(TimeOut_Sec == 1)
	{
		WDTCR = (1 << WDE) | (1 << WDP1) | (1 << WDP2);
	}
	else if(TimeOut_Sec == 2.1)
	{
		WDTCR = (1 << WDE) | (1 << WDP0) | (1 << WDP1) | (1 << WDP2);
	}
	else
	{
		//do nothing
	}

}

void WatchDog_off(void)
{
	WDTCR = (1 << WDE) | (1 << WDTOE);
	WDTCR = 0;
}


void ICU_Start(void)
{

	LCD4bitSinglePort_init();

	u32 a, b, c, high, period;
	u8 frequency[10], duty_cycle[8];
	u32 freq;
	f32 duty;

	PORTD = (1 << 6);

	while(1)
	{
		TCCR1A = 0;
        TCNT1 = 0;
		TIFR = (1 << ICF1);


		TCCR1B |= (1 << ICES1) | (1 << CS10);
		while(!(TIFR & (1<<ICF1)));
		a = ICR1;
		TIFR = (1 << ICF1);

		TCCR1B &= ~(1 << ICES1);
		while(!(TIFR & (1 << ICF1)));
		b = ICR1;
		TIFR = (1 << ICF1);

		TCCR1B |= (1 << ICES1) | (1 << CS10);
		while(!(TIFR & (1 << ICF1)));
		c = ICR1;
		TIFR = (1 << ICF1);

        TCCR1B = 0;

		if(a<b && b<c)
		{
			high = b-a;
			period = c-a;

			freq = F_CPU / period;
			duty = ( (f32)high / (f32)period ) * 100;

			itoa(freq, frequency, 10);
			itoa((u16)duty, duty_cycle, 10);

			LCD4bitSinglePort_goto(1,1);
			LCD4bitSinglePort_write("freq ");
			LCD4bitSinglePort_write(frequency);
			LCD4bitSinglePort_write(" Hz");

			LCD4bitSinglePort_goto(2,1);
			LCD4bitSinglePort_write("duty ");
			LCD4bitSinglePort_write(duty_cycle);
			LCD4bitSinglePort_write(" % ");
		}
		else
		{
			//do nothing
		}
	}
}
