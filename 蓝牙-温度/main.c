#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "LCD1602.h"
#include "DS18B20.h"

unsigned char num;
unsigned char T,Temp;

void main()
{
	UART_Init();		//串口初始化
	LCD_Init();
	LCD_ShowString(1,1,"Bluetooth:");
	LCD_ShowString(2,4,"T=");
	while(1)
	{
		LCD_ShowHexNum(2,1,num,2);
		DS18B20_ConvertT();
		T=DS18B20_ReadT()/1;
		LCD_ShowNum(2,6,T,3);
		if(num==0x01)
		{
			P2_0=0;
		}
		else if(num==0x02)
		{
			P2_0=1;
		}
	}
}

void UART_Routine() interrupt 4
{
	if(RI)						//判断是否发送数据
	{
		num=SBUF;				//读取手机发送的数据
		UART_SendByte(SBUF);	//像手机发送收到的数据
		if(num==0x03)
		{
			Temp=T/10*16+T%10;	//使手机上显示出十进制
			UART_SendByte(Temp);
		}
		RI=0;					//接收标志位清0
	}
}
