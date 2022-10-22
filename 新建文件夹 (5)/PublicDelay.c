
void Delay_10us(int ten_us)
{
	while(ten_us--);
}

void Delay_ms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}
