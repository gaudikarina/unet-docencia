#include<16F84a.h>
#use delay (clock=4000000)
#use standard_io(A,B)
void main(){
int A,B;
while(1){
   A=input_A();
   output_B(A);   
   }
}
