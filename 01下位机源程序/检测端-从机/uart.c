#include<reg52.h>
#include"uart.h"
#include"delay.h"
 
sbit led = P1^5;


void uart_init()
{
	   TMOD=0x21;	 //��ʱ��1 8λ�Զ���װ,ʹ�ø�λ�Ĵ���
	   TH1=0xfd;		//�趨TI������� �����ֵ255��  �����趨����9600������
	   TL1=0xfd;   
	 //  PCON=0x80;		//���λ��SMOD ��SMOD=1 ʱ �����ʱ������ϵ�ʱΪ�㡣
	   SM0=0;SM1=1;    //8λ����  ����ģʽ1
	   SM2=0;          //��У��  
	   TR1=1;		   //������ʱ��1
	   REN=1;	       //�������
	   RI=0; 		   //�����жϱ�־λ
	   TI=0;		   //�����жϱ�־λ 
}




void uart( unsigned int t )
{ 
 

/*	SCON = 0x40;  //��ʽ1,���������
	PCON = 0x80;  //�����ʱ���

	TMOD = 0x20;  //��ʱ��1��ʽ2
//	TH1 = 256 - F_OSC / 16 / 12 / F_BAUD;//12MHz 
	TH1 = 0xfd ;   //9600
	TR1 = 1;//������ʱ��1
*/


  	 

		SBUF = t ;
		while(!TI);
	    TI = 0;//�����һ�εķ���
	  
	    
}
