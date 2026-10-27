#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,D,C)
#include <lcd.c>

int    b,i;

#INT_EXT
serv_intext(){
   disable_interrupts(int_rb);
   lcd_gotoxy(4,1);
   printf(lcd_putc,"desactivado");
   }

#INT_RB
serv_int(){
   if((input(PIN_B4)|| input(PIN_B5)|| input(PIN_B6)|| input(PIN_B7))==1){
   lcd_gotoxy(4,1);
   printf(lcd_putc,"alarma");
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ext);
}
}

void main (){
   enable_interrupts(GLOBAL);
   enable_interrupts(int_rb);
   enable_interrupts(int_ext);
   ext_int_edge(L_TO_H);
   lcd_init();
   while(1);
}
