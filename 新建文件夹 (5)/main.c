#include <REGX51.H>
#include "LCD1602.h"
#include "PublicDelay.h"
#include "DHT11.h"

void main()
{
	unsigned char T=0,Humi=0;
	unsigned char i=0;
	LCD_init();
	while(DHT11_Init())	//ºÏ≤‚DHT11 «∑Ò¥Ê‘⁄
	{
		LCD_ShowString(1,1,"Error");
	}
	LCD_ShowString(1,1,"Temp:   C");
	LCD_ShowString(2,1,"Humi:   %RH");
	while(1)
	{
		DHT11_Read_Data(&T,&Humi);
		LCD_ShowNum(1,6,T,2);
		LCD_ShowNum(2,6,Humi,2);
		Delay_ms(1);
	}
}

