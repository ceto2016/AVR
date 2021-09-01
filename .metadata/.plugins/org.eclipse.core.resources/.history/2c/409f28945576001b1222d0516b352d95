
#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef struct{
	
	u8 Port         ;
	u8 Pin          ;
	u8 Active_State ;
	
}LED_Type;

#define ACTIVE_LOW    0
#define ACTIVE_HIGH   1

void LED_voidInit( LED_Type LED_Config );
void LED_voidOn  ( LED_Type LED_Config );
void LED_voidOff ( LED_Type LED_Config );

#endif