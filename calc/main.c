#include "stdio.h"
#include "STD_TYPE.h"
typedef enum
{

    Status_Ok,
    Status_Not_Ok

} DivideByZero;
DivideByZero calcDIVandMul(f32 *Copy_u8ArrOperend, u8 *LOC_u8ArrOprations, u8 *LOC_u8ArrOprationsIndex);
f32 calcADDandSUB(f32 *Copy_u8ArrOperend, u8 *Copy_u8ArrOprations, u8 *Copy_u8ArrOprationsIndex);
#define null (void *)0
void main(void)
{
    u8 i;
    f32 LOC_u8ArrOperend[10] = {5, 12, 12, 4, 2, 2};
    u8 LOC_u8ArrOprations[10] = {'-', '+', '/', '+', '*'};
    u8 LOC_u8ArrOprationsIndex[10] = {2, 4};
    f32 LOC_u8FinalRes = 0;
    DivideByZero DivideByZeroFlag = Status_Ok;
    DivideByZeroFlag = calcDIVandMul(LOC_u8ArrOperend, LOC_u8ArrOprations, LOC_u8ArrOprationsIndex);
    if (DivideByZeroFlag == Status_Not_Ok)
    {
        printf("Error");
    }
    else
    {

        LOC_u8FinalRes = calcADDandSUB(LOC_u8ArrOperend, LOC_u8ArrOprations, LOC_u8ArrOprationsIndex);
        printf("output  %.2f", LOC_u8FinalRes);
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
        printf("index %d \n LOC_u8ShiftCounter = %d \n", index, LOC_u8ShiftCounter);
        switch (*(Copy_u8ArrOprations + index))
        {
        case '*':
            ++LOC_u8ShiftCounter;
            LOC_u8Res = (f32)(*(Copy_u8ArrOperend + index) * (f32) * (Copy_u8ArrOperend + index + 1));
            *(Copy_u8ArrOperend + index + 1) = LOC_u8Res;
            for (u8 z = 0; z < 10; z++)
            {
                *(Copy_u8ArrOperend + z + index) = *(Copy_u8ArrOperend + z + index + 1);
                *(Copy_u8ArrOprations + z + index) = *(Copy_u8ArrOprations + z + index + 1);
            }
            for (u8 i = 0; i < 10; i++)
                printf("Copy_u8ArrOprations %d =  %d \n", i, *(Copy_u8ArrOprations + i));
            for (u8 i = 0; i < 10; i++)
                printf("Copy_u8ArrOperend %d =  %.2f \n", i, *(Copy_u8ArrOperend + i));
            for (u8 i = 0; i < 10; i++)
                printf("Copy_u8ArrOprationsIndex %d =  %d \n", i, *(Copy_u8ArrOprationsIndex + i));
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
                for (u8 z = 0; z < 10; z++)
                {
                    *(Copy_u8ArrOperend + z + index) = *(Copy_u8ArrOperend + z + index + 1);
                    *(Copy_u8ArrOprations + z + index) = *(Copy_u8ArrOprations + z + index + 1);
                }
                for (u8 i = 0; i < 10; i++)
                    printf("Copy_u8ArrOprations %d =  %d \n", i, *(Copy_u8ArrOprations + i));
                for (u8 i = 0; i < 10; i++)
                    printf("Copy_u8ArrOperend %d =  %.2f \n", i, *(Copy_u8ArrOperend + i));
                for (u8 i = 0; i < 10; i++)
                    printf("Copy_u8ArrOprationsIndex %d =  %d \n", i, *(Copy_u8ArrOprationsIndex + i));
                break;
            }
        }
    }
    return Loc_DivideByZero;
}
f32 calcADDandSUB(f32 *Copy_u8ArrOperend, u8 *Copy_u8ArrOprations, u8 *Copy_u8ArrOprationsIndex)
{
    f32 LOC_u8Res = 0;
    u8 i;
    for (i = 0; i < 10; i++)
    {
        switch (*(Copy_u8ArrOprations + i))
        {
        case '+':
            LOC_u8Res = *(Copy_u8ArrOperend + i) + (f32)(*(Copy_u8ArrOperend + i + 1));
            *(Copy_u8ArrOperend + i) = 0;
            *(Copy_u8ArrOperend + i + 1) = LOC_u8Res;
            break;
        case '-':
            LOC_u8Res = *(Copy_u8ArrOperend + i) - (f32) * (Copy_u8ArrOperend + i + 1);
            // printf("*(Copy_u8ArrOperend + i) %d \n", *(Copy_u8ArrOperend + i));
            *(Copy_u8ArrOperend + i) = 0;
            *(Copy_u8ArrOperend + i + 1) = LOC_u8Res;
            break;
        }
    }
    return LOC_u8Res;
}