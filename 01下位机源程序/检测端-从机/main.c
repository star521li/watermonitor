#include<reg52.h>
#include"global_define.h"
#include"NRF24L01.h"  
#include"Delay.h"

sbit LED = P2^0 ;
sbit DJ = P2^6 ;

unsigned int baojingzhi = 200;//Ĭ��50cm
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
  
/*������Ϊ9600*/  
void UART_init(void)  
{  
    SCON = 0x50;        //���ڷ�ʽ1  
  
    TMOD = 0x20;        // ��ʱ��ʹ�÷�ʽ2�Զ�����  
    TH1 = 0xFD;    //9600�����ʶ�Ӧ��Ԥ��������ʱ����ʽ2�£�TH1=TL1  
    TL1 = 0xFD;  
  
    TR1 = 1;//������ʱ������ʼ����������  
}  
  
/*����һ���ַ�*/  
void UART_send_byte(unsigned char dat)  
{  
    SBUF = dat;       //�����ݷŵ�SBUF��  
    while (TI == 0);//δ������Ͼ͵ȴ�  
    TI = 0;    //������Ϻ�Ҫ��TI������0  
}  
  
/*����һ���ַ���*/  
void UART_send_string(unsigned char *buf)  
{  
    while (*buf != '\0')  
    {  
        UART_send_byte(*buf++);  
    }  
}  
 ////////////////// 

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
long ad()//�������������źź���
{  
     unsigned char i;
     //data1=0;
     bADcs = 0;//��ADC0832δ����ʱ��CS�����ӦΪ�ߵ�ƽ����ʱоƬ����.
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
		 if(Value_1<baojingzhi)     //	������С�ڱ���ֵʱ����
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
	     NRFSetRXMode();//����Ϊ����ģʽ
		 Delay_x_ms(20);
		 GetDate();   //��ʼ��������
		 Delay_x_ms(20);
		 bai = 	RevTempDate[0]-'0';		//��ȡ��λ
		 shi = 	RevTempDate[1]-'0';	    //��ȡʮλ
		 ge  = 	RevTempDate[2]-'0';		//��ȡ��λ
	 	 baojingzhi = bai*100+shi*10+ge;		//����
		
	


		   if(flag_1s==1)	  //һ�뷢��һ��ˮλֵ
		   {
		   	 flag_1s = 0;
			 Value_buff[0]=Value/100+'0';
	         Value_buff[1]=Value/10%10+'0';
	         Value_buff[2]=Value%10+'0';
			 Value_buff[3]=	'\0';
			 NRFSetTxMode(Value_buff);  //����
	         while(CheckACK_RP());	//����Ƿ������,���Ӧ���ź�
		     Delay_x_ms(200);	
		   }




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

 j++;
 if(j>=500)
 {
 j = 0;
 LED =!LED;
 flag_1s = 1;
 }
  
}

