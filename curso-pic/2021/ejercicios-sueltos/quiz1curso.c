#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,D,C)
#include <lcd.c>

int A,B=0;
short b7;
void imprimir(){
   A=B;
    if (input(PIN_B7)==0)
         printf(lcd_putc,"\fbajada");
   else
         printf(lcd_putc,"\fsubida");
         }
#INT_RB
serv_int(){
  B=(input_B()&0x80);
    if (A!=B) imprimir();
   else    printf(lcd_putc,"\f");
  }

void main (){
   enable_interrupts(GLOBAL);
   enable_interrupts(int_rb);
   lcd_init();
   A=(input_B()&0x80);
   while(1);

}

