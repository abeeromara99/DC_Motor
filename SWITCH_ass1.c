/*
 * SWITCH_ass1.c
 *
 *  Created on: Dec 18, 2023
 *      Author: Abir Omara
 */



/* Lib layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#define F_CPU   8000000UL

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include "LCD_interface.h"

void Motor_cw (void);
void Motor_ccw (void);
void STOP_MOTOR (void);

int main ()
{

	u8 Correct_password [4]={'1','1','1','1'};
	u8 Input_password [4];
	u8 Local_u8Counter=0;
	u8 Local_u8NumOfAttempts=0;
	u8 Local_u8NumOfMaxAttempts=3;
	u8 Local_u8Flag;
	u8 Local_u8Choose_motor=0;
	u8 Local_u8Choose_motor_direction=0;
	u8 Local_u8Exit=0;


	u8 Local_u8Key;

	DIO_voidInit();
	LCD_voidInt();


	while (Local_u8NumOfAttempts !=Local_u8NumOfMaxAttempts)
	{
		LCD_u8GoToXY(1,0);
		LCD_voidWriteString("Enter password");
		while (Local_u8Counter != 4)
		{
			KPD_u8GetKeyState(&Local_u8Key);
			//if there are no switch pressed
			//no displaying on LCD
			if (Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
			{
				LCD_u8GoToXY(2,Local_u8Counter);
				LCD_voidSendData(Local_u8Key);
				_delay_ms(200);
				LCD_u8GoToXY(2,Local_u8Counter);
				LCD_voidSendData('*');
				Input_password[Local_u8Counter]=Local_u8Key;
				Local_u8Counter++;
			}
		}
		if ((Input_password[0]==Correct_password[0]) && (Input_password[1]==Correct_password[1]) && (Input_password[2]==Correct_password[2])  &&(Input_password[3]==Correct_password[3]))
		{
			Local_u8Flag=0;
		}

		else
		{
			Local_u8Flag=1;
		}
		if (Local_u8Flag ==0)
		{
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("Welcome to motor Dash Board");
			_delay_ms(3000);
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("1-DC Motor      2-Exit");
			Local_u8Choose_motor=0;
			while (Local_u8Choose_motor !=1)
			{
				KPD_u8GetKeyState(&Local_u8Key);

				if (Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
				{
					LCD_voidClearDisplay();
					LCD_u8GoToXY(1,0);
					LCD_voidSendData(Local_u8Key);

					switch (Local_u8Key)
					{
					case '1':
						LCD_voidClearDisplay();
						LCD_u8GoToXY(1,0);
						LCD_voidWriteString("1-cw       2-ccw3-Off     4-back");
						Local_u8Choose_motor_direction=0;
						while (Local_u8Choose_motor_direction!=1)
						{
							KPD_u8GetKeyState(&Local_u8Key);
							if (Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
							{
								LCD_voidClearDisplay();
								LCD_u8GoToXY(1,0);
								LCD_voidSendData(Local_u8Key);

								switch (Local_u8Key)
								{
								case '1':
									LCD_u8GoToXY(2,0);
									LCD_voidWriteString("Rotate CW");
									Motor_cw();
									_delay_ms(1000);
									break;
								case '2':
									LCD_u8GoToXY(2,0);
									LCD_voidWriteString("Rotate CCW");
									Motor_ccw();
									break;
								case '3':
									LCD_u8GoToXY(2,0);
									LCD_voidWriteString("Turn Off");
									STOP_MOTOR();
									break;
								default:
									Local_u8Choose_motor_direction=1;
									Local_u8Choose_motor=1;
								}
							}
						}
						break;
					case '2':
						Local_u8Choose_motor=1;
						LCD_voidClearDisplay();
						Local_u8Counter=0;

						break;
					}
				}
			}
		}


		else if (Local_u8Flag==1)
		{
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("incorrect       password");
			_delay_ms(500);
			LCD_voidClearDisplay();
			//LCD_u8GoToXY(1,0);
			//LCD_voidWriteString("try again");
			//_delay_ms(1000);
			Local_u8Counter=0;
			Local_u8NumOfAttempts++;
			if (Local_u8NumOfAttempts ==Local_u8NumOfMaxAttempts)
			{
				LCD_voidClearDisplay();
				LCD_u8GoToXY(1,0);
				LCD_voidWriteString("you tried 3     times");
				_delay_ms(1000);
				LCD_voidClearDisplay();
				LCD_u8GoToXY(1,0);
				LCD_voidWriteString("wait for 5 sec  and try later");
				_delay_ms(5000);
				LCD_voidClearDisplay();
				Local_u8NumOfAttempts=0;
			}
		}


	}

	return 0;
}

void Motor_cw (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN0,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_PIN_LOW);
}
void Motor_ccw (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN0,DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_PIN_HIGH);
}

void STOP_MOTOR (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN0,DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_PIN_LOW);
}
