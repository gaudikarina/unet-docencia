#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,C)
#define use_portb_kbd TRUE
#include <kbd.c>
#include <lcd.c>
int i,C;
char T;
void main(){
   port_b_pullups(1);
   kbd_init();
   lcd_init();
      while(1){
       T=kbd_getc();
         switch(T)
         {
          case '2':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"UNET");
         break;
         case '4':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"MICRO");
         break;
         case '7':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"ELE646T");
         break;
       }
      }      
}
