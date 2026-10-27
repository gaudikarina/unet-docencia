#include <16f877.h>
#device adc=10
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,bits=8)
int16 c=0;
void main(){
   while(1){
   printf("\fContador Ascendente:%3ld",c);
   delay_ms(200);
   c++;
   if (c==501)
      c=0;
   }
}
