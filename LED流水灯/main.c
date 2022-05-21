#include <REGX52.H>
#include "Delay.h"

void main()
{
	while(1)
	{
		unsigned char i,j;
		for(i=0;i<8;i++)
		{
			P2=~(0x01<<i);
			Delay(500);
			if(i==7)
			{
				for(j=0;j<7;j++)
				{
					P2=~(0x40>>j);
					Delay(500);
				}
			}
		}
	}
}