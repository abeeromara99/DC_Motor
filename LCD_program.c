/******************************************************************************************/
/******************************************************************************************/
/******************************     Name   :  Abir Omara     ******************************/
/******************************     Date   :  03/12/2023     ******************************/
/******************************     SWC    :  LCD            ******************************/
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
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

void LCD_voidInt(void)
{
	_delay_ms(35);
	/* Function set command -> N on DB3 Number of lines 1(0) or 2(1)
	                        -> F on DB2 character font 5*7(0) or 5*10(1)*/
	LCD_voidSendCommand(0b00111000);
	_delay_us(40);

	/* Display on/off  -> D on DB2 display on(1) or off(0)
	 *                 -> C on DB1 cursor on(1) or off (0) on only 5*7
	 *                 -> B on DB0 blink cursor on(1) or off(0)*/
	LCD_voidSendCommand(0b00001111);
	_delay_us(40);

	/* Clear display*/
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);

	/* Entry mode set   -> I/D on DB1 increase(1) or decrease(0) DDRAM address
	 *                  -> SH on DB0 shift display left(1) or right(0) */
	LCD_voidSendCommand(0b00000110);
}

void LCD_voidClearDisplay (void)
{
	LCD_voidSendCommand(0b00000001);
}
void LCD_voidSendCommand (u8 Copy_u8Command)
{
#if LCD_u8_MODE == LCD_u8_MODE_8_BIT
	/* step1 Rs=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_LOW);
	/* step2 RW=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_PIN_LOW);
	/* write Command */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Command);
	/* E=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_us(1);
	/* E=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
	_delay_us(1);
#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT
	/*this code in case of connect higher four bit in PORT with LCD (send higher command value and shift left for lower)
	 * in case of connect lower four bit in PORT with LCD (shift right  higher command value and send comand value)*/
	/* step1 Rs=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_LOW);
	/* step2 RW=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_PIN_LOW);
	/* write Command */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Command);
	/* E=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_us(1);
	/* E=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
	_delay_us(1);
	/*write the rest of command*/
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Command<<4);
	/* E=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_us(1);
	/* E=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
	_delay_us(1);
#else
#error "pleasse confirm right LCD_u8_MODE"
#endif
}

void LCD_voidSendData (u8 Copy_u8Data)
{
#if LCD_u8_MODE == LCD_u8_MODE_8_BIT
	/* step1 Rs=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_HIGH);
	/* step2 RW=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_PIN_LOW);
	/* write data */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Data);
	/* E=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_us(1);
	/* E=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
	_delay_us(1);
#elif LCD_u8_MODE == LCD_u8_MODE_4_BIT
	/* step1 Rs=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_HIGH);
	/* step2 RW=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_PIN_LOW);
	/* write data */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Data);
	/* E=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_us(1);
	/* E=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
	_delay_us(1);
	/* write data */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Data<<4);
	/* E=1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_us(1);
	/* E=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
	_delay_us(1);


#else
#error "pleasse confirm right LCD_u8_MODE"
#endif
}

void LCD_voidWriteString (u8 * pu8StringCopy)
{
	u8 Local_u8Count=0,Local_u8_Y_Location=0;
	for (Local_u8Count=0;pu8StringCopy[Local_u8Count] != '\0';Local_u8Count++)
	{
		if (Local_u8Count <=15)
		{
			LCD_voidSendData(pu8StringCopy[Local_u8Count]);
			_delay_ms(2);
		}
		else
		{
			LCD_u8GoToXY(2,Local_u8_Y_Location);
			LCD_voidSendData(pu8StringCopy[Local_u8Count]);
			_delay_ms(2);
			Local_u8_Y_Location++;
		}
	}
}
u8 LCD_u8GoToXY  (u8 Copy_u8LineNum, u8 Copy_u8Location)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if (Copy_u8LineNum <= 39)
	{
		switch (Copy_u8LineNum)
		{
		case LCD_u8_LINE1: LCD_voidSendCommand(0x80+Copy_u8Location);  break;
		case LCD_u8_LINE2: LCD_voidSendCommand(0xC0+Copy_u8Location); break;
		default: Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

void LCD_voidWriteNumber(u16 Copy_u16Number)
{
	u8 Local_u8Counter=0,Local_u8Digits=0,Local_u8Current;
	u16 Local_u8CopyNumber=Copy_u16Number;
	while(Local_u8CopyNumber)
	{
		Local_u8CopyNumber/=10;
		Local_u8Digits++;
	}
	Local_u8CopyNumber=Copy_u16Number;
	for(Local_u8Counter=0;Local_u8Counter<Local_u8Digits;Local_u8Counter++)
	{
		Local_u8Current=Local_u8CopyNumber/(Private_GetPower(10,Local_u8Digits-1-Local_u8Counter));
		LCD_voidSendData(Local_u8Current+'0');
		Local_u8CopyNumber%=(Private_GetPower(10,Local_u8Digits-1-Local_u8Counter));
	}

}
static u16 Private_GetPower(u8 Copy_u8Num1, u8 Copy_u8Num2)
{
	u16 Local_u8Result=1;
	u8 Local_u8Counter=0;
	for(Local_u8Counter=0;Local_u8Counter<Copy_u8Num2;Local_u8Counter++)
	{
		Local_u8Result*=Copy_u8Num1;
	}
	return Local_u8Result;
}


void LCD_voidWriteSpecialChar (u8 Copy_u8Address,u8 *pu8Array,u8 Copy_u8LineNum,u8 Copy_u8Location)
{

	u8 Local_u8Count=0;
	if (Copy_u8Address<=7)
	{
		LCD_voidSendCommand(0b01000000+8*Copy_u8Address);
	}

	for (Local_u8Count=0;Local_u8Count <8 ;Local_u8Count++)
	{
		LCD_voidSendData(pu8Array[Local_u8Count]);
	}
	LCD_u8GoToXY(Copy_u8LineNum,Copy_u8Location);
	LCD_voidSendData(Copy_u8Address);

}
