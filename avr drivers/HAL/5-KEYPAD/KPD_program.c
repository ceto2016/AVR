/*
 * KPD_program.c
 *
 *  Created on: Feb 12, 2021
 *      Author: le
 */

#include <util/delay.h>

#include "../../Services/STD_TYPE.h"
#include "../../Services/BIT_MATH.h"

#include "../../MCAL/1-DIO/DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"


void KPD_voidInit     (void){

	DIO_enumSetPinDirection( KPD_PORT , KPD_R0 , DIO_INPUT );
	DIO_enumSetPinDirection( KPD_PORT , KPD_R1 , DIO_INPUT );
	DIO_enumSetPinDirection( KPD_PORT , KPD_R2 , DIO_INPUT );
	DIO_enumSetPinDirection( KPD_PORT , KPD_R3 , DIO_INPUT );

	DIO_enumSetPinValue    ( KPD_PORT , KPD_R0 , DIO_HIGH );
	DIO_enumSetPinValue    ( KPD_PORT , KPD_R1 , DIO_HIGH );
	DIO_enumSetPinValue    ( KPD_PORT , KPD_R2 , DIO_HIGH );
	DIO_enumSetPinValue    ( KPD_PORT , KPD_R3 , DIO_HIGH );

	DIO_enumSetPinDirection( KPD_PORT , KPD_C0 , DIO_OUTPUT );
	DIO_enumSetPinDirection( KPD_PORT , KPD_C1 , DIO_OUTPUT );
	DIO_enumSetPinDirection( KPD_PORT , KPD_C2 , DIO_OUTPUT );
	DIO_enumSetPinDirection( KPD_PORT , KPD_C3 , DIO_OUTPUT );

	DIO_enumSetPinValue    ( KPD_PORT , KPD_C0 , DIO_HIGH );
	DIO_enumSetPinValue    ( KPD_PORT , KPD_C1 , DIO_HIGH );
	DIO_enumSetPinValue    ( KPD_PORT , KPD_C2 , DIO_HIGH );
	DIO_enumSetPinValue    ( KPD_PORT , KPD_C3 , DIO_HIGH );

}


u8   KPD_u8GetPressed (void){

	u8 LOC_u8ReturnData = 0 ;
	u8 LOC_u8ColIterator    ;
	u8 LOC_u8RowIterator    ;
	u8 LOC_u8GetPressed     ;

	for( LOC_u8ColIterator = 0 + KPD_COL_INIT ; LOC_u8ColIterator < KPD_COL_END + 1 ; LOC_u8ColIterator++ ){

		DIO_enumSetPinValue( KPD_PORT , LOC_u8ColIterator , DIO_LOW );

		for( LOC_u8RowIterator = 0 + KPD_ROW_INIT ; LOC_u8RowIterator < KPD_ROW_END + 1 ; LOC_u8RowIterator++ ){

			DIO_enumGetPinValue( KPD_PORT , LOC_u8RowIterator , &LOC_u8GetPressed );
			if( LOC_u8GetPressed == 0 ){

				_delay_ms(50);

				DIO_enumGetPinValue( KPD_PORT , LOC_u8RowIterator , &LOC_u8GetPressed );
				if( LOC_u8GetPressed == 0 ){

					LOC_u8ReturnData = KPD_u8Buttons[ LOC_u8RowIterator - KPD_ROW_INIT ][ LOC_u8ColIterator - KPD_COL_INIT ];
					DIO_enumSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_OUTPUT);
					DIO_enumSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
				}

				DIO_enumGetPinValue( KPD_PORT , LOC_u8RowIterator , &LOC_u8GetPressed );
				while( LOC_u8GetPressed == 0 ){

					DIO_enumGetPinValue( KPD_PORT , LOC_u8RowIterator , &LOC_u8GetPressed );

				}

				break;

			}

		}

		DIO_enumSetPinValue( KPD_PORT , LOC_u8ColIterator , DIO_HIGH );

	}

	return LOC_u8ReturnData ;

}
