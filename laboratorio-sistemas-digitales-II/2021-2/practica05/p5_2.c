#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device high_ints=true
#device adc=10
#use delay(clock=4000000)
#use standard_io(C)
#include <hdm64gs12gau.c>
#include <graphics.c>
float temp,pres;
int16 ad1,ad2;
char text[]="CCP MODO COMPARACION";
char t3[]="Ancho Pulso:";
char voltios[12];
char v1[12];
char v2[12];
char v3[12];
int var=0;
int32 i=0;
#INT_AD high
void ad_int(){
   ad1=read_adc();
   set_timer1(0);
   ccp_2=2500;
   i=i+1;
}


void main (){

   glcd_init(ON);
   disable_interrupts(global);
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   setup_ccp2(CCP_COMPARE_RESET_TIMER);
   setup_timer_1(T1_internal|T1_DIV_BY_1);
   set_timer1(0);
   ccp_2=2500;
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ad);
   while(1){
      glcd_text57(0,10,text, 1, 1);
     sprintf(v1,"ad1= %4Lu", ad1); 
     glcd_text57(5,20,v1, 1, 1);
      pres= ((ad1 /1024.0 )+0.095)/(0.009);  
      sprintf(v2,"P= %3.2f kPa",pres);
      glcd_text57(5,30,v2, 1, 1);   
       sprintf(v3,"int= %6Lu",i);
      glcd_text57(5,50,v3, 1, 1);      
   delay_ms(500);
   glcd_fillScreen(Off);
   }
}
