/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mohamed Tarek
 Description : MC1 Code in Exercise2
 Date        : 19/9/2014
 ================================================================================================
 */
//MC1
#define F_CPU 8000000UL
#define MC2_READY 0x10
#include "uart.h"
#include "keypad.h"
#include "lcd.h"
#include "util/delay.h"
#include "avr/io.h"
#include "Timer.h"
void read_password(uint8*password);
void send_password(uint8*password);
int main(void)
{
	unsigned char password[5];
	unsigned char check_password[5];
	volatile unsigned char check_result=0;
	TimerConfig Timer0_Config = {Normal,F_CPU_1024,0,0};
	Timer0_Init(&Timer0_Config);
	LCD_init();
	UART_Config uart_config = {9600,ASYNC,BIT1,DISABLED};
	UART_init(&uart_config);
	SREG |= (1<<7);
	//while(UART_recieveByte()!=MC2_READY);
	_delay_ms(500); // delay to wait for MC2 to be ready
	do
	{
		LCD_clearScreen();
		LCD_displayString("Enter Password");
		LCD_moveCursor(1,0);
		read_password(password);
		_delay_ms(500);
		send_password(password);
		LCD_clearScreen();
		LCD_displayString("Re-enter Password");
		LCD_moveCursor(1,0);
		read_password(check_password);
		_delay_ms(500);
		send_password(check_password);
		//_delay_ms(500);
		check_result=UART_recieveByte();
		if(check_result!=1)
		{
			LCD_clearScreen();
			LCD_displayString("invalid password");
			_delay_ms(500);
		}
	}
	while(check_result!=1);
	LCD_clearScreen();
	LCD_displayString("Correct Password");
	_delay_ms(1000);
	while(1){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"- : Change Password");
		LCD_displayStringRowColumn(1,0,"+ : Open Door");
		uint8 command=KEYPAD_getPressedKey();
		_delay_ms(500);
		UART_sendByte(command);
		_delay_ms(100);
		if(command=='-')
		{
			do
			{
				LCD_clearScreen();
				LCD_displayString("Enter Password");
				LCD_moveCursor(1,0);
				read_password(password);
				_delay_ms(500);
				send_password(password);
				LCD_clearScreen();
				LCD_displayString("Re-enter Password");
				LCD_moveCursor(1,0);
				read_password(check_password);
				_delay_ms(500);
				send_password(check_password);
				//_delay_ms(500);
				check_result=UART_recieveByte();
				if(check_result!=1)
				{
					LCD_clearScreen();
					LCD_displayString("invalid password");
					_delay_ms(500);
				}
			}
			while(check_result!=1);
			LCD_clearScreen();
			LCD_displayString("Password Changed");
		}
		else if(command=='+')
		{
			uint8 count=0;
			do
			{
				count++;
				LCD_clearScreen();
				LCD_displayString("Enter Password");
				LCD_moveCursor(1,0);
				read_password(password);
				_delay_ms(500);
				send_password(password);
				//_delay_ms(500);
				check_result=UART_recieveByte();
				if(check_result!=1)
				{
					LCD_clearScreen();
					LCD_displayString("wrong password");
					_delay_ms(500);
				}
			}
			while(check_result!=1&&count<3);
			if(check_result==1)
			{
				Timer0_seconds_MC1=0;
				LCD_clearScreen();
				LCD_displayString("opening door");
				while(Timer0_seconds_MC1<15);
				LCD_clearScreen();
				LCD_displayString("door opened");
				while(Timer0_seconds_MC1<18);
				LCD_clearScreen();
				LCD_displayString("closing door");
				while(Timer0_seconds_MC1<33);
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("Activate Alarm");
				Timer0_seconds_MC1=0;
				while(Timer0_seconds_MC1<60);
			}
		}
	}


}
void read_password(uint8*password)
{
	for (uint8 i = 0; i < 5; i++) {
		uint8 keypad_value=KEYPAD_getPressedKey();
		while ((i == 4)&&(keypad_value != 13));

		password[i] = KEYPAD_getPressedKey();
		_delay_ms(500);
		LCD_displayCharacter('*');
	}
}
void send_password(uint8*password)
{
	for (uint8 i=0 ; i<4 ; i++)
	{
		UART_sendByte( password[i] );
		_delay_ms(130);
	}
}
