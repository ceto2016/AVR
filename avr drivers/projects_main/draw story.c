#include "../Services/STD_TYPE.h"
#include "../Services/BIT_MATH.h"

#include <util/delay.h>
#include "../MCAL/1-DIO/DIO_interface.h"
//#include "../HAL/4-LCD/CLCD_interface.h"
#define GREEN 0b00000001
#define RED 0b00000010
#define YELLOW 0b00000100
#define person 0
#define personRight 1
#define personLeft 2
int draw story(void){
	u8 personsChar[] = {
			0x0E,
			0x0A,
			0x04,
			0x0E,
			0x0E,
			0x04,
			0x0A,
			0x00,
			0x1C,
			0x14,
			0x08,
			0x1E,
			0x18,
			0x08,
			0x14,
			0x00,
			0x07,
			0x05,
			0x02,
			0x0F,
			0x03,
			0x02,
			0x05,
			0x00
	};
	CLCD_voidInit();
	CLCD_voidSendCommend(0b01000000);
	//draw Char
	for(u8 i = 0 ; i <24  ; i ++){
		CLCD_voidSendData(personsChar[i]);
	}

	CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_8 , person );
	CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_1 , person );
	_delay_ms(1000);
	CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_1 );
	CLCD_voidSendString((u8*)  " ");
	CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_2 , person );
	//	//	draw 3rd person
	CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_15 , person );
	_delay_ms(1000);
	CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_15 );
	CLCD_voidSendString((u8*) " ");
	CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_14 , person );
	_delay_ms(1000);

	while(1){
		CLCD_voidSendPostion(CLCD_ROW_1 , CLCD_Column_3 );
		CLCD_voidSendString((u8*) "              ");
		CLCD_voidSendPostion(CLCD_ROW_1 , CLCD_Column_3 );
		CLCD_voidSendString((u8*) "what you do");
		// second frame
		CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_2 , personRight );
		_delay_ms(600);
		CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_14 , personLeft );
		_delay_ms(2000);
		CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_2 , person );
		_delay_ms(600);
		CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_14 , person );
		// moving

		for(u8 i = 1 ; i <= 6 ; i++){
			CLCD_voidSendPostion(CLCD_ROW_2 , 2+ (i-1) );
			CLCD_voidSendString((u8*) " ");
			CLCD_voidDrawExtraChar(CLCD_ROW_2 , 2 + i , person );
			CLCD_voidSendPostion(CLCD_ROW_2 , 8+ (i-1) );
			CLCD_voidSendString((u8*) " ");
			CLCD_voidDrawExtraChar(CLCD_ROW_2 , 8 + i , person );
			CLCD_voidSendPostion(CLCD_ROW_2 , 14+ (i-1) );
			CLCD_voidSendString((u8*) " ");
			CLCD_voidDrawExtraChar(CLCD_ROW_2 , 14 + i , person );
			_delay_ms(600);
		}
		CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_2 , personRight );
		_delay_ms(600);
		CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_14 , personLeft );
		CLCD_voidSendPostion(CLCD_ROW_1 , CLCD_Column_3 );
		CLCD_voidSendString((u8*) "                  ");
		CLCD_voidSendPostion(CLCD_ROW_1 , CLCD_Column_3 );
		CLCD_voidSendString((u8*) "back on you");
		CLCD_voidSendPostion(CLCD_ROW_2 , CLCD_Column_1 );
		CLCD_voidSendString((u8*)  " ");
		CLCD_voidDrawExtraChar(CLCD_ROW_2 , CLCD_Column_2 , personRight );
		_delay_ms(4000);
	}
}


//	LED_Type led1 = {DIO_PORTA,DIO_PIN0 , ACTIVE_HIGH};
//	SW_Type SW1 = {DIO_PORTC,DIO_PIN7 , SW_PULL_UP};
//LED_voidInit(led1);
//SW_voidInit(SW1);
//	while(1){
//		if(SW_u8GetPressed(SW1) == DIO_LOW){
//			_delay_ms(150);
//			if(SW_u8GetPressed(SW1) == DIO_LOW){
//				LED_voidOn(led1);
//
//			}
//		}else{
//			LED_voidOff(led1);
//		}
//	}
//	return 0;
//void lcd_voidPrint

//trafic light
//LED_Type led_RED = {DIO_PORTC , DIO_PIN1 ,ACTIVE_LOW };
//	LED_voidInit(led_RED);
//	LED_Type led_YELLOW = {DIO_PORTC , DIO_PIN2 ,ACTIVE_LOW };
//	LED_voidInit(led_YELLOW);
//	LED_Type led_GREEN = {DIO_PORTC , DIO_PIN0 ,ACTIVE_LOW };
//	LED_voidInit(led_GREEN);
//
//	const u8 SSD_u8Numbers[10]={0b00111111, 0b00000110 ,0b01011011,0b01001111,0b01100110 ,0b01101101,0b01111101 ,0b00000111, 0b01111111,0b01101111 };
//	DIO_enumSetPortDirection   (DIO_PORTA, 0xff);
//	DIO_enumSetPortDirection   (DIO_PORTD, 0xff);
//	DIO_enumSetPortDirection   (DIO_PORTC, 0b00000011);
//
//	while(1){
//		for ( u8 z = 0 ; z <= 2 ; z ++){
//			DIO_enumSetPortValue(DIO_PORTC,TRAFIC_LED[z]);
//		for(u8 i = 6 ; i >= 1 ; i--){
//			DIO_enumSetPortValue(DIO_PORTA, SSD_u8Numbers[i - 1]);
//			for(u8 j = 10 ; j >= 1 ; j--){
//				_delay_ms(100);
//				DIO_enumSetPortValue(DIO_PORTD, SSD_u8Numbers[j - 1]);
//				_delay_ms(100);
//			}
//		}}
