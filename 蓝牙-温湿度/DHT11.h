#ifndef __DHT11_H__
#define __DHT11_H__

void DHT11_Rst(void);
unsigned char DHT11_Check(void);
unsigned char DHT11_Init();
unsigned char DHT11_Read_Byte(void);
unsigned char DHT11_Read_Data(unsigned char *T,unsigned char *Humi);

#endif