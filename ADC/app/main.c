/*
 * main.c
 *
 *  Created on: Apr 26, 2021
 *      Author: ceto2
 */

#include "stdio.h"
#include "util/delay.h"
#include "../Services/STD_TYPES.h"
#include "../HAL/4-LCD/CLCD_interface.h"
#include "../HAL/7-ADC/ADC_interface.h"
#include "../MCAL/01-DIO/DIO_interface.h"
void main(void){
	u16 LOC_u16AdcDigitalValue = 0;
	u32 LOC_u32AdcAnalogValue = 0;
	u32 LOC_u32Temp = 0;
	ADC_voidinit();
	CLCD_voidInit();
	while( 1){
		CLCD_voidSendPostion(CLCD_ROW_1,CLCD_Column_1);
		CLCD_voidSendString((u8*)"TEMP : ");
		LOC_u16AdcDigitalValue= ADC_u16getValue();
		LOC_u32AdcAnalogValue = ((u32) 5.0 * 1000*LOC_u16AdcDigitalValue) / 1023;
		CLCD_voidSendNumber(LOC_u32AdcAnalogValue);
		_delay_ms(1000);
		CLCD_voidClearLCE();
	}
}

// LM35 CODE
//LOC_u16AdcDigitalValue= ADC_u16getValue();
//		LOC_u32AdcAnalogValue = ((u32)5.0 * 1000* LOC_u16AdcDigitalValue) / 1023;
//		LOC_u32Temp = ((u32)LOC_u32AdcAnalogValue )/ 10;
//		CLCD_voidSendNumber(LOC_u32Temp);
