#include <INTRINS.H>

void Delay(unsigned int ms)		//@11.0592MHz
{
	unsigned char i,j,k;
	for(k=0;k<ms;k++)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}