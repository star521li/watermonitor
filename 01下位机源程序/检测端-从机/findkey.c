#include<reg52.h>
#include"delay.h"

#define port P0

char findkey ()
{
	unsigned char line,row,temp1,temp2 ;
 	unsigned char  key=0;
  	

  	temp1=0x01;                         //�����м�⣬�Ա��ں���ȡ����֤��һλΪ0
   	for( line=0 ; line<4 ; line++ )
		{
		port=0xf0;
		port=~temp1;					    //���͵�һ��
		temp1<<=1;					    //��������
		if(  (port&0xf0)!= 0xf0  )        //****��ʱ�м�����
	      	{
				Delay_x_ms(10);  
		   	  	if(  (port&0xf0)!= 0xf0  )  	 //����������������
	        	{
			    	temp2=0x10;
	            	for(row=0;row<4;row++)            //�м��
				    {
				    	if((port&temp2)==0x00)          //�ж���һ�а���
						{
							key = 4*line + row ;							
 					 						  
					 	    while((port&0xf0)!=0xf0);	  //�ȴ�����̧��
 						    
							return(key);
					 
						}
				    	temp2<<=1;
			    	}  
						
		 
		    	}  
			}
    	} 
 
  return(-1);
}
