#include <16F877.h>
#use delay(clock=4000000)
#use standard_io(C)

void main() {
   setup_timer_2(T2_DIV_BY_1,249,1);
   set_pwm1_duty(500);
   setup_ccp1(CCP_PWM); 
   while(1){       
      }
   }
      

