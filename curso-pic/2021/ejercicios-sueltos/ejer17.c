#include <16F877.h>
#use delay(clock=4000000)
#include <lcd.c>


short p,c;
float AP;
long fs,fb;

#INT_CCP1
   serv_int(){
   printf(lcd_putc,"entro");
   }
   
void main(){
   p=0;
   c=0;
   lcd_init();
   setup_ccp1(CCP_CAPTURE_FE);
   setup_timer_1(T1_INTERNAL);
   enable_interrupts(global);
   enable_interrupts(int_ccp1);
   while(1);
}

