#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(E,B)

int E,B,i;

void main()
{
   while (1){
   E=input_E();
   E&=3; //011
   switch(E){
   case 0:
   output_B(255);
   delay_ms(500);
   output_B(0);
   delay_ms(500);
   break;
   case 1:
   output_B(0x55);
   delay_ms(500);
   output_B(0xAA);
   delay_ms(500);
   break;
   case 2:
   B=1;
   for(i=0;i<=7;i++){
      output_B(B);
      delay_ms(500);
      B<<=1;
   }
   case 3:
   B=128;
   for(i=0;i<=7;i++){
      output_B(B);
      delay_ms(500);
      B>>=1;
   }
 
   }
   
   }
}
