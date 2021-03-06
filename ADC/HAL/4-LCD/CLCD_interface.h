/*
 * CLCD_interface.h
 *
 *  Created on: Feb 6, 2021
 *      Author: le
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_
#define CLCD_ROW_1 1
#define CLCD_ROW_2 2

#define CLCD_Column_1 1
#define CLCD_Column_2 2
#define CLCD_Column_3 3
#define CLCD_Column_4 4
#define CLCD_Column_5 5
#define CLCD_Column_6 6
#define CLCD_Column_7 7
#define CLCD_Column_8 8
#define CLCD_Column_9 9
#define CLCD_Column_10 10
#define CLCD_Column_11 11
#define CLCD_Column_12 12
#define CLCD_Column_13 13
#define CLCD_Column_14 14
#define CLCD_Column_15 15
#define CLCD_Column_16 16



void CLCD_voidInit 			 ( void );
void CLCD_voidSendData       ( u8 Copy_u8Data    );
void CLCD_voidSendCommend    ( u8 Copy_u8Commend );
void CLCD_voidSendString     ( u8 * Copy_u8ptrString );
void CLCD_voidSendNumber  	 ( u64  Copy_u64ptrNumber );
void CLCD_voidSendPostion  	 ( u8  Copy_u8RowNumber ,u8  Copy_u8ColumnNumber);
void CLCD_voidSendExtraChar  ( u8  Copy_u8RowNumber ,u8  Copy_u8ColumnNumber);
void CLCD_voidDrawExtraChar  ( u8  Copy_u8RowNumber ,u8  Copy_u8ColumnNumber , u8 Copy_u8Postion);
void CLCD_voidClearLCE		 (void);

#endif /* CLCD_INTERFACE_H_ */
