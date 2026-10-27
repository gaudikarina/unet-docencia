#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,C)
#define use_portb_kbd TRUE
#include <kbd_4.c>
int i,C;
char T;
void main(){
   port_b_pullups(1);
   output_C(0);
   kbd_init();
   while(1){
      T=kbd_getc();
      switch(T)
      {
      case '1':
         output_C(1);
         break;
      case '2':
         output_C(3);
         break;
      case '3':
         output_C(7);
         break;
      case '4':
         output_C(15);
         break;
      case '5':
         output_C(31);
         break;
      case '6':
         output_C(63);
         break;
      case '7':
         output_C(127);
         break;
      case '8':
         output_C(255);
         break;
      case '9':
         for(i=0;i<=10;i++){
         output_C(0);
         delay_ms(50);
         output_C(255);
         delay_ms(50);
         }
         break;
      case '*':
         i=0;
         C=0x80;
         for(i=0;i<=7;i++){
         output_C(C);
         delay_ms(500);
         C>>=1;
         }
         break;
      case '#':
         i=0;
         C=1;
         for(i=0;i<=7;i++){
         output_C(C);
         delay_ms(500);
         C<<=1;
         }
         break;
       case 'A':
         output_C(0);
         delay_ms(50);
         output_C(0x55);
         delay_ms(50);
         break;
       case 'B':
         output_C(0);
         delay_ms(50);
         output_C(0xAA);
         delay_ms(50);
         break;
       case 'C':
         output_C(0);
         delay_ms(50);
         output_C(0xf0);
         delay_ms(50);
         break;
       case 'D':
         output_C(0);
         delay_ms(50);
         output_C(0x0f);
         delay_ms(50);
         break;
         
      }
   }
}
