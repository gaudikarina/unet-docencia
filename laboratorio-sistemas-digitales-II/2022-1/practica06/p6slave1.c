#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#use delay (clock=4000000)
#use i2c(slave,sda=PIN_B0,scl=PIN_B1,address=0x10)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#include <stdio.h>
#include<math.h>
#include <hdm64gs12gau.c>
#include <graphics.c>
int th,tl,hh,hl;
int16 t,h,lsb,msb,m;
float p1,p2;
#INT_SSP
void serv_int(void){
   int estado,d;
    estado=i2c_isr_state();
    if(estado==0)
      d=i2c_read();
    if((estado>0)&&(estado<0x80)){
      hl=i2c_read();
      hh=i2c_read();
      tl=i2c_read();
      th=i2c_read();  
      }
}
long transformar(int n1,int n2){
     msb=n1<<8;
     lsb=0x00FF&n2;
     m=msb|lsb;
     return(m);
}

void main() {
      enable_interrupts(int_ssp);
      enable_interrupts(GLOBAL);
   While (1) {
     t=transformar(th,tl);
     h=transformar(hh,hl);
     p1=(175.72*t/65536.0)-46.85;
     p2=(125.0*h/65536.0)-6.0;
     printf("\fT=%3.2f oC, H=%3.2f %%RH",p1,p2); 
     delay_ms(500);
   }
}
