#include<reg52.h>
sbit EN=P2^5;
sbit RS=P2^7;
sbit RW=P2^6;
sbit BUSY=P0^7;
  

#define dataport P0
//sbit PSB=P3^7;
//��ָͨ��ģʽ��0x30
//��չָ�0x36

unsigned int b=4;
void lcd_busy();



static void delayus(unsigned int x)
{
  while(x--);
}


void show_12864_com(bit mode,unsigned char dat)//-----------------���0����д���ݣ�1��
	{ 
	EA=0;
	   lcd_busy();
	   RS=mode;
	   RW=0;
	   EN=0;
	   dataport=dat;
	   delayus(5);
	   EN=1;
	   delayus(1);
	   EN=0;
	   //delay(40);
	EA=1;
	}
void show_12864_xy(unsigned char x,unsigned char y)//--------------λ��
    {
	 	switch (x)
	 	{
	       case 1:x=0x80;break;
		   case 2:x=0x90;break;
		   case 3:x=0x88;break;
		   case 4:x=0x98;break;
		}
	  show_12864_com(0,x+y);
	}



void show_12864_Write(unsigned char  x,unsigned char  y,unsigned char  date)	 //����д����
{
	show_12864_xy(x,y);
	show_12864_com(1,date);


}


 
void show_12864_Clear()				          	 //LCD���� 
{
  unsigned char x,y;
  for(x=0;x<8;x++)
   {
	 for(y=0;y<128;y++)
	  show_12864_Write(x,y,0x00);
   }
}






void show_12864_char(char x)                        //��ʾ2λ������
{ char a,b;
  a=x/10;b=x%10;
  show_12864_com(1,a+48);
  show_12864_com(1,b+48);
}


void show_12864_3int(unsigned int x)                 //��ʾ3λ������
{  char a,b,c;  
    a=x/100;
	b=x%100/10;
	c=x%10;
	show_12864_com(1,a+48);
	show_12864_com(1,b+48);
	show_12864_com(1,c+48);
}

void show_12864_4int(unsigned int x)                 //��ʾ4λ������
{  char a,b,c,d;  
    a=x/1000;
	b=x%1000/100;
	c=x%100/10;
	d=x%10;
	show_12864_com(1,a+48);
	show_12864_com(1,b+48);
	show_12864_com(1,c+48);
	show_12864_com(1,d+48);
}




void show_12864_5int(unsigned int x)                 //��ʾ5λ������
{
  char a,b,c,d,e;
  a=x/10000;
  b=x%10000/1000;
  c=x%1000/100;
  d=x%100/10;
  e=x%10;
  show_12864_com(1,a+48);
  show_12864_com(1,b+48);
  show_12864_com(1,c+48);
  show_12864_com(1,d+48);
  show_12864_com(1,e+48);
}



void show_12864_2float(   float x )                //��ʾ2λ��С��
{
  unsigned int   number;
  unsigned char	 a,b,c;
    number = x * 100;
    a=number/100;
	b=number%100/10;
	c=number%10;
	show_12864_com(1,a+48);
	show_12864_com(1,'.');
	show_12864_com(1,b+48);
	show_12864_com(1,c+48);
}



void show_12864_3float(   float x )                //��ʾ3λ��С��
{
  unsigned int   number;
  unsigned char	 a,b,c,d;
    number = x * 1000;
	a=number/1000;
	b=number%1000/100;
	c=number%1000%100/10;
	d=number%10;

	show_12864_com(1,a+48);
	show_12864_com(1,'.');
	show_12864_com(1,b+48);
	show_12864_com(1,c+48);
    show_12864_com(1,d+48);
}




void printf(unsigned char *uc)                      //��ӡһ���ַ�
{ 
  while(*uc!='\0')
  {
    show_12864_com(1,*uc);uc++;
  }
}



void show_12864_init()//-------------------------------------------��ʼ��
    {
	dataport =0XFF;
	show_12864_com(0,0x30);//��ָͨ��ģʽ
	show_12864_com(0,0x0c);//����ʾ	 0x0c��겻��ʾ 
	show_12864_com(0,0x06);//�������ģʽ
	show_12864_com(0,0x01);//����

//////// ///////////////�Լ�д��Ҫ��ʼ���ĺ��� /////////////

/*	show_12864_xy(1,0);
	printf("  ����Ŵ���");
    show_12864_xy(2,0);
	printf("��  ��:     dB");
	show_12864_xy(3,0);	
	printf("��Чֵ:     Vrms");
	show_12864_xy(4,0);	
	printf("AGC ״̬����");
*/
//////// ///////////////�Լ�д��Ҫ��ʼ���ĺ��� /////////////	
	}



//------------------------------------------------------------------------------------------------------
//																										|
//							��������ڻ�ͼ																			|
//------------------------------------------------------------------------------------------------------
void lcd_busy()      //���æ
{
   dataport=0xff;
   RS=0;
   RW=1;
   EN=1;
   while(BUSY==1);
   EN=0;
}
unsigned char rb()       //�����ֽ�
{  unsigned char tmp;
   lcd_busy();
   RS=1;
   RW=1;
   EN=1;
   delayus(1);tmp=dataport;
   EN=0;
   return tmp;
}
unsigned int r2b(unsigned char y,unsigned char x)     //���������ֽ�
{  //y:0-31   x:0-15
   unsigned int tmp;
   show_12864_com(0,0x34);
   show_12864_com(0,0x80+y);
   show_12864_com(0,0x80+x);
   show_12864_com(0,0x30);
   rb();
   tmp=rb();
   tmp=tmp<<8|rb();
   show_12864_com(0,0x36);
   return tmp;
}
void write_gram(unsigned char y,unsigned char x,unsigned int dat)//	uchar code *img  дͼ��RAM
{
   show_12864_com(0,0x34);
   show_12864_com(0,0x80+y);
   show_12864_com(0,0x80+x);
   show_12864_com(0,0x30);
   show_12864_com(1,(dat&0xff00)>>8);
   show_12864_com(1,dat&0x00ff);
   show_12864_com(0,0x36);
}
void dot(unsigned char x,unsigned char y)                        //���
{
   int tmp=0;
   unsigned char Vx,Vy;
   Vx=x/16;
   if(y>31){Vy=y-32;Vx=8+x/16;}
    else Vy=y; 
   tmp|=r2b(Vy,Vx);
   tmp|=1<<(15-(x%16)); 
   write_gram(Vy,Vx,tmp);
}
void line(unsigned char x1, unsigned char y1, unsigned char x2,unsigned char y2)      //����
{
  int x,y,i;
  float dx,dy;	
  dx=x2-x1;
  if(dx<0){dx=-dx;}
  dy=y2-y1;
  if(dy<0){dy=-dy;}
  if(dx>dy)
   {
	     if(x1<x2)
		   {
		     for(i=0;i<dx;i++)
			  {	dot(x1+i,y);
			    y=y1+(dy/dx)*i;
			  }
		   }
   }
   else 
   {	    
	     for(i=0;i<dy;i++)
		  {	dot(y1+i,x);
		    y=y1+(dx/dy)*i;
		  }		 
   }
}
void clr_gram()                                   //���RAM
{  int i,j;  
  for(j=0;j<32;j++)
    for(i=0;i<16;i++)
	{  show_12864_com(0,0x34);
	   show_12864_com(0,0x80+j);
	   show_12864_com(0,0x80+i);
	   show_12864_com(0,0x30);
	   show_12864_com(1,0x00);
	   show_12864_com(1,0x00);
	}
}

//------------------------------------------------------------------------------------------------------
//																										| 
//																										|
//------------------------------------------------------------------------------------------------------