/*
 * CLCD_program.c
 *
 *  Created on: Feb 6, 2021
 *      Author: le
 */

#include <util/delay.h>

#include "../../Services/STD_TYPES.h"
#include "../../Services/BIT_MATHS.h"

#include "../../MCAL/01-DIO/DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"


void CLCD_voidInit ( void ){

	DIO_enumSetPortDirection ( CLCD_DATA_PORT    , 255        );
	DIO_enumSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_OUTPUT  );
	DIO_enumSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_OUTPUT  );
	DIO_enumSetPinDirection  ( CLCD_CONTROL_PORT , CLCD_EN , DIO_OUTPUT  );

	_delay_ms(50);

	//Funtion set
	CLCD_voidSendCommend( 0b00111100 );
	_delay_ms(1);

	//Display ON OFF
	CLCD_voidSendCommend( 0b00001100 );
	_delay_ms(1);

	//Clear
	CLCD_voidSendCommend( 0b00000001 );
	_delay_ms(2);

	//Entry Mode
	CLCD_voidSendCommend( 0b00000110 );
	_delay_ms(1);

}



void CLCD_voidSendData    ( u8 Copy_u8Data    ){

	DIO_enumSetPortValue( CLCD_DATA_PORT    , Copy_u8Data        );
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_RS , DIO_HIGH );
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_RW , DIO_LOW  );
	/* Enable Pulse ===> Falling Edge */
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_EN , DIO_HIGH );
	_delay_ms(1);
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_EN , DIO_LOW  );
	_delay_ms(1);

}
void CLCD_voidSendCommend ( u8 Copy_u8Commend ){

	DIO_enumSetPortValue( CLCD_DATA_PORT    , Copy_u8Commend     );
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_RS , DIO_LOW  );
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_RW , DIO_LOW  );
	/* Enable Pulse ===> Falling Edge */
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_EN , DIO_HIGH );
	_delay_ms(1);
	DIO_enumSetPinValue ( CLCD_CONTROL_PORT , CLCD_EN , DIO_LOW  );
	_delay_ms(1);

}
void CLCD_voidSendString  ( u8 * Copy_u8ptrString ){

	u8 LOC_u8Iterator = 0 ;

	while( Copy_u8ptrString[ LOC_u8Iterator ] != '\0' ){
		CLCD_voidSendData( Copy_u8ptrString[ LOC_u8Iterator ] );
		LOC_u8Iterator++ ;
	}
}
void CLCD_voidSendNumber  ( u64 Copy_u64ptrNumber ){
	u64 Loc_u64Reversed = 1 ;
	if(Copy_u64ptrNumber == 0) {
		CLCD_voidSendString((u8*)"0");
	}
	else{
		while( Copy_u64ptrNumber != 0){
			Loc_u64Reversed = (Loc_u64Reversed * 10 ) + (Copy_u64ptrNumber % 10);
			Copy_u64ptrNumber /= 10 ;
		}
		while( Loc_u64Reversed != 1){
			CLCD_voidSendData((Loc_u64Reversed % 10) + 48);
			Loc_u64Reversed /= 10;
		}}
}
void CLCD_voidSendPostion  ( u8  Copy_u8RowNumber ,u8  Copy_u8ColumnNumber){
	if( Copy_u8RowNumber == CLCD_ROW_1){
		CLCD_voidSendCommend(0x80 + ( Copy_u8ColumnNumber - 1));
	}
	else if ( Copy_u8RowNumber == CLCD_ROW_2){
		CLCD_voidSendCommend(0x80 + 64 +( Copy_u8ColumnNumber - 1));
	}
}
//u8 customChar[] = {
//  0x00,
//  0x04,
//  0x00,
//  0x11,
//  0x11,
//  0x11,
//  0x0A,
//  0x04
//};

void CLCD_voidSendExtraChar  ( u8  Copy_u8RowNumber ,u8  Copy_u8ColumnNumber){

// go to CGRam
CLCD_voidSendCommend(0b01000000);
//draw Char
for(u8 i = 0 ; i < 8 ; i ++){
	CLCD_voidSendData(i);
}
//back toDDram
CLCD_voidSendPostion(Copy_u8RowNumber,Copy_u8ColumnNumber);
// send Char
CLCD_voidSendData(0);
}
void CLCD_voidDrawExtraChar  ( u8  Copy_u8RowNumber ,u8  Copy_u8ColumnNumber , u8 Copy_u8Postion){
//back toDDram
CLCD_voidSendPostion(Copy_u8RowNumber,Copy_u8ColumnNumber);
// send Char
CLCD_voidSendData(Copy_u8Postion);
}
void CLCD_voidClearLCE(void){
	CLCD_voidSendCommend( 0b00000001 );
	_delay_ms(1);
}
