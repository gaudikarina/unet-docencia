#include <18f4550.h>
#fuses HSPLL,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#device adc=10
#use delay(clock=48000000)
#use i2c(slave,sda=PIN_B0,scl=PIN_B1,address=0x10)
#include <stdio.h>
#include<math.h>
#include <hdm64gs12gau.c>
#include <graphics.c>
char text[]="Zona 01";
char t3[]="T=";
char t4[]="oC";
char it[6];
char TL[6];
char voltios[6];
int estado,dato1,dato2; 
int16 q=0;
float p=0;
#INT_SSP
void serv_int(void){
   int bandera,b,d;
    estado=i2c_isr_state();
     if(estado==0)
   {
      d=i2c_read();
   }
    if((estado>0)&&(estado<0x80))
      bandera=i2c_read();
      b=bandera;
    if(estado==0x80){
     switch(b)
      {
         Case 1:
            i2c_write(dato1);
            break;
         Case 2:
            i2c_write(dato2);
            break;
      }
   
     }
}
void main() {  
      enable_interrupts(int_ssp);
      enable_interrupts(GLOBAL);
      setup_adc_ports(AN0|VSS_VDD);
      setup_adc(ADC_CLOCK_INTERNAL);
      set_adc_channel(0);
      glcd_init(ON);
   While (1) {
    q = read_adc(); 
    p = 5.0 * q /(1024.0*0.010);
    dato1=0x00ff&q;
    dato2=q>>8;
    glcd_text57(30,10,text, 1, 1);
    glcd_text57(20,20,t3, 1, 1);
    sprintf(voltios,"%2.1f", p); 
    glcd_text57(35,20,voltios, 1, 1);
    glcd_text57(65,20,t4, 1, 1);
    sprintf(it,"%LX", q); 
    glcd_text57(35,30,it, 1, 1);
    sprintf(TL,"%X", dato2); 
    glcd_text57(35,40,TL, 1, 1);
    delay_ms(500);
    glcd_fillScreen(Off);      
   }
}
