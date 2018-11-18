#ifndef __show_12864_H__
#define __show_12864_H__

extern void show_12864_init();

extern void show_12864_com(bit mode,unsigned char dat);
extern void show_12864_xy(unsigned char x,unsigned char y);  
extern void show_12864_Write(unsigned char  x,unsigned char  y,unsigned char  date);
//extern void show_12864_char(char x) ;
//extern void show_12864_3int(unsigned int x) ;
//extern void show_12864_4int(unsigned int x) ;
//extern void show_12864_5int(unsigned int x) ;

//extern void show_12864_2float(   float x );	


extern void printf(unsigned char *uc);  



//void write_gram(unsigned char y,unsigned char x,unsigned int dat);
//void dot(unsigned char x,unsigned char y);
//void clr_gram();
//void line(unsigned char x1, unsigned char y1, unsigned char x2,unsigned char y2); 


#endif