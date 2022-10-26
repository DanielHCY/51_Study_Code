#include <REGX52.H>
#include "Delay.h"
#include "UART.h"
#include "LCD1602.h"
#include "DHT11.h"
#include "PublicDelay.h"

unsigned char num;
unsigned char T,Temp,Humi;

void main()				//DHT11:S接P2_3,GEN接P2_2
{
	UART_Init();		//串口初始化
	LCD_Init();
	P2_2=0;
	while(DHT11_Init())
	{
		LCD_ShowString(1,1,"Error!");
	}
	LCD_ShowString(1,1,"Bluetooth:");
	LCD_ShowString(2,1,"T=   C");
	LCD_ShowChar(2,5,0xDF);		//显示摄氏度符号
	LCD_ShowString(2,8,"H=  %");
	while(1)
	{
		LCD_ShowHexNum(1,11,num,2);
		DHT11_Read_Data(&T,&Humi);
		LCD_ShowNum(2,3,T,2);
		LCD_ShowNum(2,10,Humi,2);
		if(num==0x01)
		{
			P2_0=0;
		}
		else if(num==0x02)
		{
			P2_0=1;
		}
		Delay_ms(1);
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
		if(num==0x04)
		{
			Temp=Humi/10*16+Humi%10;	//使手机上显示出十进制
			UART_SendByte(Temp);
		}
		RI=0;					//接收标志位清0
	}
}
