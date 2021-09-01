/*
 * ADC_private.h
 *
 *  Created on: Apr 26, 2021
 *      Author: ceto2
 */

#ifndef HAL_7_ADC_ADC_PRIVATE_H_
#define HAL_7_ADC_ADC_PRIVATE_H_

#define ADMUX  (*(volatile u8 *)( 0x27))
#define ADCSRA (*(volatile u8 *)( 0x26))
#define ADCH   (*(volatile u8 *)( 0x25))
#define ADCL   (*(volatile u8 *)( 0x24))

#endif /* HAL_7_ADC_ADC_PRIVATE_H_ */
