/******************************************************************************************/
/******************************************************************************************/
/******************************     Name   :  Abir Omara     ******************************/
/******************************     Date   :  03/12/2023     ******************************/
/******************************     SWC    :  LCD            ******************************/
/******************************   Version  :  1.0            ******************************/
/******************************************************************************************/
/******************************************************************************************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define LCD_u8_LINE1    1
#define LCD_u8_LINE2    2


void LCD_voidInt(void);

void LCD_voidSendCommand (u8 Copy_u8Command);

void LCD_voidSendData (u8 Copy_u8Data);

void LCD_voidWriteString (u8 * pu8StringCopy);

u8 LCD_u8GoToXY  (u8 Copy_u8LineNum, u8 Copy_u8Location);

void LCD_voidWriteNumber(u16 Copy_u16Number);

void LCD_vidWriteNumber(u16 Copy_u16Number);
static u16 Private_GetPower(u8 Copy_u8Num1, u8 Copy_u8Num2);

void LCD_voidWriteSpecialChar (u8 Copy_u8Address,u8 *pu8Array,u8 x,u8 y);


#endif

