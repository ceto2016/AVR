#include "Services/STD_TYPE.h"
#include "MCAL/1-DIO/DIO_interface.h"
#include "util/delay.h"
int main()
{
    DIO_ErrorStatus result;
    DIO_enumSetPortDirection(DIO_PORTA, 0xff);
    while (1)
    {
        result = DIO_enumSetPortValue(DIO_PORTA, 0b00000001);
        _delay_ms(2);
        result = DIO_enumSetPortValue(DIO_PORTA, 0b00000010);
        _delay_ms(2);
        result = DIO_enumSetPortValue(DIO_PORTA, 0b00000100);
        _delay_ms(2);
        result = DIO_enumSetPortValue(DIO_PORTA, 0b00001000);
        _delay_ms(2);
    }
    return 0;
}
