#include<reg52.h>
#include"global_define.h"
#include"NRF24L01.h"  
#include"Delay.h"

sbit LED = P2^0 ;
sbit DJ = P2^6 ;

unsigned int baojingzhi = 200;//默认50cm
unsigned char baojing[8];
unsigned char ge,shi,bai;
unsigned int shuiwei ;
idata unsigned char TxDate[TX_DATA_WITDH]={0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,11,12};

sbit bADcs=P2^5;
sbit bADcl=P2^4;
sbit bADda=P2^3;
unsigned char data1;
unsigned char flag_1s;
long	Value;
unsigned char Value_buff[8];
///////////
//typedef unsigned char uint8;  
//unsigned int   uint16;  
  
unsigned char Value_buff2[8];  
  
/*void delay(uint16 n)  
{  
    while (n--);  
}  */
  
/*波特率为9600*/  
void UART_init(void)  
{  
    SCON = 0x50;        //串口方式1  
  
    TMOD = 0x20;        // 定时器使用方式2自动重载  
    TH1 = 0xFD;    //9600波特率对应的预设数，定时器方式2下，TH1=TL1  
    TL1 = 0xFD;  
  
    TR1 = 1;//开启定时器，开始产生波特率  
}  
  
/*发送一个字符*/  
void UART_send_byte(unsigned char dat)  
{  
    SBUF = dat;       //把数据放到SBUF中  
    while (TI == 0);//未发送完毕就等待  
    TI = 0;    //发送完毕后，要把TI重新置0  
}  
  
/*发送一个字符串*/  
void UART_send_string(unsigned char *buf)  
{  
    while (*buf != '\0')  
    {  
        UART_send_byte(*buf++);  
    }  
}  
 ////////////////// 

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
long ad()//采样传感器的信号函数
{  
     unsigned char i;
     //data1=0;
     bADcs = 0;//当ADC0832未工作时其CS输入端应为高电平，此时芯片禁用.
	 bADcl=0;
	 bADda=1;
	 bADcl=1;
	 bADcl=0;//i down
	 bADda=1;
	 bADcl=1;
	 bADcl=0;	//   2 down
	 bADda=0;
	 bADcl=1;
	 bADcl=0;	//   3 down
	 bADda=1;
	 bADcl=1;
	 bADcl=0;	//   4 down

	 for(i=8;i>0;i--)
	 	{
		
	 	data1<<=1;
	 	bADcl=0;
		bADcl=1;
		if(bADda==1) data1|=0x01;
		   	bADda=1;
	 	}
		 bADcs=1;
	 	
       Value=data1*1.0/256*500;
	   
	  // Value=Value*K_MG_MV;
	  // Value=Value-5;
	   if(Value<0)Value=0;
	   return Value;
}
void DelayMs(uint time)
{
	uint i,j;
	for(i=time;i>0;i--)
		for(j=112;j>0;j--);
}
 
 
void main()
{
//   unsigned char buff[8];
   uint num=0 ;
    unsigned int Value_1;    
    DJ = 1;
   Init_Timer0();
   NRF24L01Int();     
   RevTempDate[0] = '2';
   RevTempDate[1] = '0';
   RevTempDate[2] = '0';
   //////
   UART_init(); 

   while(1)
    {  	
		 ad();
		 Value_1 = Value;
		 if(Value_1<baojingzhi)     //	当距离小于报警值时报警
		   DJ = 0 ;  
		 else 
		   DJ = 1;

		/////
		Value_buff2[0]=Value/100+'0';
	    Value_buff2[1]=Value/10%10+'0';
	    Value_buff2[2]=Value%10+'0';
		Value_buff2[3]=	'\0';
		UART_send_string(Value_buff2);  
        //delay(20000);  
		/////
	     NRFSetRXMode();//设置为接收模式
		 Delay_x_ms(20);
		 GetDate();   //开始接收数据
		 Delay_x_ms(20);
		 bai = 	RevTempDate[0]-'0';		//提取百位
		 shi = 	RevTempDate[1]-'0';	    //提取十位
		 ge  = 	RevTempDate[2]-'0';		//提取个位
	 	 baojingzhi = bai*100+shi*10+ge;		//计算
		
	


		   if(flag_1s==1)	  //一秒发送一次水位值
		   {
		   	 flag_1s = 0;
			 Value_buff[0]=Value/100+'0';
	         Value_buff[1]=Value/10%10+'0';
	         Value_buff[2]=Value%10+'0';
			 Value_buff[3]=	'\0';
			 NRFSetTxMode(Value_buff);  //发送
	         while(CheckACK_RP());	//检测是否发送完毕,检测应答信号
		     Delay_x_ms(200);	
		   }




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

 j++;
 if(j>=500)
 {
 j = 0;
 LED =!LED;
 flag_1s = 1;
 }
  
}

