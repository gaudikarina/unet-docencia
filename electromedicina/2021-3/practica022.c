#include <16f877.h>
#use delay(clock=4000000)
#use standard_io(A,B,D,E)
int A,BL,BH,DL,DH,i;
const int D[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};

void mostrardisplay(int H, int L ){
    output_D(0x00);    
    output_E(0x07);
    output_D(L);    
    output_E(0x06);
    delay_ms(3);
    output_D(0x00);    
    output_E(0x07);
    output_D(H);    
    output_E(0x05);
    delay_ms(3);   
   return;  
}
void main(){
      while(1){
      // Base Hexadecimal
      BL=input_A()&0x0f;
      BH=(input_A()>>4)&0x03;
      DL=D[BL];
      DH=D[BH];
      mostrardisplay (DH,DL); 
      }      
}
