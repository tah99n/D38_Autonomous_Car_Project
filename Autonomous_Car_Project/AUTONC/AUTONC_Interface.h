/*
 * AUTONC_Program.h
 *
 * 
 *  Author: Ammar Mahmoud,Mahmoud Tahoun,Mohammed ElSayed,Mohammed Khalid
 */ 


#ifndef AUTONC_INTERFACE_H_
#define AUTONC_INTERFACE_H_

#define AUTONC_STOP           0
#define AUTONC_FORWARD        1
#define AUTONC_BACKWARD       2
#define AUTONC_ROTATE_RIGHT   3
#define AUTONC_ROTATE_LEFT    4


void AUTONC_init(void);
void AUTONC_DisplayProjectDetails(void);
void AUTONC_ControlSpeed(void);




#endif /* AUTONC_INTERFACE_H_ */
