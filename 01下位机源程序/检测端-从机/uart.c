#include<reg52.h>
#include"uart.h"
#include"delay.h"
 
sbit led = P1^5;


void uart_init()
{
	   TMOD=0x21;	 //定时器1 8位自动重装,使用高位寄存器
	   TH1=0xfd;		//设定TI的溢出率 （最大值255）  现在设定的是9600波特率
	   TL1=0xfd;   
	 //  PCON=0x80;		//最高位是SMOD 当SMOD=1 时 波特率倍增，上电时为零。
	   SM0=0;SM1=1;    //8位数据  工作模式1
	   SM2=0;          //无校验  
	   TR1=1;		   //开启定时器1
	   REN=1;	       //允许接收
	   RI=0; 		   //接受中断标志位
	   TI=0;		   //发送中断标志位 
}




void uart( unsigned int t )
{ 
 

/*	SCON = 0x40;  //方式1,不允许接收
	PCON = 0x80;  //波特率倍速

	TMOD = 0x20;  //定时器1方式2
//	TH1 = 256 - F_OSC / 16 / 12 / F_BAUD;//12MHz 
	TH1 = 0xfd ;   //9600
	TR1 = 1;//启动定时器1
*/


  	 

		SBUF = t ;
		while(!TI);
	    TI = 0;//完成上一次的发送
	  
	    
}
