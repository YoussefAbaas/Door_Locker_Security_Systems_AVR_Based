/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: Timer.c
 *
 * Description: source file for the Timer driver
 *
 * Author: Yousif
 *
 *******************************************************************************/
#include "avr/io.h"
#include <avr/interrupt.h>
#include "Timer.h"
/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/
volatile uint32 Timer0_seconds_MC1=0;
volatile uint32 Timer0_seconds_MC2=0;
volatile uint32 Timer1_seconds_MC1=0;
volatile uint32 Timer1_seconds_MC2=0;
uint8 timer0_ticks=0;
uint8 timer1_ticks=0;
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                                ISR Definitions                             *
 *******************************************************************************/
ISR (TIMER0_OVF_vect) /* ISR for timer 0 works with normal mode*/
{
	timer0_ticks++;
	if(timer0_ticks==NUMBER_OF_OVERFLOWS_PER_SECOND_TIMER0)
	{
Timer0_seconds_MC1++;Timer0_seconds_MC2++;
if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
   timer0_ticks=0;
	}
}
ISR (TIMER1_OVF_vect) /* ISR for timer 1 works with normal mode*/
{
Timer1_seconds_MC1++;Timer1_seconds_MC2++;
if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR (TIMER0_COMP_vect) /* ISR for timer 0 works with compare mode */
{
	timer0_ticks++;
	if(timer0_ticks==NUMBER_OF_COMPARES_PER_SECOND_TIMER0)
	{
Timer0_seconds_MC1++;Timer0_seconds_MC2++;
if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
    timer0_ticks=0;
	}
}
ISR (TIMER1_COMPA_vect) /* ISR for timer 1 works with compare mode */
{
Timer1_seconds_MC1++;Timer1_seconds_MC2++;
if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Timer0_Init(TimerConfig*Config_ptr)
{
	TCNT0 = Config_ptr->initial_value; //Set Timer initial value to 0
	if(Config_ptr->mode==Normal)
	{
	TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock
	 */
	TCCR0 = Config_ptr->clock|Config_ptr->mode;
	}
	if(Config_ptr->mode==CTC)
		{
		TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
		/* Configure timer0 control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM01=1 & WGM00=0
			 * 3. No need for OC0 in this example so COM00=0 & COM01=0
			 * 4. clock
			 */
		TCCR0 = Config_ptr->clock|Config_ptr->mode;
		OCR0  = Config_ptr->compare_value; // Set Compare Value
		}
}
void Timer0_Deinit()
{
	TCNT0=0;
	TCCR0=0;
	TIMSK&=~(1<<TOIE0)&~(1<<OCIE0); //stop interrupts
}
void Timer0_Stop()
{
	TCCR0&=0xf8; //clear prescaler bits
}
void Timer1_Init(TimerConfig*Config_ptr)
{

	if(Config_ptr->mode==Normal)
		{
		TCNT1 = Config_ptr->initial_value;
		TCCR1B = Config_ptr->clock|Config_ptr->mode;
		TCCR1A = (1<<FOC1A); /* Enable Timer1 Normal Mode Interrupt */
		}
	else if(Config_ptr->mode==CTC)
	{
		OCR1A = Config_ptr->compare_value;
		TCCR1B = Config_ptr->clock|Config_ptr->mode;
		TCCR1A = (1<<FOC1A);
		TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */
	}
}
void Timer1_Deinit()
{
	TCNT1=0;
	TCCR1A=0;
	TCCR1B=0;
	TIMSK&=~(1<<TOIE1)&~(1<<OCIE1A); //stop interrupts
}
void Timer1_Stop()
{
	TCCR1B&=0xf8; //clear prescaler bits
}
void Timer0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}
