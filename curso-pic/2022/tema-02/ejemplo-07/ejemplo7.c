#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,D)
#include <lcd.c>
int B,B1,B2,B3;
void bin_octal(){
   B1=B&7;
   B2=(B>>3)&7;
   B3=(B>>6)&3;
}
void main(){
   port_b_pullups(1);
   lcd_init();
   while(1){
      B=input_B();
      bin_octal();
      lcd_gotoxy(6,1);
      printf(lcd_putc,"%u %u %u\n",B3,B2,B1);
      lcd_gotoxy(4,2);
      printf(lcd_putc,"Base Octal");
      delay_ms(50);
      lcd_gotoxy(4,2);
      printf(lcd_putc,"          ");
      delay_ms(50);
      }
}
