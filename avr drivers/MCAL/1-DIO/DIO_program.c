
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"


DIO_ErrorStatus DIO_enumSetPortDirection( u8 Copy_u8Port , u8 Copy_u8Direction ){

	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	switch( Copy_u8Port ){

	case DIO_PORTA: DDRA_REG = Copy_u8Direction   ;  break;
	case DIO_PORTB: DDRB_REG = Copy_u8Direction   ;  break;
	case DIO_PORTC: DDRC_REG = Copy_u8Direction   ;  break;
	case DIO_PORTD: DDRD_REG = Copy_u8Direction   ;  break;
	default       : LOC_enumState = DIO_NOK   ;  break;

	}

	return LOC_enumState ;

}


DIO_ErrorStatus DIO_enumSetPortValue    ( u8 Copy_u8Port , u8 Copy_u8Value ){

	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	switch( Copy_u8Port ){

	case DIO_PORTA: PORTA_REG = Copy_u8Value     ;  break;
	case DIO_PORTB: PORTB_REG = Copy_u8Value     ;  break;
	case DIO_PORTC: PORTC_REG = Copy_u8Value     ;  break;
	case DIO_PORTD: PORTD_REG = Copy_u8Value     ;  break;
	default       : LOC_enumState = DIO_NOK  ;  break;

	}

	return LOC_enumState ;

}

DIO_ErrorStatus DIO_enumSetPinDirection  ( u8 Copy_u8Port , u8 Copy_u8PinNumber , u8 Copy_u8Direction ){

	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	if( ( Copy_u8PinNumber >= DIO_PIN0 ) && ( Copy_u8PinNumber <= DIO_PIN7 ) ){

		switch( Copy_u8Port ){

		case DIO_PORTA:

			if      ( Copy_u8Direction == DIO_OUTPUT ){ SET_BIT( DDRA_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Direction == DIO_INPUT  ){ CLR_BIT( DDRA_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;

		case DIO_PORTB:

			if      ( Copy_u8Direction == DIO_OUTPUT ){ SET_BIT( DDRB_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Direction == DIO_INPUT  ){ CLR_BIT( DDRB_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;
		case DIO_PORTC:

			if      ( Copy_u8Direction == DIO_OUTPUT ){ SET_BIT( DDRC_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Direction == DIO_INPUT  ){ CLR_BIT( DDRC_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;
		case DIO_PORTD:

			if      ( Copy_u8Direction == DIO_OUTPUT ){ SET_BIT( DDRD_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Direction == DIO_INPUT  ){ CLR_BIT( DDRD_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;

		default      : LOC_enumState = DIO_NOK ; break;

		}

	}else{ LOC_enumState = DIO_NOK ; }

	return LOC_enumState ;
}
DIO_ErrorStatus DIO_enumSetPinValue      ( u8 Copy_u8Port , u8 Copy_u8PinNumber , u8 Copy_u8Value     ){

	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	if( ( Copy_u8PinNumber >= DIO_PIN0 ) && ( Copy_u8PinNumber <= DIO_PIN7 ) ){

		switch( Copy_u8Port ){

		case DIO_PORTA:

			if      ( Copy_u8Value == DIO_HIGH ){ SET_BIT( PORTA_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Value == DIO_LOW   ){ CLR_BIT( PORTA_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;

		case DIO_PORTB:

			if      ( Copy_u8Value == DIO_HIGH ){ SET_BIT( PORTB_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Value == DIO_LOW  ){ CLR_BIT( PORTB_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;
		case DIO_PORTC:

			if      ( Copy_u8Value == DIO_HIGH ){ SET_BIT( PORTC_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Value == DIO_LOW  ){ CLR_BIT( PORTC_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;
		case DIO_PORTD:

			if      ( Copy_u8Value == DIO_HIGH ){ SET_BIT( PORTD_REG , Copy_u8PinNumber ); }

			else if ( Copy_u8Value == DIO_LOW  ){ CLR_BIT( PORTD_REG , Copy_u8PinNumber ); }

			else{ LOC_enumState = DIO_NOK ; }

			break;

		}

	}else{ LOC_enumState = DIO_NOK ; }

	return LOC_enumState ;

}

DIO_ErrorStatus DIO_enumGetPortValue     ( u8 Copy_u8Port , u8 * Copy_u8ptrData ){

	DIO_ErrorStatus LOC_enumState = DIO_OK;

	switch( Copy_u8Port ){

	case DIO_PORTA : *Copy_u8ptrData = PINA_REG ; break;
	case DIO_PORTB : *Copy_u8ptrData = PINB_REG ; break;
	case DIO_PORTC : *Copy_u8ptrData = PINC_REG ; break;
	case DIO_PORTD : *Copy_u8ptrData = PIND_REG ; break;
	default        : LOC_enumState = DIO_NOK    ; break;

	}

	return LOC_enumState ;

}
DIO_ErrorStatus DIO_enumGetPinValue      ( u8 Copy_u8Port , u8 Copy_u8PinNumber , u8 * Copy_u8ptrData ){

	DIO_ErrorStatus LOC_enumState = DIO_OK;

	if( ( Copy_u8PinNumber >= DIO_PIN0 ) && ( Copy_u8PinNumber <= DIO_PIN7 ) ){

		switch( Copy_u8Port ){

		case DIO_PORTA : *Copy_u8ptrData = GET_BIT( PINA_REG , Copy_u8PinNumber ) ; break;
		case DIO_PORTB : *Copy_u8ptrData = GET_BIT( PINB_REG , Copy_u8PinNumber ) ; break;
		case DIO_PORTC : *Copy_u8ptrData = GET_BIT( PINC_REG , Copy_u8PinNumber ) ; break;
		case DIO_PORTD : *Copy_u8ptrData = GET_BIT( PIND_REG , Copy_u8PinNumber ) ; break;
		default        : LOC_enumState = DIO_NOK    ; break;

		}

	}
	else{ LOC_enumState = DIO_NOK    ; }

	return LOC_enumState ;

}


