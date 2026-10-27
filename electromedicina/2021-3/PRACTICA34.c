#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,D)
#include <lcd.c>
INT b4,b5,b6,b7;
#INT_RB
void ser_int(void){
         b4=input(pin_b4);
         b5=input(pin_b5);
         b6=input(pin_b6);
         b7=input(pin_b7);       
}
int i;

void main(){
     lcd_init();
     enable_interrupts(INT_RB);
     enable_interrupts(GLOBAL);
     port_b_pullups(1); 
   while(1){
       lcd_gotoxy(1,1);
       printf(lcd_putc,"NB=%u",b4);
       lcd_gotoxy(8,1);
       printf(lcd_putc,"NM=%u",b5);
       lcd_gotoxy(1,2);
       printf(lcd_putc,"NA=%u",b6);
       lcd_gotoxy(8,2);
       printf(lcd_putc,"FULL=%u",b7);
         }
}
