/*
 * GIE_program.c
 *
 *  Created on: Apr 15, 2021
 *      Author: ceto2
 */

#include "../../Services/STD_TYPE.h"
#include "../../Services/BIT_MATH.h"
#include"../1-DIO/DIO_interface.h"
#include "GIE_private.h"
#include "GIE_interface.h"
#include "GIE_config.h"
void GIE_voidEnableGIE(void){
	SET_BIT( SREG , DIO_PIN7 );
}
void GIE_voidDisabelGIE(void){
	CLR_BIT(SREG, DIO_PIN7 );
}
