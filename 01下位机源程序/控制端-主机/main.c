#include<reg52.h>
#include"global_define.h"
#include"NRF24L01.h"  
#include"Delay.h"

extern void InitLcd1602();
extern void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);

sbit LED = P1^6 ;
sbit key1 = P3^4 ;
sbit key2 = P3^5 ;
unsigned int baojingzhi = 200;//默认50cm
unsigned char baojing[8];
unsigned char ge,shi,bai;
unsigned int shuiwei ;
idata unsigned char TxDate[TX_DATA_WITDH]={0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,11,12};


void DelayMs(uint time)
{
	uint i,j;
	for(i=time;i>0;i--)
		for(j=112;j>0;j--);
}
void keyscan()	//设置报警值函数
{
	if(key1==0)	   // 报警值加
	{
	    DelayMs(5);
		if(key1==0)
		{
		while(!key1);
		baojingzhi++;
		if(baojingzhi>=500) baojingzhi = 0;
		baojing[0]=baojingzhi/100+'0';
	    baojing[1]=baojingzhi/10%10+'0';
	    baojing[2]=baojingzhi%10+'0';
	    baojing[3]='\0';

		LcdShowStr(4,1,baojing);
		NRFSetTxMode(baojing);  //发送
	    while(CheckACK_RP());	//检测是否发送完毕,检测应答信号
		Delay_x_ms(200);	
		}
	}
	if(key2==0)	   // 报警值减
	{
	    DelayMs(5);
		if(key2==0)
		{
		while(!key2);
		baojingzhi--;
		if(baojingzhi<=0) baojingzhi = 0;
		baojing[0]=baojingzhi/100+'0';
	    baojing[1]=baojingzhi/10%10+'0';
	    baojing[2]=baojingzhi%10+'0';
	    baojing[3]='\0';

		LcdShowStr(4,1,baojing);
		NRFSetTxMode(baojing);  //发送
	    while(CheckACK_RP());	//检测是否发送完毕,检测应答信号
		Delay_x_ms(200);
		}
	}

}
/*------------------------------------------------
                    定时器初始化子程序
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响		     
 TH0=(65536-1000)/256;		  //重新赋值 1ms
 TL0=(65536-1000)%256;
 EA=1;            //总中断打开
 ET0=1;           //定时器中断打开
 TR0=1;           //定时器开关打开
 PT0=1;           //优先级打开
}
void main()
{
   unsigned char buff[8];
   uint num=0 ;
      

   Init_Timer0();
   NRF24L01Int();     
   InitLcd1602();    //1602液晶初始化
   LcdShowStr(0,0,"Level:");
   LcdShowStr(0,1,"Set:200");
   
   while(1)
    {  	 
	     Delay_x_ms(20);		 
	     NRFSetRXMode();//设置为接收模式
		 Delay_x_ms(20);
		 GetDate();   //开始接收数据
		 Delay_x_ms(20);
	     LcdShowStr(6,0,RevTempDate);	//显示
		 bai = 	RevTempDate[0]-'0';		//提取百位
		 shi = 	RevTempDate[1]-'0';	    //提取十位
		 ge  = 	RevTempDate[2]-'0';		//提取个位
	 	 shuiwei = bai*100+shi*10+ge;		//计算

		if(shuiwei<=baojingzhi)     //	当距离小于报警值时报警
		   LED = 0;  
		else 
		   LED = 1;

	 }
 		 

//		else num = 0;  
 	
}	
  /*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{

 static unsigned int j;
 TH0=(65536-1000)/256;		  //重新赋值 1ms
 TL0=(65536-1000)%256;
 keyscan();
 j++;
 if(j>=500)
 {
 j = 0;
 }
  
}
