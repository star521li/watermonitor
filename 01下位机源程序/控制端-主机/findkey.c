#include<reg52.h>
#include"delay.h"

#define port P0

char findkey ()
{
	unsigned char line,row,temp1,temp2 ;
 	unsigned char  key=0;
  	

  	temp1=0x01;                         //设置行检测，以便于后面取反后保证有一位为0
   	for( line=0 ; line<4 ; line++ )
		{
		port=0xf0;
		port=~temp1;					    //拉低第一行
		temp1<<=1;					    //逐行拉低
		if(  (port&0xf0)!= 0xf0  )        //****此时有键按下
	      	{
				Delay_x_ms(10);  
		   	  	if(  (port&0xf0)!= 0xf0  )  	 //按键消抖！！！！
	        	{
			    	temp2=0x10;
	            	for(row=0;row<4;row++)            //列检测
				    {
				    	if((port&temp2)==0x00)          //判断哪一列按下
						{
							key = 4*line + row ;							
 					 						  
					 	    while((port&0xf0)!=0xf0);	  //等待按键抬起
 						    
							return(key);
					 
						}
				    	temp2<<=1;
			    	}  
						
		 
		    	}  
			}
    	} 
 
  return(-1);
}
