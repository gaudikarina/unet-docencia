#include <16f84a.h>
#use delay(clock=4000000)
#use standard_io(A,B)
int c,m,U,D;
const int D1[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
void mostrardisplay(void){
    output_B(0x00);    
    output_A(0x07);
    output_B(U);    
    output_A(0x06);
    delay_ms(3);
    output_B(0x00);    
    output_A(0x07);
    output_B(D);    
    output_A(0x05);
    delay_ms(3);   
   return;  
}
void binabcd7s(int R1){
       int a,cn,dc,un;
       cn=R1/100;
       a=R1%100;
       dc=a/10;
       un=a%10;
       D=D1[dc];
       U=D1[un];
}
void main(){
      setup_timer_0(RTCC_EXT_L_TO_H|RTCC_DIV_1);
      set_timer0(0);
      while(1){
      c=get_timer0();
      m=c*2;
      if(m==100)
         set_timer0(0);
      binabcd7s(m);
      mostrardisplay();       
      
   }      
}
