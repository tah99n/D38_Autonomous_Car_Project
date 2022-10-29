/*
 * DCM_Program.c
 *
 *
 *  Author: Ammar Mahmoud,Mahmoud Tahoun,Mohammed ElSayed,Mohammed Khalid
 */

//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "DIO_Interface.h"
#include "TMR_Interface.h"
#include "TMR_Config.h"

//HAL
#include "DCM_Interface.h"


void DCM_Init(void){
	
	  DIO_SetPinDirection(DIO_PORTD,DIO_PIN4,DIO_PIN_OUTPUT); //EN1
	  DIO_SetPinDirection(DIO_PORTD,DIO_PIN5,DIO_PIN_OUTPUT); //EN2
	  
	  DIO_SetPinDirection(DIO_PORTC,DIO_PIN3,DIO_PIN_OUTPUT);//MA pin1
	  DIO_SetPinDirection(DIO_PORTC,DIO_PIN4,DIO_PIN_OUTPUT);//MA pin2
	  DIO_SetPinDirection(DIO_PORTC,DIO_PIN5,DIO_PIN_OUTPUT);//MB pin1
	  DIO_SetPinDirection(DIO_PORTC,DIO_PIN6,DIO_PIN_OUTPUT);//MB pin2
}



void DCM_ON(u8 MotorNumber,u8 Direction){
	
	switch(MotorNumber){
		case DCM_MOTOR1:
		DIO_SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_HIGH);
		if (Direction==DCM_CW)
		{
			 DIO_SetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH);
			 DIO_SetPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_LOW);
		}
		else if (Direction==DCM_CCW){
			DIO_SetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_LOW);
			DIO_SetPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_HIGH);
			
		}
		break;
		
		case DCM_MOTOR2:
		DIO_SetPinValue(DIO_PORTD,DIO_PIN5,DIO_PIN_HIGH);
		if (Direction==DCM_CW)
		{
			DIO_SetPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_HIGH);
			DIO_SetPinValue(DIO_PORTC,DIO_PIN6,DIO_PIN_LOW);
		}
		else if (Direction==DCM_CCW){
			DIO_SetPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_LOW);
			DIO_SetPinValue(DIO_PORTC,DIO_PIN6,DIO_PIN_HIGH);
			
		}
		break;	
	}
}

void DCM_OFF(u8 MotorNumber){
	switch(MotorNumber){
		case DCM_MOTOR1:
		DIO_SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_LOW);
		break;
		case DCM_MOTOR2:
		DIO_SetPinValue(DIO_PORTD,DIO_PIN5,DIO_PIN_LOW);
		break;
		
	}
}

