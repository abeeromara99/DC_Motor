/******************************************************************************************/
/******************************************************************************************/
/******************************     Name   :  Abir Omara     ******************************/
/******************************     Date   :  07/12/2023     ******************************/
/******************************     SWC    :  KPD            ******************************/
/******************************   Version  :  1.0            ******************************/
/******************************************************************************************/
/******************************************************************************************/

/* Lib layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#define F_CPU   8000000UL

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"

const u8 KPD_Au8Keys[4][4]=KPD_KEYS;

const u8 KPD_Au8RowsPin[4]={KPD_u8_R1_PIN,KPD_u8_R2_PIN,KPD_u8_R3_PIN,KPD_u8_R4_PIN};

const u8 KPD_Au8ColumssPin[4]={KPD_u8_C1_PIN,KPD_u8_C2_PIN,KPD_u8_C3_PIN,KPD_u8_C4_PIN};

u8 KPD_u8GetKeyState (u8 * Copy_pu8ReturnedKey)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8RowsCounter;
	u8 Local_u8ColumsCounter;
	u8 Local_u8PinValue;
	u8 Local_u8Flag=0;

	if (Copy_pu8ReturnedKey != NULL)
	{
		*Copy_pu8ReturnedKey=KPD_u8_KEY_NOT_PRESSED;
		/*Activate each row => for loop in the pins of the rows*/
		for (Local_u8RowsCounter=0 ;Local_u8RowsCounter<=3;Local_u8RowsCounter++)
		{
			DIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPin[Local_u8RowsCounter],DIO_u8_PIN_LOW);
			/*check which input pin has zero*/
			for(Local_u8ColumsCounter=0;Local_u8ColumsCounter<=3;Local_u8ColumsCounter++)
			{
				DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColumssPin[Local_u8ColumsCounter],&Local_u8PinValue);
				if (Local_u8PinValue == DIO_u8_PIN_LOW) /*switch is pressed*/
				{
					/*Debouncing */
					_delay_ms(20);
					DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColumssPin[Local_u8ColumsCounter],&Local_u8PinValue);
					/*Check if Pin still equal low */
					while (Local_u8PinValue == DIO_u8_PIN_LOW)
					{
						DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8ColumssPin[Local_u8ColumsCounter],&Local_u8PinValue);
					}
					*Copy_pu8ReturnedKey =KPD_Au8Keys [Local_u8RowsCounter][Local_u8ColumsCounter];
					Local_u8Flag=1;
					break;
				}
			}
			/*Deactivate Row  */
			DIO_u8SetPinValue(KPD_u8_PORT,KPD_Au8RowsPin[Local_u8RowsCounter],DIO_u8_PIN_HIGH);
			if (Local_u8Flag ==1)
			{
				break;
			}
		}

	}
	else
	{
		u8 Local_u8ErrorState = STD_TYPES_NOK;

	}
	return Local_u8ErrorState;
}
