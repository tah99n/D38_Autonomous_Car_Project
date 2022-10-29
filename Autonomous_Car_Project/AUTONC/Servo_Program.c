/*
 * Servo_Program.c
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


void Servo_OFF (void){
	TMR_timer2stop();
}

void Servo_RotateDegree(s8 Angle){
	
			TMR_timer2init();
			TMR_timer2SetCompareMatchValue(2*Angle+190);//range  -30 to 30   -30 = (130)   30 = (250)
			TMR_timer2start();
}