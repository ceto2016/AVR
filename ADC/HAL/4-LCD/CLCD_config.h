/*
 * CLCD_config.h
 *
 *  Created on: Feb 6, 2021
 *      Author: le
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/*
 	 Options :-
 	  1-DIO_PORTA
 	  2-DIO_PORTB
 	  3-DIO_PORTC
 	  4-DIO_PORTD

 */

#define CLCD_DATA_PORT      DIO_PORTD
#define CLCD_CONTROL_PORT   DIO_PORTB

/*
 	 Options :-
 	  1-DIO_PIN0
 	  2-DIO_PIN1
 	  3-DIO_PIN2
 	  4-DIO_PIN3
 	  5-DIO_PIN4
 	  6-DIO_PIN5
 	  7-DIO_PIN6
 	  8-DIO_PIN7

 */

#define CLCD_RS             DIO_PIN0
#define CLCD_RW             DIO_PIN1
#define CLCD_EN             DIO_PIN2


#endif /* CLCD_CONFIG_H_ */
