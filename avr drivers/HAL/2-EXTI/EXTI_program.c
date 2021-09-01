/*

 * EXTI_program.c
 *
 *  Created on: Apr 15, 2021
 *      Author: ceto2
 */

#include "../../Services/STD_TYPE.h"
#include "../../Services/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

#include "../1-DIO/DIO_interface.h"

void (*EXTI_Callback[3])(void) = { NULL };

void EXTI_voidSetCallBack(void (*Copy_pvoidCallBack)(void), u8 Copy_u8EXTILine)
{
	if (Copy_pvoidCallBack != NULL)
	{
		EXTI_Callback[Copy_u8EXTILine] = Copy_pvoidCallBack;
	}
}

void __vector_1(void)
{
	if (EXTI_Callback[0] != NULL)
	{
		EXTI_Callback[0]();
		EXTI_voidClearFlag(EXTI_LINE0);
	}
}
void __vector_2(void)
{
	if (EXTI_Callback[1] != NULL)
	{
		EXTI_Callback[1]();
		EXTI_voidClearFlag(EXTI_LINE1);
	}
}

void __vector_3(void)
{
	if (EXTI_Callback[2] != NULL)
	{
		EXTI_Callback[2]();
		EXTI_voidClearFlag(EXTI_LINE2);
	}
}

void EXTI_voidInit      ( void ){

	/*EXTERNAL INTERRUPT 0*/
#ifdef EXTI_LINE0_ENABLE
	SET_BIT(GICR_REG, GICR_INT0_BIT);
#if EXTI_u8Line0_Mode == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR_REG,MCUCR_ISC00_BIT);
	CLR_BIT(MCUCR_REG,MCUCR_ISC01_BIT);
#elif EXTI_u8Line0_Mode == EXTI_ON_CHANGE
	SET_BIT(MCUCR_REG,MCUCR_ISC00_BIT);
	CLR_BIT(MCUCR_REG,MCUCR_ISC01_BIT);
#elif EXTI_u8Line0_Mode == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR_REG,MCUCR_ISC00_BIT);
	SET_BIT(MCUCR_REG,MCUCR_ISC01_BIT);
#elif EXTI_u8Line0_Mode == EXTI_RISING_EDGE
	SET_BIT(MCUCR_REG, MCUCR_ISC00_BIT);
	SET_BIT(MCUCR_REG, MCUCR_ISC01_BIT);
#endif
#endif

	/*EXTERNAL INTERRUPT 1*/
#ifdef EXTI_LINE1_ENABLE
	SET_BIT(GICR_REG,GICR_INT1_BIT);
#if EXTI_u8Line1_Mode == EXTI_LOW_LEVEL
	CLR_BIT(MCUCR_REG,MCUCR_ISC10_BIT);
	CLR_BIT(MCUCR_REG,MCUCR_ISC11_BIT);
#elif EXTI_u8Line1_Mode == EXTI_ON_CHANGE
	SET_BIT(MCUCR_REG,MCUCR_ISC10_BIT);
	CLR_BIT(MCUCR_REG,MCUCR_ISC11_BIT);
#elif EXTI_u8Line1_Mode == EXTI_FALLING_EDGE
	CLR_BIT(MCUCR_REG,MCUCR_ISC10_BIT);
	SET_BIT(MCUCR_REG,MCUCR_ISC11_BIT);
#elif EXTI_u8Line1_Mode == EXTI_RISING_EDGE
	SET_BIT(MCUCR_REG,MCUCR_ISC10_BIT);
	SET_BIT(MCUCR_REG,MCUCR_ISC11_BIT);
#endif
#endif

	/*EXTERNAL INTERRUPT 2*/
#ifdef EXTI_LINE2_ENABLE
	SET_BIT(GICR_REG,GICR_INT2_BIT);
#if EXTI_u8Line1_Mode == EXTI_FALLING_EDGE
	CLR_BIT(MCUCSR_REG,MCUCSR_ISC2_BIT);
#elif EXTI_u8Line1_Mode == EXTI_RISING_EDGE
	SET_BIT(MCUCSR_REG,MCUCSR_ISC2_BIT);
#endif
#endif

}
void EXTI_voidEnable(u8 Copy_u8EXTILine, u8 Copy_EXTISense)
{
	switch (Copy_u8EXTILine)
	{
	case EXTI_LINE0:
		//enable PIE
		EXTI_voidChangeSense(Copy_EXTISense, BIT0, BIT1);
		// 		add sense mode
		SET_BIT(GICR_REG, DIO_PIN6);
		break;
	case EXTI_LINE1:

		// 		add sense mode
		EXTI_voidChangeSense(Copy_EXTISense, BIT2, BIT3);
		//enable PIE
		SET_BIT(GICR_REG, DIO_PIN7);
		break;
	case EXTI_LINE2:
		//make pin input and pull up
		// 		add sense mode
		EXTI_voidChangeSenseInt2(Copy_EXTISense, BIT6);
		//enable PIE
		SET_BIT(GICR_REG, DIO_PIN5);
		break;
	}
}

// change sense for int0 and int1
void EXTI_voidChangeSense(u8 Copy_u8SenseMode, u8 Copy_u8Pin1, u8 Copy_u8Pin2)
{
	switch (Copy_u8SenseMode)
	{
	case EXTI_LOW_LEVEL:

		CLR_BIT(MCUCR_REG, Copy_u8Pin1);

		CLR_BIT(MCUCR_REG, Copy_u8Pin2);

		break;
	case EXTI_ON_CHANGE:

		SET_BIT(MCUCR_REG, Copy_u8Pin1);

		CLR_BIT(MCUCR_REG, Copy_u8Pin2);

		break;
	case EXTI_FALLING_EDGE:

		CLR_BIT(MCUCR_REG, Copy_u8Pin1);

		SET_BIT(MCUCR_REG, Copy_u8Pin2);

		break;
	case EXTI_RISING_EDGE:

		SET_BIT(MCUCR_REG, Copy_u8Pin1);

		SET_BIT(MCUCR_REG, Copy_u8Pin2);

		break;
	default:
		return;
	}
}

// change sense for int2
void EXTI_voidChangeSenseInt2(u8 Copy_u8SenseMode, u8 Copy_u8Pin)
{
	switch (Copy_u8SenseMode)
	{
	case EXTI_FALLING_EDGE:

		CLR_BIT(MCUCR_REG, Copy_u8Pin);

		break;

	case EXTI_RISING_EDGE :
		SET_BIT(MCUCR_REG, Copy_u8Pin);

		break;
	default:
		return;
	}
}

void EXTI_voidDisable(u8 Copy_u8EXTILine)
{
	switch (Copy_u8EXTILine)
	{
	case EXTI_LINE0:
		CLR_BIT(GICR_REG, DIO_PIN6);
		break;
	case EXTI_LINE1:
		CLR_BIT(GICR_REG, DIO_PIN7);
		break;
	case EXTI_LINE2:
		CLR_BIT(GICR_REG, DIO_PIN5);
		break;
	}
}

void EXTI_voidClearFlag(u8 Copy_u8EXTILine)
{
	switch (Copy_u8EXTILine)
	{
	case EXTI_LINE0:
		SET_BIT(GIFR_REG, DIO_PIN6);
		break;
	case EXTI_LINE1:
		SET_BIT(GIFR_REG, DIO_PIN7);
		break;
	case EXTI_LINE2:
		SET_BIT(GIFR_REG, DIO_PIN5);
		break;
	}
}
