#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B)


#INT_TIMER0
void serv_int(void){
      output_toggle(PIN_B0);
      set_timer0(25);
   }


void main (){
   output_low(pin_B0);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_timer0);
   set_timer0(25);
   while(1);
}
