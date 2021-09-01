
#include "../../Services/STD_TYPE.h"
#include "../../Services/BIT_MATH.h"

#include "../../MCAL/1-DIO/DIO_interface.h"

#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"


void SW_voidInit    ( SW_Type SW_Config ){

	DIO_enumSetPinDirection( SW_Config.Port , SW_Config.Pin , DIO_INPUT );

	if( SW_Config.Pull_State == SW_PULL_UP ){

		DIO_enumSetPinValue( SW_Config.Port , SW_Config.Pin , DIO_HIGH );

	}

}
u8   SW_u8GetPressed( SW_Type SW_Config ){

	u8 LOC_u8Result = 0;

	DIO_enumGetPinValue( SW_Config.Port , SW_Config.Pin , &LOC_u8Result );

	return LOC_u8Result ;

}
