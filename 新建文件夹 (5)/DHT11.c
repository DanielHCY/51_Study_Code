#include <REGX51.H>
#include "PublicDelay.h"
#include "intrins.h"

#define DHT11_DQ P2_3

void DHT11_Rst(void)	  //��λDHT11 
{                 
	DHT11_DQ=1;
	Delay_10us(1);
	DHT11_DQ=0; 	  //����DQ
  Delay_ms(25);   //��������18ms
  DHT11_DQ=1; 	  //DQ=1 
	Delay_10us(3);  //��������20~40us
}

//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
unsigned char DHT11_Check(void) 	   
{   
	unsigned char Retry=0;
	
	while(!DHT11_DQ&&(Retry<100))//�жϴӻ����� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����
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
  while(DHT11_DQ&&(Retry<100))//�жϴӻ����� 80us �ĸߵ�ƽ�Ƿ������������������������ݽ���״̬
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

//��DHT11��ȡһ���ֽ�
//����ֵ������������
unsigned char DHT11_Read_Byte(void)
{        
  unsigned char i,temp;
	unsigned char Data_Byte=0; 
	unsigned char Retry=0;
	for(i=0;i<8;i++)//����8bit������ 
 	{ 
//	while(!DHT11_DQ);//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ���
		while (!DHT11_DQ&&Retry<50)//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ���
		{
			Retry++;
			_nop_();
		}
		Retry=0;
		Delay_10us(3);//�ȴ�40us 
		temp=0;//ʱ��Ϊ26us-28us����ʾ���յ�Ϊ����'0' 
		if(DHT11_DQ==1)
		{
			temp=1; //���26us-28us֮�󪣻�Ϊ�ߵ�ƽ�����ʾ���յ�����Ϊ'1' 
		}
//	while(DHT11_DQ);//�ȴ������źŸߵ�ƽ��'0'Ϊ26us-28us��'1'Ϊ70us
		while (DHT11_DQ&&(Retry<100))//�ȴ������źŸߵ�ƽ��'0'Ϊ26us-28us��'1'Ϊ70us
		{
			Retry++;
			_nop_();
		}
		Data_Byte<<=1;//���յ�����Ϊ��λ��ǰ�����ƪ� 
		Data_Byte|=temp; 
  }
  return Data_Byte;
}

//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
unsigned char DHT11_Read_Data(unsigned char *T,unsigned char *Humi)
{        
 	unsigned char Buf[5];
	unsigned char i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
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
