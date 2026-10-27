#include <18f4550.h>
#fuses HSPLL,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#device adc=10
#use delay(clock=48000000)
#use i2c(Master,sda=PIN_B0,scl=PIN_B1)
#include <stdio.h>
#include<math.h>
#include <hdm64gs12gau.c>
#include <graphics.c>
char t1[]="Zona 01";
char t2[]="Zona 02";
char t3[]="T=";
char t4[]="oC";
char it[6];
char voltios[6];
char voltios2[6];
char text[]="Sala de Control";
float zonaT(int slvaddress){
          int16 TL,TH,T;
          int q, q1;
          float p;
          i2c_start();
          i2c_write(slvaddress);
          i2c_write(1);
          i2c_stop();
          i2c_start();                 //Inicializa la transmisión
          i2c_write(slvaddress|1);
          q=i2c_read(0);
          i2c_start();
          i2c_write(slvaddress);
          i2c_write(2);
          i2c_start();                 //Inicializa la transmisión
          i2c_write(slvaddress|1);
          q1=i2c_read(0);
          i2c_stop();
          TH=q1<<8;
          TL=0x00FF&q;
          T=TH|TL;
          p = 5.0 * T/(1024.0*0.010);
          return(p);
}


void main() {

   float p1,p2;

   glcd_init(ON);
   While (1) {
//!         sprintf(it,"%LX", T); 
//!         glcd_text57(35,20,it, 1, 1);
//!         sprintf(voltios,"%X", q1); 
//!         glcd_text57(35,30,voltios, 1, 1);
          glcd_text57(15,5,text, 1, 1);
          glcd_text57(1,25,t1, 1, 1);
          glcd_text57(60,25,t3, 1, 1);
          sprintf(voltios,"%2.1f", p1); 
          glcd_text57(75,25,voltios, 1, 1);
          glcd_text57(110,25,t4, 1, 1);
          glcd_text57(1,45,t2, 1, 1);
          glcd_text57(60,45,t3, 1, 1);
          sprintf(voltios2,"%2.1f", p2); 
          glcd_text57(75,45,voltios2, 1, 1);
          glcd_text57(110,45,t4, 1, 1);
          
          delay_ms(500);
          p1=zonaT(0x10);
          p2=zonaT(0x20);         

 //         T=th;
//!          T=((q1<<8)&0xFF00)|q;
//!         i2c_start();                 //Inicializa la transmisión
//!         i2c_write(0x21);
//!         q1=i2c_read(0);
//!         i2c_stop();
        glcd_fillScreen(Off);
    
    
         
//!      glcd_text57(20,0,text, 2, 1);
//!      glcd_text57(20,20,t3, 1, 1);
//!      sprintf(voltios,"%2.1f", p); 
//!      glcd_text57(35,20,voltios, 1, 1);
//!      glcd_text57(75,20,t4, 1, 1);
//!      TH = q >> 8;
//!      TL = q & 0xFF;                
    
 //     i2c_write(TL);
//!      i2c_write(TH);
      
 //     delay_ms(1000);
         
      }
}
