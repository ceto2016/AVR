#include "stdio.h"
#include "util/delay.h"

#include "Services/BIT_MATHS.h"
#include "Services/STD_TYPES.h"

#include "MCAL/1-DIO/DIO_interface.h"

#include "HAL/4-LCD/CLCD_interface.h"
#include "HAL/5-KEYPAD/KPD_interface.h"

#define PORTA_REG *((volatile u8 *)0x3B)

typedef enum
{

	Status_Ok,
	Status_Not_Ok

} DivideByZero;

DivideByZero calcDIVandMul(f32 *Copy_u8ArrOperend, u8 *LOC_u8ArrOprations, u8 *LOC_u8ArrOprationsIndex);
f32 calcADDandSUB(f32 *Copy_u8ArrOperend, u8 *Copy_u8ArrOprations, u8 *Copy_u8ArrOprationsIndex);

f32 toInt(u8 Copy_u8Ch);
void clearArray(u8 *Copy_ptrArray);

int main(void) {
	CLCD_voidInit();
	KPD_voidInit();
	u8 LOC_u8Iterator = 0;
	u8 LOC_u8Counter = 0;
	u8 LOC_u8ComeData = 0;
	f32 LOC_u8ArrOperands[10] 	   		   = { 0 };
	u8 LOC_u8ArrOperandsLength[10] 		   = { 0 };
	u8 LOC_u8ArrOperations[10] 	  		   = { 0 };
	u8 LOC_u8ArrOprationsIndex[10]		   = { 0 };
	u8 LOC_u8ArrOprationsIndexCounter=0;
	u8 LOC_u8OperationCounter = 0;
	u8 LOC_u8OperandCounter = 0;
	u8 LOC_u8OperationFlag	=	0;
	u8 LOC_u8ResFlag	=	0;
	f32 LOC_f32Result 		=	0;
	u32 LOC_f32ResultFraction = 0;
	DivideByZero DivideByZeroFlag = Status_Ok;
	CLCD_voidSendPostion(CLCD_ROW_1,CLCD_Column_1);
	CLCD_voidSendString((u8 *) "Calculator V0.0!");
	_delay_ms(2000);
	CLCD_voidClearDisplay();
	while (1) {
		LOC_u8ComeData = KPD_u8GetPressed();
		if (LOC_u8ComeData != 0) {
			if(LOC_u8ResFlag == 1 ){
				CLCD_voidClearDisplay();
				LOC_u8Iterator = 0;
				LOC_u8Counter = 0;
				LOC_u8OperandCounter = 0;
				LOC_u8OperationCounter = 0;
				LOC_u8OperationFlag	=	0;
				LOC_f32Result 		=	0;
				clearFArray(LOC_u8ArrOperands);
				clearArray(LOC_u8ArrOperations);
				clearArray(LOC_u8ArrOperandsLength);
				clearArray(LOC_u8ArrOprationsIndex);
				LOC_u8ResFlag = 0;
			}
			switch(LOC_u8ComeData){
			case 'E':
				LOC_u8ResFlag = 1;
				if(LOC_u8OperationFlag == 1){
					CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_1);
					CLCD_voidSendString((u8*) "Syntax Error");
					_delay_ms(1000);
					CLCD_voidClearDisplay();
					break;
				}
				DivideByZeroFlag = calcDIVandMul(LOC_u8ArrOperands, LOC_u8ArrOperations, LOC_u8ArrOprationsIndex);
				if (DivideByZeroFlag == Status_Not_Ok)
				{
					CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_1);
					CLCD_voidSendString((u8*) "Divide By Zero");
					_delay_ms(1000);
					CLCD_voidClearDisplay();
					break;
				}
				else
				{
					LOC_f32Result = calcADDandSUB(LOC_u8ArrOperands, LOC_u8ArrOperations, LOC_u8ArrOprationsIndex);
					if(LOC_f32Result == 0){
						CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_1);
						CLCD_voidSendString((u8 *)"0");
						CLCD_voidSendPostion(CLCD_ROW_1 , LOC_u8Counter  );
					}else if ( LOC_f32Result > 0){

						CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_1);
						if((u32)LOC_f32Result == 0)
							CLCD_voidSendString((u8*)"0");
						else
							CLCD_voidSendNumber(LOC_f32Result );
						CLCD_voidSendString((u8 *) ".");
						LOC_f32ResultFraction = (u32) ( LOC_f32Result * 100  );
						LOC_f32ResultFraction = LOC_f32ResultFraction % 100;
						if(LOC_f32ResultFraction == 0)
							CLCD_voidSendString((u8*)"00");
						else
							CLCD_voidSendNumber(LOC_f32ResultFraction);

						CLCD_voidSendPostion(CLCD_ROW_1 , LOC_u8Counter );
					}else if( LOC_f32Result < 0){
						LOC_f32Result = LOC_f32Result * -1;

						CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_1);
						CLCD_voidSendString((u8 *) "-");
						CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_2);

						if((u32)LOC_f32Result == 0)
							CLCD_voidSendString((u8*)"0");
						else
							CLCD_voidSendNumber(LOC_f32Result );
						CLCD_voidSendString((u8 *) ".");
						LOC_f32ResultFraction = (u32) ( LOC_f32Result * 100  );
						LOC_f32ResultFraction = LOC_f32ResultFraction % 100;

						if(LOC_f32ResultFraction == 0)
							CLCD_voidSendString((u8*)"00");
						else
							CLCD_voidSendNumber(LOC_f32ResultFraction);
						CLCD_voidSendPostion(CLCD_ROW_1 , LOC_u8Counter );
					}
				}
				break;
			case 'C':
				CLCD_voidClearDisplay();
				LOC_u8Iterator = 0;
				LOC_u8Counter = 0;
				LOC_u8ComeData = 0;
				LOC_u8OperandCounter = 0;
				LOC_u8OperationCounter = 0;
				LOC_u8OperationFlag	=	0;
				LOC_f32Result 		=	0;
				clearFArray(LOC_u8ArrOperands);
				clearArray(LOC_u8ArrOperations);
				clearArray(LOC_u8ArrOperandsLength);
				clearArray(LOC_u8ArrOprationsIndex);
				break;

			case '+':
				if(LOC_u8OperationFlag != 1 && LOC_u8ArrOperandsLength[LOC_u8OperandCounter] != 0){
					LOC_u8ArrOperations[LOC_u8OperationCounter] = '+' ;
					LOC_u8OperationCounter++;
					LOC_u8OperandCounter++;
					LOC_u8Counter++;
					LOC_u8OperationFlag = 1;
					CLCD_voidSendData('+');
				}
				else if (LOC_u8OperationFlag == 1 ){
					LOC_u8ArrOperations[LOC_u8OperationCounter - 1] = '+' ;
					CLCD_voidSendPostion(CLCD_ROW_1 , LOC_u8Counter);
					CLCD_voidSendData('+');

				}
				break;

			case '-':
				if(LOC_u8OperationFlag != 1 && LOC_u8ArrOperandsLength[LOC_u8OperandCounter] != 0){
					LOC_u8ArrOperations[LOC_u8OperationCounter] = '-' ;
					LOC_u8OperationCounter++;
					LOC_u8OperandCounter++;
					LOC_u8Counter++;
					LOC_u8OperationFlag = 1;
					CLCD_voidSendData('-');
				}
				else if (LOC_u8OperationFlag == 1 ){
					LOC_u8ArrOperations[LOC_u8OperationCounter - 1] = '-' ;
					CLCD_voidSendPostion(CLCD_ROW_1 , LOC_u8Counter);
					CLCD_voidSendData('-');
				}
				break;

			case '*':
				if(LOC_u8OperationFlag != 1 && LOC_u8ArrOperandsLength[LOC_u8OperandCounter] != 0)
				{
					LOC_u8ArrOperations[LOC_u8OperationCounter] = '*' ;
					LOC_u8ArrOprationsIndex[LOC_u8ArrOprationsIndexCounter] = LOC_u8OperationCounter;
					LOC_u8ArrOprationsIndexCounter++;
					LOC_u8OperationCounter++;
					LOC_u8OperandCounter++;
					LOC_u8Counter++;
					LOC_u8OperationFlag = 1;
					CLCD_voidSendData('*');
				}
				else if (LOC_u8OperationFlag == 1 ){
					LOC_u8ArrOperations[LOC_u8OperationCounter - 1] = '*' ;
					LOC_u8ArrOprationsIndex[LOC_u8ArrOprationsIndexCounter - 1] = LOC_u8OperationCounter  - 1;
					CLCD_voidSendPostion(CLCD_ROW_1 , LOC_u8Counter);
					CLCD_voidSendData('*');
				}
				break;

			case '/':
				if(LOC_u8OperationFlag != 1 && LOC_u8ArrOperandsLength[LOC_u8OperandCounter] != 0)
				{
					LOC_u8ArrOperations[LOC_u8OperationCounter] = '/' ;
					LOC_u8ArrOprationsIndex[LOC_u8ArrOprationsIndexCounter] = LOC_u8OperationCounter;
					LOC_u8ArrOprationsIndexCounter++;
					LOC_u8OperationCounter++;
					LOC_u8OperandCounter++;
					LOC_u8OperationFlag = 1;
					LOC_u8Counter++;
					CLCD_voidSendData('/');
				}
				else if (LOC_u8OperationFlag == 1 ){
					LOC_u8ArrOperations[LOC_u8OperationCounter - 1] = '/' ;
					LOC_u8ArrOprationsIndex[LOC_u8ArrOprationsIndexCounter - 1] = LOC_u8OperationCounter  - 1;
					CLCD_voidSendPostion(CLCD_ROW_1 , LOC_u8Counter);
					CLCD_voidSendData('/');
				}
				break;

			default:
				LOC_u8OperationFlag = 0;
				LOC_u8Counter++;
				if(LOC_u8ArrOperandsLength[LOC_u8OperandCounter] == 0 ){
					if(LOC_u8ComeData == '0' && LOC_u8OperandCounter == 0 ){
						break;
					}
					LOC_u8ArrOperands[LOC_u8OperandCounter] = toInt(LOC_u8ComeData);
					LOC_u8ArrOperandsLength[LOC_u8OperandCounter]++;
					CLCD_voidSendData(LOC_u8ComeData);
				}
				else{

					LOC_u8ArrOperands[LOC_u8OperandCounter] = LOC_u8ArrOperands[LOC_u8OperandCounter] * 10 + ( f32) toInt(LOC_u8ComeData);
					LOC_u8ArrOperandsLength[LOC_u8OperandCounter]++;
					if(LOC_u8ComeData == '0' )
						CLCD_voidSendString((u8 *) "0");
					else
						CLCD_voidSendNumber(toInt(LOC_u8ComeData));
				}
				break;

			}
		}
	}
	return 0;

}


f32 toInt(u8 Copy_u8Ch){
	return (f32)Copy_u8Ch - '0';
}


void clearArray(u8 *Copy_ptrArray){
	for(u8 LOC_u8Iterator = 0 ; LOC_u8Iterator < 10 ; LOC_u8Iterator++){
		Copy_ptrArray[LOC_u8Iterator] = 0;
	}
}
void clearFArray(f32 *Copy_ptrArray){
	for(u8 LOC_u8Iterator = 0 ; LOC_u8Iterator < 10 ; LOC_u8Iterator++){
		Copy_ptrArray[LOC_u8Iterator] = 0;
	}
}
DivideByZero calcDIVandMul(f32 *Copy_u8ArrOperend, u8 *Copy_u8ArrOprations, u8 *Copy_u8ArrOprationsIndex)
{
	DivideByZero Loc_DivideByZero = Status_Ok;
	f32 LOC_u8Res = 0;
	u8 index = 0;
	u8 LOC_u8ShiftCounter = 0;
	for (u8 i = 0; i < 10; i++)
	{
		index = *(Copy_u8ArrOprationsIndex + i) - LOC_u8ShiftCounter;
		switch (*(Copy_u8ArrOprations + index))
		{
		case '*':
			++LOC_u8ShiftCounter;
			LOC_u8Res = *(Copy_u8ArrOperend + index)  *   *(Copy_u8ArrOperend + index + 1);
			*(Copy_u8ArrOperend + index + 1) = LOC_u8Res;
			DIO_enumSetPinDirection(DIO_PORTA,DIO_PIN0, DIO_HIGH);
			TOGGEL_BIT(PORTA_REG,DIO_PIN0);
			for (u8 z = 0; z < 10; z++)
			{
				*(Copy_u8ArrOperend + z + index) = *(Copy_u8ArrOperend + z + index + 1);
				*(Copy_u8ArrOprations + z + index) = *(Copy_u8ArrOprations + z + index + 1);
			}
			break;
		case '/':
			if (*(Copy_u8ArrOperend + index + 1) == 0)
			{
				Loc_DivideByZero = Status_Not_Ok;
				return Loc_DivideByZero;
			}
			else
			{
				++LOC_u8ShiftCounter;
				LOC_u8Res = (f32)(*(Copy_u8ArrOperend + index) / (f32) * (Copy_u8ArrOperend + index + 1));
				*(Copy_u8ArrOperend + index + 1) = LOC_u8Res;
				DIO_enumSetPinDirection(DIO_PORTA,DIO_PIN0, DIO_HIGH);
				TOGGEL_BIT(PORTA_REG,DIO_PIN0);
				for (u8 z = 0; z < 10; z++)
				{
					*(Copy_u8ArrOperend + z + index) = *(Copy_u8ArrOperend + z + index + 1);
					*(Copy_u8ArrOprations + z + index) = *(Copy_u8ArrOprations + z + index + 1);
				}
				break;
			}
		}
	}
	return Loc_DivideByZero;
}
f32 calcADDandSUB(f32 *Copy_u8ArrOperend, u8 *Copy_u8ArrOprations, u8 *Copy_u8ArrOprationsIndex)
{
	f32 LOC_u8Res = *(Copy_u8ArrOperend);
	u8 i;
	for (i = 0; i < 10; i++)
	{
		switch (*(Copy_u8ArrOprations + i))
		{
		case '+':
			LOC_u8Res = *(Copy_u8ArrOperend + i) +( * (Copy_u8ArrOperend + i + 1));
			*(Copy_u8ArrOperend + i) = 0;
			*(Copy_u8ArrOperend + i + 1) = LOC_u8Res;
			break;
		case '-':
			LOC_u8Res = *(Copy_u8ArrOperend + i) - ( * (Copy_u8ArrOperend + i + 1));
			*(Copy_u8ArrOperend + i) = 0;
			*(Copy_u8ArrOperend + i + 1) = LOC_u8Res;
			break;
		}
	}
	return LOC_u8Res;
}
