#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#use delay (clock=4000000)
#use i2c(Master,sda=PIN_B0,scl=PIN_B1)
#include <stdio.h>
#include<math.h>
#include <hdm64gs12gau.c>
#include <graphics.c>
char t1[]="SALA 01";
char t3[]="T=";
char t4[]="oC";
char t5[]="H=";
char t6[]="%RH";
char tem[6];
char hum[6];
int th,tl;
int ttl,tth,hl,hh;  
long  t,h;
long leersensor(int d1){
          int c;
          long msb,lsb,m;
          i2c_start();
          i2c_write(0x80);
          i2c_write(d1);
          i2c_start();
          i2c_write(0x81);
          delay_ms(100);
          th=i2c_read();  
          tl=i2c_read(0);  
          c=i2c_read(0);  
          i2c_stop();
          msb=th<<8;
          lsb=0x00FF&tl;
          m=msb|lsb;
          return(m);
          
}
void reset(){
          i2c_start();
          i2c_write(0x80);
          i2c_write(0xfe);
          i2c_stop();
}
void enviarpic(){
          hl=h&0x00ff;
          hh=(h>>8);
          ttl=t&0x00ff;
          tth=(t>>8);
          i2c_start();
          i2c_write(0x10);
          i2c_write(hl);
          i2c_start();          
          i2c_write(hh);
          i2c_start();
          i2c_write(ttl);
          i2c_start();
          i2c_write(tth);
          i2c_stop();
}
void main() {
   float p1,p2;
    
   glcd_init(ON);
   While (1) {
          h=leersensor(0xe5);
          reset();
          t=leersensor(0xe3);
          reset();
          enviarpic();
          p1=(175.72*t/65536.0)-46.85;
          p2=(125.0*h/65536.0)-6.0;
          glcd_text57(25,5,t1, 1, 1);
          glcd_text57(1,25,t3, 1, 1);
          glcd_text57(75,25,t4, 1, 1);
          sprintf(tem,"%3.2f",p1); 
          glcd_text57(30,25,tem, 1, 1);
          glcd_text57(1,45,t5, 1, 1);
          glcd_text57(75,45,t6, 1, 1);
          sprintf(hum,"%3.2f", p2); 
          glcd_text57(30,45,hum, 1, 1);          
          delay_ms(500);   
          glcd_fillScreen(Off);         
      }
}
