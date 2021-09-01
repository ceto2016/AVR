
#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define SSD_COMMON_CATHODE  0
#define SSD_COMMON_ANODE    1

typedef struct{
	
	u8 Type       ;
	u8 DataPort   ;
	u8 EnablePort ;
	u8 EnablePin  ;
	
}SSD_Type;

void SSD_voidSendNumber( SSD_Type Copy_structConfig , u8 Copy_u8Number );
void SSD_voidEnable    ( SSD_Type Copy_structConfig );
void SSD_voidDisable   ( SSD_Type Copy_structConfig );

#endif