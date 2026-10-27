#include<16f877.h>
#use delay(clock=4M)
#use standard_io(B)
int b0;
#INT_EXT
void servint(void){
   output_toggle(PIN_B1);
}
void main(){
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
   ext_int_edge( L_TO_H );
   port_b_pullups(1);
   output_low(PIN_B1);
   while(1);
}
