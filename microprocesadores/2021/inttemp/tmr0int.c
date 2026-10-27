#include <16f84a.h>
#use delay(clock=4M)
#use standard_io(B)
#int_TIMER0
void srv_int(void){
         output_toggle(PIN_B0);
         set_timer0(6);         
}
void main(){
      setup_timer_0(RTCC_DIV_2|RTCC_INTERNAL);
      enable_interrupts(INT_TIMER0); 
      enable_interrupts(GLOBAL); 
      set_timer0(6);
      output_high(PIN_B0);
      while(1);    
}
