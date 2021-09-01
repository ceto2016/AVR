
#include "../../Services/STD_TYPE.h"
#include "../../Services/BIT_MATH.h"

#include "../../MCAL/1-DIO/DIO_interface.h"

#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

//Common Cathode
const u8 SSD_u8Numbers[10]={0b00111111, 0b00000110 ,0b01011011,0b01001111,0b01100110 ,0b01101101,0b01111101 ,0b00000111, 0b01111111,0b01101111 };
void SSD_voidSendNumber( SSD_Type Copy_structConfig , u8 Copy_u8Number ){
	
	if( Copy_structConfig.Type == SSD_COMMON_CATHODE ){
		
		DIO_enumSetPortValue( Copy_structConfig.DataPort , SSD_u8Numbers[ Copy_u8Number ] );
		
	}else if( Copy_structConfig.Type == SSD_COMMON_ANODE ){
		
		DIO_enumSetPortValue( Copy_structConfig.DataPort , ~( SSD_u8Numbers[ Copy_u8Number ] ) );
		
	}
	
}
void SSD_voidEnable    ( SSD_Type Copy_structConfig ){
	
	if( Copy_structConfig.Type == SSD_COMMON_CATHODE ){
		
		DIO_enumSetPinValue( Copy_structConfig.EnablePort , Copy_structConfig.EnablePin , DIO_LOW );
				
	}else if( Copy_structConfig.Type == SSD_COMMON_ANODE ){
		
		DIO_enumSetPinValue( Copy_structConfig.EnablePort , Copy_structConfig.EnablePin , DIO_HIGH );
		
	}
	
}

void SSD_voidDisable   ( SSD_Type Copy_structConfig ){
	
	if( Copy_structConfig.Type == SSD_COMMON_CATHODE ){
		
		DIO_enumSetPinValue( Copy_structConfig.EnablePort , Copy_structConfig.EnablePin , DIO_HIGH );
				
	}else if( Copy_structConfig.Type == SSD_COMMON_ANODE ){
		
		DIO_enumSetPinValue( Copy_structConfig.EnablePort , Copy_structConfig.EnablePin , DIO_LOW );
		
	}
	
}
