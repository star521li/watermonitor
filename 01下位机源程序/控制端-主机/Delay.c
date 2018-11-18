
/***************************延时函数****************/
void Delay(unsigned int t)
{
  unsigned char x,y;
  for(x=t;x>0;x--)
   for(y=110;y>0;y--);
}

/**********************************************
   DS18B20专用延时子函数
**********************************************/
void DDelay(unsigned int t) 
{ 
	unsigned char n;
	n=0; 
	while(n<t) 
	{
	  n++;
	} 
}



void Delay_x_ms(unsigned int x)
{
     unsigned char i,j ;
   while(x--)
{
   for(i=22;i>0;i--)
    for(j=10;j>0;j--);
}

}

