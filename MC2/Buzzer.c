/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Description: source file for the Buzzer driver
 *
 * Author: Yousif
 *
 *******************************************************************************/
#include "buzzer.h"
#include "gpio.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Buzzer_Init(void)
{
	GPIO_setupPinDirection(Buzzer_PORT_ID, Buzzer_FIRST_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(Buzzer_PORT_ID, Buzzer_SECOND_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_FIRST_PIN_ID, LOGIC_LOW);
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_SECOND_PIN_ID, LOGIC_LOW);
}

void Buzzer_On()
{
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_FIRST_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_SECOND_PIN_ID, LOGIC_LOW);
}
void Buzzer_Off()
{
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_FIRST_PIN_ID, LOGIC_LOW);
	GPIO_writePin(Buzzer_PORT_ID, Buzzer_SECOND_PIN_ID, LOGIC_LOW);
}
