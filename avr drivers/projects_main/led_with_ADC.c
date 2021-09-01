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
void ledSwitch(u16 Copy_u16AdcAnalogValue);

void main(void){
	u16 LOC_u16AdcDigitalValue = 0;
	u16 LOC_u16AdcAnalogValue = 0;
	DIO_enumSetPortDirection(DIO_PORTC,0xff);
	DIO_enumSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
	ADC_voidinit();
	CLCD_voidInit();
	CLCD_voidSendPostion(CLCD_ROW_1,CLCD_Column_1);
	_delay_ms(2000);
	CLCD_voidClearLCE();
	while( 1){
		CLCD_voidSendPostion(CLCD_ROW_1,CLCD_Column_1);
		CLCD_voidSendString((u8*)"Digital : ");
		LOC_u16AdcDigitalValue = ADC_u16getValue();
		CLCD_voidSendNumber(LOC_u16AdcDigitalValue);
		CLCD_voidSendPostion(CLCD_ROW_2,CLCD_Column_1);
		CLCD_voidSendString((u8*)"Analog : ");
		LOC_u16AdcAnalogValue = (5.0 * 100 * LOC_u16AdcDigitalValue) / 1023;
		CLCD_voidSendNumber((LOC_u16AdcAnalogValue / 100));
		CLCD_voidSendData('.');
		CLCD_voidSendNumber((LOC_u16AdcAnalogValue % 100) );
		ledSwitch(LOC_u16AdcDigitalValue);
		_delay_ms(2000);
		CLCD_voidClearLCE();
	}
}

void ledSwitch(u16 Copy_u16AdcDigitalValue){
	if(Copy_u16AdcDigitalValue > 600){
		DIO_enumSetPinValue(DIO_PORTC,DIO_PIN0,DIO_HIGH);
		DIO_enumSetPinValue(DIO_PORTC,DIO_PIN1,DIO_LOW);
	}
	else{
		DIO_enumSetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
		DIO_enumSetPinValue(DIO_PORTC,DIO_PIN0,DIO_LOW);
	}
}
