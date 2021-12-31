/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description: header file for the Buzzer driver
 *
 * Author: Yousif
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define Buzzer_PORT_ID         PORTD_ID
#define Buzzer_FIRST_PIN_ID     PIN6_ID
#define Buzzer_SECOND_PIN_ID    PIN7_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the Buzzer
 */
void Buzzer_Init(void);
/*
 * Description :
 * Function responsible for making Buzzer on
 */
void Buzzer_On();
/*
 * Description :
 * Function responsible for making Buzzer off
 */
void Buzzer_Off();

#endif /* BUZZER_H_ */
