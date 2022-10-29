/*
 * AUTONC.c
 *
 *
 *  Author: Ammar Mahmoud,Mahmoud Tahoun,Mohammed ElSayed,Mohammed Khalid
 */


#define F_CPU 16000000UL
#include <util/delay.h>

//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "DIO_Interface.h"
#include "TMR_Interface.h"
#include "GI_Interface.h"
#include "EXTI_Interface.h"

//HAL
#include "USS_Interface.h"
#include "LCD_Interface.h"
#include "DCM_Interface.h"
#include "Servo_Interface.h"


#include "AUTONC_Interface.h"

void STOP_Function(void);

int main(void)
{
	u32 distance,distanceRight,distanceLeft; // to get USS distances
	AUTONC_init(); // Directions and initialization modules
	GI_Enable();
	EXTI_INT0SetCallBack(&STOP_Function);// external interrupt to stop the program
	EXTI_Enable(EXTI_INT0,EXTI_FALLING_EDGE);// direct when pressing button 2 
	AUTONC_DisplayProjectDetails();
//Start
Move:
	USS_GetDistance(&distance);
	while( (distance>=30) && (distance<=1000) ){
		AUTONC_setCarState(AUTONC_FORWARD);
		//servo on right
		Servo_RotateDegree(30);//servo rotate right
        AUTONC_ControlSpeed();
		USS_GetDistance(&distanceRight);
		_delay_ms(10);
		LCD_clear();
		LCD_AmitSendString((u8*)"FWD Nearest obj. after:");
		LCD_writeNumber(distanceRight);
		LCD_AmitSendString((u8*)" cm");
		//servo on center
		AUTONC_setCarState(AUTONC_FORWARD);
		Servo_RotateDegree(0);//servo rotate to center
		AUTONC_ControlSpeed();
		USS_GetDistance(&distance);
		_delay_ms(10);
		LCD_clear();
		LCD_AmitSendString((u8*)"FWD Nearest obj. after:");
		LCD_writeNumber(distance);
		LCD_AmitSendString((u8*)" cm");
		//servo on Left
		AUTONC_setCarState(AUTONC_FORWARD);
		Servo_RotateDegree(-30);//servo rotate Left
		AUTONC_ControlSpeed();
		USS_GetDistance(&distanceLeft);
		_delay_ms(10);
		LCD_clear();
		LCD_AmitSendString((u8*)"FWD Nearest obj. after:");
		LCD_writeNumber(distanceLeft);
		LCD_AmitSendString((u8*)" cm");
		
		Servo_RotateDegree(0);// servo back to center
		if((distanceRight>=distanceLeft) && (distanceRight>=distance) && (distance<40) ){
			AUTONC_setCarState(AUTONC_ROTATE_RIGHT);
			LCD_clear();
			LCD_AmitSendString((u8*)"Rotate Right -->");
			_delay_ms(40);
		}
		else if((distanceLeft>=distanceRight) && (distanceLeft>=distance) && (distance<40) ){
			AUTONC_setCarState(AUTONC_ROTATE_LEFT);
			LCD_clear();
			LCD_AmitSendString((u8*)"Rotate Left <--");
			_delay_ms(40);
		}
		else{
			
			//continue
		}

		AUTONC_setCarState(AUTONC_STOP);// to control speed
		_delay_ms(150);// for LCD and repeatability and servo
		USS_GetDistance(&distance);	
	}
	
		USS_GetDistance(&distance);
		
	while( (distance<30) || (distance>1000) ){
		
			AUTONC_setCarState(AUTONC_BACKWARD);
			LCD_clear();
			USS_GetDistance(&distance);
			LCD_AmitSendString((u8*)"BWD Nearest obj. after:");
			LCD_writeNumber(distance);
			LCD_AmitSendString((u8*)" cm");
			_delay_ms(200);
			AUTONC_setCarState(AUTONC_STOP);
			USS_GetDistance(&distance);
			_delay_ms(500);
	}
		goto Move;

}
void STOP_Function(void){//force stop
	AUTONC_setCarState(AUTONC_STOP);
	Servo_RotateDegree(0);
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,3);
	LCD_AmitSendString((u8*)"Thank you");
	while(1){}
}

