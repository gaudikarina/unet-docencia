#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B)

short i;

#INT_ccp1
void serv_int(void){
      if (++i==1)
         setup_ccp1(CCP_COMPARE_CLR_ON_MATCH);
      else
         setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
      CCP_1=200;
      set_timer1(0);
      }

void main (){
   i=0;
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
   setup_ccp1(CCP_COMPARE_SET_ON_MATCH);
   CCP_1=200;
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ccp1);
   while(1);
}
