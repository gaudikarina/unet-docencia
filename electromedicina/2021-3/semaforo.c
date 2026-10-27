#include <16f84a.h>
#use delay(clock=4000000)
#byte PORTA=0X05
#byte TRISA=0X85
#byte PORTB=0X06
#byte TRISB=0X86
void main(){
   TRISA=0X00;
   TRISB=0X00;
   PORTA=0;
   PORTB=0;
   while(1){
      PORTA=0X01;
      PORTB=0X04;
      delay_ms(200);
      PORTB=0X02;
      delay_ms(50);
      PORTA=0X04;
      PORTB=0X01;
      delay_ms(200);
      PORTA=0X02;
      delay_ms(50);         
   }
}
