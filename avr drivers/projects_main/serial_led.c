/*
 * serial_led.c
 *
 *  Created on: Feb 25, 2021
 *      Author: ceto2
 */
/*#include "./Services/STD_TYPE.h"
#include "./Services/BIT_MATH.h"

#include <util/delay.h>
#include "MCAL/1-DIO/DIO_interface.h"
#include "HAL/4-LCD/CLCD_interface.h"
#include "HAL/5-KEYPAD/KPD_interface.h"
#include "HAL/3-SSD/SSD_interface.h"


int main(void){
	DIO_ErrorStatus portStatus;
	DIO_ErrorStatus pinStatus;
	portStatus = DIO_enumSetPortDirection(DIO_PORTA,0xff);
	while(1){
		if( portStatus == DIO_OK){
			for(u8 i = 0  ; i <= 7 ; i++){
				pinStatus = DIO_enumSetPortValue(DIO_PORTA, 1 << i);
				if(pinStatus == DIO_NOK ){
					break;
				}
				_delay_ms(500);
			}
			for(u8 i = 6  ; i >= 1 ; i--){
				DIO_enumSetPortValue(DIO_PORTA, 1 << i);
				if(pinStatus == DIO_NOK ){
					break;
				}
				_delay_ms(500);
			}
		}
	}
	return 0;
}
 *
 *
 *
 * */

