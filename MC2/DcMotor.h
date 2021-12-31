/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the Dc Motor driver
 *
 * Author: Yousif
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define Motor_PORT_ID         PORTC_ID
#define Motor_FIRST_PIN_ID     PIN5_ID
#define Motor_SECOND_PIN_ID    PIN6_ID
/*******************************************************************************
 *                                Types Definitions                             *
 *******************************************************************************/
typedef enum
{
	Stop,AntiClockwise,Clockwise
}DcMotor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the dc motor
 */
void DcMotor_Init(void);
/*
 * Description :
 * Function responsible for rotating dc motor Clockwise
 */
void DcMotor_Rotate_Clockwise();
/*
 * Description :
 * Function responsible for rotating dc motor AntiClockwise
 */
void DcMotor_Rotate_AntiClockwise();
/*
 * Description :
 * Function responsible for stopping dc motor
 */
void DcMotor_Stop();

#endif /* DCMOTOR_H_ */
