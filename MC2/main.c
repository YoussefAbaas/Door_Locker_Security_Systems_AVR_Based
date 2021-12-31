/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mohamed Tarek
 Description : MC1 Code in Exercise2
 Date        : 19/9/2014
 ================================================================================================
 */
//MC2
#define F_CPU 8000000UL
#define MC2_READY 0x10
#include "uart.h"
#include "util/delay.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "lcd.h"
#include "DcMotor.h"
#include "gpio.h"
#include "external_eeprom.h"
#include "Timer.h"
#include "Buzzer.h"
void receive_password(uint8*password);
void check_pw(uint8*password,uint8*check_password);
void eeprom_save_password(uint8*password);
void eeprom_load_password(uint8*password);
volatile uint8 check_flag=1;
int main(void)
{

	unsigned char password[4];
	unsigned char check_password[4];
	TimerConfig Timer0_Config = {Normal,F_CPU_1024,0,0};
	Timer0_Init(&Timer0_Config);
	UART_Config uart_config = {9600,ASYNC,BIT1,DISABLED};
	UART_init(&uart_config);
	DcMotor_Init();
	Buzzer_Init();
	UART_sendByte(MC2_READY);
	SREG |= (1<<7);
	do
	{
		receive_password(password);
		receive_password(check_password);
		check_pw(password,check_password);
	}
	while(check_flag==0);
	eeprom_save_password(password);
	while(1)
	{
		uint8 command=UART_recieveByte();
		_delay_ms(100);
		if(command=='-')
		{
			do
			{
				receive_password(password);
				receive_password(check_password);
				check_pw(password,check_password);
			}
			while(check_flag==0);
			eeprom_save_password(password);
		}
		else if(command=='+')
		{
			eeprom_load_password(password);
			uint8 count=0;
			do
			{
				count++;
				receive_password(check_password);
				check_pw(password,check_password);
			}
			while(check_flag==0&&count<3);
			if(check_flag==1)
			{
				Timer0_seconds_MC2=0;
				while(Timer0_seconds_MC2<15)Timer0_setCallBack(DcMotor_Rotate_Clockwise);
				while(Timer0_seconds_MC2<18)Timer0_setCallBack(DcMotor_Stop);
				while(Timer0_seconds_MC2<33)Timer0_setCallBack(DcMotor_Rotate_AntiClockwise);
				Timer0_setCallBack(DcMotor_Stop);
			}
			else if(check_flag==0)
			{
				/* activate Puzzer*/
				Buzzer_On();
				Timer0_seconds_MC2 = 0;
				while ( Timer0_seconds_MC2 <= 60);         			// Lock Mc for 60 seconds
				Buzzer_Off();
			}
		}


	}
}
void receive_password(uint8*password)
{
	for(int i=0;i<4;i++)
	{
		password[i]=UART_recieveByte();
		_delay_ms(100);
	}
	_delay_ms(100);
}
void check_pw(uint8*password,uint8*check_password)
{
	for(uint8 i=0;i<4;i++)
	{
		if(password[i]!=check_password[i])
		{
			UART_sendByte(0);
			_delay_ms(130);
			check_flag=0;
			break;
		}
		check_flag=1;
	}
	if(check_flag==1){UART_sendByte(1);}
}
void eeprom_save_password(uint8*password)
{
	for (uint8 i = 0; i < 4; i++) {
			EEPROM_writeByte( (0x80 + i), password[i] );
			_delay_ms(100);
		}
}

void eeprom_load_password(uint8*password)
{
	for (uint8 i = 0; i < 4; i++) {
					EEPROM_readByte((0x80+i), (password+i));
					_delay_ms(100);
				}
}
