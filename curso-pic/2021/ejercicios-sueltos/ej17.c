#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(C,D)
#include <lcd.c>

short pulso,cambio;
float AP;
long fs,fb;

#INT_ccp2
void serv_int(void){
      printf(lcd_putc," entro");
      if (cambio==0){
          printf(lcd_putc," PULSO 0");
         setup_ccp1(CCP_CAPTURE_FE);
         FS=CCP_1;
         cambio=1;
      }
      else{
         
         setup_ccp1(CCP_CAPTURE_RE);
         FB=CCP_1;
         cambio=0;
      printf(lcd_putc," CAMBIO 1");
         delay_ms(200);   
         if (pulso==0) 
         {
         pulso=1;
      printf(lcd_putc," PULSO 0");
      delay_ms(200);
      }
      }
}

void main (){
   pulso=0;
   cambio=0;
   lcd_init();
   set_tris_C(0xff);
   printf(lcd_putc," inicio");
   setup_timer_1(T1_INTERNAL);
   setup_ccp2(CCP_CAPTURE_RE);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ccp2);

   while(1){
        if (pulso==1) {
         AP=(fb-fs)*1.0;
         printf(lcd_putc," Pulso= %6.1f uS",AP);
         delay_ms(100);
         pulso=0;
   }
   }
}
