#include <16f877.h>
#use delay(clock=4000000)
#use standard_io(A,C)
int A=99,BL,BH,D,U;
const int D1[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};

void mostrardisplay(int H, int L ){
    output_C(0x00);    
    output_A(0x07);
    output_C(L);    
    output_A(0x06);
    delay_ms(3);
    output_C(0x00);    
    output_A(0x07);
    output_C(H);    
    output_A(0x05);
    delay_ms(3);   
   return;  
}
void bcd7seg(){
  int m,dec,uni;
       m=A%100;
       dec=A/10;
       uni=A%10;
       D=D1[dec];
       U=D1[uni];
}
void main(){
      while(1){
      bcd7seg();
      mostrardisplay(D,U); 
      delay_ms(100); 
      A--;
      if (A==255)
        A=99;
      }      
}
