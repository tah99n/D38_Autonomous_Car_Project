/*
 * AUTONC_Program.c
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


//HAL
#include "USS_Interface.h"
#include "USS_Config.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"
#include "DCM_Interface.h"


#include "AUTONC_Interface.h"

void AUTONC_DisplayProjectDetails(void){
	LCD_AmitSendString((u8*) " Autonomous Car");
	_delay_ms(1000);
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,3);
	LCD_AmitSendString((u8*) "Graduation");
	LCD_goToSpecificPosition(LCD_LINE_TWO,4);
	LCD_AmitSendString((u8*) "Project");
	_delay_ms(1000);
	LCD_clear();
	LCD_AmitSendString((u8*) " Team Members:");
	_delay_ms(1000);
	LCD_clear();
	LCD_AmitSendString((u8*) "-Ammar Mahmoud");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_AmitSendString((u8*) "-Mahmoud Tahoun");
	_delay_ms(1000);
	LCD_clear();
	LCD_AmitSendString((u8*) "-Mohamed ElSayed");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_AmitSendString((u8*) "-Mohammed Khalid");
	_delay_ms(1000);
	LCD_clear();
}

void AUTONC_init(void){
	
	USS_Init();
	LCD_Start_AMIT();
	LCD_Init();
	DCM_Init();
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN7,DIO_PIN_OUTPUT);// servo PWM
	DIO_SetPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);// BUZZER
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN3,DIO_PIN_INPUT);// Button  1
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN2,DIO_PIN_INPUT);// Button  2
	
}

void AUTONC_setCarState(u8 Direction){
	
	switch(Direction){
		
		case AUTONC_FORWARD:
		DCM_ON(DCM_MOTOR1,DCM_CW);
		DCM_ON(DCM_MOTOR2,DCM_CW);
		break;
		
		case AUTONC_BACKWARD:
		DCM_ON(DCM_MOTOR1,DCM_CCW);
		DCM_ON(DCM_MOTOR2,DCM_CCW);
		break;
		
		case AUTONC_ROTATE_RIGHT:
		DCM_ON(DCM_MOTOR1,DCM_CCW);
		DCM_ON(DCM_MOTOR2,DCM_CW);
		break;
		
		case AUTONC_ROTATE_LEFT:
		DCM_ON(DCM_MOTOR1,DCM_CW);
		DCM_ON(DCM_MOTOR2,DCM_CCW);
		break;
		
		case AUTONC_STOP:
		DCM_OFF(DCM_MOTOR1);
		DCM_OFF(DCM_MOTOR2);
		break;
			
	}
	
}

void AUTONC_ControlSpeed(void){
	_delay_ms(100);
	AUTONC_setCarState(AUTONC_STOP);// to control speed
	_delay_ms(50);// time for servo hardware rotate
}




