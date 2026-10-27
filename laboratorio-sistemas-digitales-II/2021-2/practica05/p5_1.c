#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device high_ints=true
#use delay(clock=4000000)
#use standard_io(C)
#include <hdm64gs12gau.c>
#include <graphics.c>
short pulso=0,cambio=0;
float AP=0.0;
int16 tf=0,fs=0,fb=0;
char text[]="CCP MODO CAPTURA";
char t3[]="Ancho Pulso:";
char voltios[12];
char v1[12];
char v2[12];
#INT_ccp1 high
void serv_int(void){
      if (cambio==0){
         fs=CCP_1;
        // set_timer1(0);
         setup_ccp1(CCP_CAPTURE_FE);
         cambio=1;
      }
      else{
         fb=CCP_1;
   //      set_timer1(0);
         setup_ccp1(CCP_CAPTURE_RE);         
         cambio=0;
         if (pulso==0)
         {
            pulso=1;
         }
      }
}

void main (){
  // pulso=0;
   cambio=0;
   glcd_init(ON);
   setup_timer_1(T1_internal|T1_DIV_BY_1);
   setup_ccp1(CCP_CAPTURE_RE);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ccp1);
    set_timer1(0);
   while(1){
      glcd_text57(10,10,text, 1, 1);
      glcd_text57(30,25,t3, 1, 1);
//!      sprintf(v1,"fs= %6Lu", fs);
//!      glcd_text57(1,0,v1, 1, 1);
//!      sprintf(v2,"fb= %6Lu", fb);      
//!      glcd_text57(1,10,v2, 1, 1);
      if (pulso==1) {
         tf=(fb-fs);
         AP=tf*1.0;
      //   sprintf(voltios,"%6Lu uS", tf); 
         sprintf(voltios,"%6.1f uS", AP); 
         glcd_text57(25,40,voltios, 1, 1);
         pulso=0;
         }           
   delay_ms(1500);
   glcd_fillScreen(Off);
   }
}
