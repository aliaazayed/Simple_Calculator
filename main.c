/*
 * main.c
 *
 *  Created on: Aug 22, 2023
 *      Author: user
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"


#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"


#include "KPD_interface.h"

#include <avr/delay.h>


int main(void)
{
	u8 key,i=1,key1;
	s32 num1=0,num2=0;

	CLCD_voidInitialization();
	HKPD_voidInitialization();

	while(1)    //125+5=130
	{
		key= HKPD_u8GetPressedKey();
		if(key!= NOT_PRESSED)
		{
			if(key>='0'&&key<='9') //125
			{ CLCD_voidSetPosition(CLCD_ROW_1,i);
			CLCD_voidSendData(key);//'1' '2' '5'

			num1=num1*10+(key-'0'); //'1'-'0'=1    12    125     num1=5

			}

			if((key=='+')||(key=='-')||(key=='/')|| (key=='*') ) //125+
						{
							num2=num1;//125       num2=125
							num1=0;
							CLCD_voidSetPosition(CLCD_ROW_1,i);
							CLCD_voidSendData(key);
							key1=key;
						}

			if(key=='=')
			{
				CLCD_voidSetPosition(CLCD_ROW_1,i);
				CLCD_voidSendData(key);
				i++;
				switch(key1)
				{
				case '+':CLCD_voidSetPosition(CLCD_ROW_1,i); CLCD_voidSendNumber(num1+num2); break;
				case '-':CLCD_voidSetPosition(CLCD_ROW_1,i); CLCD_voidSendNumber(num2-num1); break;
				case '*':CLCD_voidSetPosition(CLCD_ROW_1,i); CLCD_voidSendNumber(num1*num2); break;
				case '/':CLCD_voidSetPosition(CLCD_ROW_1,i); CLCD_voidSendFloat((1.0*num2)/num1); break;
				}
			}
			i++;
			if(key=='c')
			{
				CLCD_voidClearScreen();
				CLCD_voidSetPosition(CLCD_ROW_1,i);
				num1=0;
				num2=0;
				i=1;

			}


		}

	}
}

