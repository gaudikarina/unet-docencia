#include <16F877a.h>
#use delay (clock=4000000)
#use standard_io(C)
#include<lcd.c>



short pulso,cambio;
float AP;
long fs,fb;

#INT_ccp1
void serv_int(void){
  
      if (cambio==0){
         setup_ccp1(CCP_CAPTURE_FE);
    
    FS=CCP_1;
         cambio=1;
      }
      else{
         setup_ccp1(CCP_CAPTURE_RE);
    
      FB=CCP_1;
         cambio=0;
  
         if (pulso==0)
         {
         pulso=1;
  
      }
      }
}

void main (){
   pulso=0;
   cambio=0;
   lcd_init();
   setup_timer_1(T1_INTERNAL);
   setup_ccp1(CCP_CAPTURE_RE);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ccp1);

   while(1){
        if (pulso==1) {
         AP=(fb-fs)*1.0;
        printf(lcd_putc," \f Pulso= %6.1f uS",AP);
         delay_ms(100);
         pulso=0;
   }
   }
}
