/*
 * GI_Program.c
 *
 *
 *  Author: Ammar Mahmoud,Mahmoud Tahoun,Mohammed ElSayed,Mohammed Khalid
 */

//UTILES
#include "TYPE_DEF.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

//MCAL
#include "GI_Interface.h"

void GI_Enable  (void){
	SET_BIT(SREG,7);// Set Status Register
}

void GI_Disable (void){
	CLR_BIT(SREG,7);// Reset Status Register
}