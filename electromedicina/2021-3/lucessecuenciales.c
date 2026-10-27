#include <16f84a.h>
#use delay(clock=4000000)
#byte PORTA=0X05
#byte TRISA=0X85
#byte PORTB=0X06
#byte TRISB=0X86
int A;
void main(){
   TRISA=0X1F;
   TRISB=0X00;
   PORTA=0;
   PORTB=0;
   while(1){
      A=PORTA&0X1F;      
      switch (A){
      case  0x15:
         PORTB=255;
         delay_ms(200);
         PORTB=0;
         delay_ms(200);
         break;
     case 023:
         PORTB=0XAA;
         delay_ms(200);
         PORTB=0;
         delay_ms(200);
         break;
     case 28:
         PORTB=0X55;
         delay_ms(200);
         PORTB=0;
         delay_ms(200);
         break;    
     default:
      PORTB=0;
    }
  }
}
