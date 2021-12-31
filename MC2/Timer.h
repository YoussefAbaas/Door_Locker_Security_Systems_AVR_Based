/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: Timer.h
 *
 * Description: header file for the Timer driver
 *
 * Author: Yousif
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUMBER_OF_OVERFLOWS_PER_SECOND_TIMER0 30
#define NUMBER_OF_COMPARES_PER_SECOND_TIMER0 30
/*******************************************************************************
 *                                Types Definitions                             *
 *******************************************************************************/
typedef enum {
	Normal=0x80,PWM=0x40,CTC=0x88,FastPWM=0x48
}Timer_Mode;
typedef enum {
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;
typedef struct
{
	Timer_Mode mode;
	Timer_Clock clock;
	uint16 initial_value;
	uint16 compare_value;
}TimerConfig;
/*******************************************************************************
 *                      Global Variables                                   *
 *******************************************************************************/
extern volatile uint32 Timer0_seconds_MC1;
extern volatile uint32 Timer0_seconds_MC2;
extern volatile uint32 Timer1_seconds_MC1;
extern volatile uint32 Timer1_seconds_MC2;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Timer0_Init(TimerConfig*Config_ptr);
void Timer0_Deinit();
void Timer0_Stop();
void Timer1_Init(TimerConfig*Config_ptr);
void Timer1_Deinit();
void Timer1_Stop();
void Timer0_setCallBack(void(*a_ptr)(void));
void Timer1_setCallBack(void(*a_ptr)(void));
#endif /* TIMER_H_ */
