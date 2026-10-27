#include <16f877.h>
#use delay(clock=4000000)
#use standard_io(A,B)
int B,i;
const int D[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
void main(){
      while(1){
      for(i=10;i>=1;i--){
         B=D[i-1];
         output_B(B);
         delay_ms(300);
         }
      for(i=1;i<=5;i++)
      {
         B=0x40;
         output_B(B);
         delay_ms(300);
         B=0X00;
         output_B(B);
         delay_ms(300);
      }
      }      
}
