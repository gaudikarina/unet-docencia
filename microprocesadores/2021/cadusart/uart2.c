#include <16f877.h>
#device adc=10
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,bits=8)
#include<lcd.c>
char T;
#int_RDA
serv_int()
{
T=getc();
  }

void main(){
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   lcd_init();
   while(1){
   lcd_gotoxy(1,1);
   printf(lcd_putc,"La Tecla es: %c",T);
   }
}
