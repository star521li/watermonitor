#include<reg52.h>
#include"global_define.h"
#include"NRF24L01.h"  
#include"Delay.h"

extern void InitLcd1602();
extern void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);

sbit LED = P1^6 ;
sbit key1 = P3^4 ;
sbit key2 = P3^5 ;
unsigned int baojingzhi = 200;//Ĭ��50cm
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
void keyscan()	//���ñ���ֵ����
{
	if(key1==0)	   // ����ֵ��
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
		NRFSetTxMode(baojing);  //����
	    while(CheckACK_RP());	//����Ƿ������,���Ӧ���ź�
		Delay_x_ms(200);	
		}
	}
	if(key2==0)	   // ����ֵ��
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
		NRFSetTxMode(baojing);  //����
	    while(CheckACK_RP());	//����Ƿ������,���Ӧ���ź�
		Delay_x_ms(200);
		}
	}

}
/*------------------------------------------------
                    ��ʱ����ʼ���ӳ���
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��		     
 TH0=(65536-1000)/256;		  //���¸�ֵ 1ms
 TL0=(65536-1000)%256;
 EA=1;            //���жϴ�
 ET0=1;           //��ʱ���жϴ�
 TR0=1;           //��ʱ�����ش�
 PT0=1;           //���ȼ���
}
void main()
{
   unsigned char buff[8];
   uint num=0 ;
      

   Init_Timer0();
   NRF24L01Int();     
   InitLcd1602();    //1602Һ����ʼ��
   LcdShowStr(0,0,"Level:");
   LcdShowStr(0,1,"Set:200");
   
   while(1)
    {  	 
	     Delay_x_ms(20);		 
	     NRFSetRXMode();//����Ϊ����ģʽ
		 Delay_x_ms(20);
		 GetDate();   //��ʼ��������
		 Delay_x_ms(20);
	     LcdShowStr(6,0,RevTempDate);	//��ʾ
		 bai = 	RevTempDate[0]-'0';		//��ȡ��λ
		 shi = 	RevTempDate[1]-'0';	    //��ȡʮλ
		 ge  = 	RevTempDate[2]-'0';		//��ȡ��λ
	 	 shuiwei = bai*100+shi*10+ge;		//����

		if(shuiwei<=baojingzhi)     //	������С�ڱ���ֵʱ����
		   LED = 0;  
		else 
		   LED = 1;

	 }
 		 

//		else num = 0;  
 	
}	
  /*------------------------------------------------
                 ��ʱ���ж��ӳ���
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{

 static unsigned int j;
 TH0=(65536-1000)/256;		  //���¸�ֵ 1ms
 TL0=(65536-1000)%256;
 keyscan();
 j++;
 if(j>=500)
 {
 j = 0;
 }
  
}
