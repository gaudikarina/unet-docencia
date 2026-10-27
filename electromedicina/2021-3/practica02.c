#include <16f84a.h>
#use delay(clock=4000000)
#use standard_io(A,B)
int A,B;
const int D[6]={0x00,0x77,0x79,0x19,0x3F,0x3E};
void main(){
      while(1){
      B=input_A()&0x0f;
      if (B<6 && B>0){
         B=D[B];
         output_B(B);
      }
      else{
         output_B(0X7F);    
         delay_ms(500);
         output_B(0); 
         delay_ms(500);}
    }
}
