/*
 * ADC_program.c
 *
 *  Created on: Apr 26, 2021
 *      Author: ceto2
 */

#include "../../Services/STD_TYPES.h"
#include "../../Services/BIT_MATHS.h"


#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"



void ADC_voidinit(void){
	ADMUX  =  0b01000000;
	ADCSRA =  0b10010111;
}

u16 ADC_u16getValue(void){
u16 LOC_u16RES = 0;
// start conversion
	SET_BIT(ADCSRA, 6);
//read
	while(GET_BIT(ADCSRA,4) == 0){
		LOC_u16RES = ADCL |(ADCH << 8);
	}
	SET_BIT(ADCSRA, 4);
return LOC_u16RES;
}
