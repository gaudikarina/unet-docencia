#include <16f877.h>
#use delay(clock=4000000)
#use standard_io(A)
int c=0;
void main(){
      setup_timer_0(RTCC_EXT_L_TO_H|RTCC_DIV_1);
      set_timer0(0);
      while(1){
      c=get_timer0();
      while(c==0){
      c=get_timer0();
      }
      switch(c)
      {
      case 1:
         output_high(PIN_A0);
         delay_us(1916);
         output_low(PIN_A0);
         delay_us(1916);
         break;
      case 2:
         output_high(PIN_A0);
         delay_us(1701);
         output_low(PIN_A0);
         delay_us(1701);
         break;
      case 3:
         output_high(PIN_A0);
         delay_us(1515);
         output_low(PIN_A0);
         delay_us(1515);
         break;
      case 4:
         output_high(PIN_A0);
         delay_us(1433);
         output_low(PIN_A0);
         delay_us(1433);
         break;
      case 5:
         output_high(PIN_A0);
         delay_us(1276);
         output_low(PIN_A0);
         delay_us(1276);
         break;
      case 6:
         output_high(PIN_A0);
         delay_us(1136);
         output_low(PIN_A0);
         delay_us(1136);
         break;
      case 7:
         output_high(PIN_A0);
         delay_us(1012);
         output_low(PIN_A0);
         delay_us(1012);
         break;
      default:
        set_timer0(0);
      }
     
   }
}
