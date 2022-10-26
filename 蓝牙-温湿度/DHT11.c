#include <REGX51.H>
#include "PublicDelay.h"
#include "intrins.h"

#define DHT11_DQ P2_3

void DHT11_Rst(void)	  //复位DHT11 
{                 
	DHT11_DQ=1;
	Delay_10us(1);
	DHT11_DQ=0; 	  //拉低DQ
  Delay_ms(25);   //拉低至少18ms
  DHT11_DQ=1; 	  //DQ=1 
	Delay_10us(3);  //主机拉高20~40us
}

//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
unsigned char DHT11_Check(void) 	   
{   
	unsigned char Retry=0;
	
	while(!DHT11_DQ&&(Retry<100))//判断从机发出 80us 的低电平响应信号是否结束
	{
		Retry++;
		_nop_();
	}
	if(Retry>=100)
	{
		return 1;
	}
	else
	{
		Retry=0;
	}
  while(DHT11_DQ&&(Retry<100))//判断从机发出 80us 的高电平是否结束如结束则主机进入数据接收状态
	{
		Retry++;
		_nop_();
	} 
	if(Retry>=100)
	{
		return 1;	    	
	}
	return 0;
}

unsigned char DHT11_Init()
{
	DHT11_DQ=1;
	DHT11_Rst();	  
	return DHT11_Check();
}

//从DHT11读取一个字节
//返回值：读到的数据
unsigned char DHT11_Read_Byte(void)
{        
  unsigned char i,temp;
	unsigned char Data_Byte=0; 
	unsigned char Retry=0;
	for(i=0;i<8;i++)//接收8bit的数据 
 	{ 
//	while(!DHT11_DQ);//等待50us的低电平开始信号结束
		while (!DHT11_DQ&&Retry<50)//等待50us的低电平开始信号结束
		{
			Retry++;
			_nop_();
		}
		Retry=0;
		Delay_10us(3);//等待40us 
		temp=0;//时间为26us-28us表示接收的为数据'0' 
		if(DHT11_DQ==1)
		{
			temp=1; //如果26us-28us之后还为高电平则表示接收的数据为'1' 
		}
//	while(DHT11_DQ);//等待数据信号高电平'0'为26us-28us'1'为70us
		while (DHT11_DQ&&(Retry<100))//等待数据信号高电平'0'为26us-28us'1'为70us
		{
			Retry++;
			_nop_();
		}
		Data_Byte<<=1;//接收的数据为高位在前右移 
		Data_Byte|=temp; 
  }
  return Data_Byte;
}

//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
unsigned char DHT11_Read_Data(unsigned char *T,unsigned char *Humi)
{        
 	unsigned char Buf[5];
	unsigned char i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			Buf[i]=DHT11_Read_Byte();
		}
		if((Buf[0]+Buf[1]+Buf[2]+Buf[3])==Buf[4])
		{
			*Humi=Buf[0];
			*T=Buf[2];
		}
	}else return 1;
	return 0;	    
}
