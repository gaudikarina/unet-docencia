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
      lcd_gotoxy(3,1);
      printf(lcd_putc,"HEX");
      lcd_gotoxy(9,1);
      printf(lcd_putc,"OCT");
      lcd_gotoxy(3,2);
      printf(lcd_putc,"%X",B);
      lcd_gotoxy(9,2);
      printf(lcd_putc,"%u %u %u\n",B3,B2,B1);

      }
}
