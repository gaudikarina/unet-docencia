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
         case '0':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"0");
            lcd_gotoxy(6,2);
            printf(lcd_putc,"Cero"); 
         break;
         case '1':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"1");
            lcd_gotoxy(6,2);
            printf(lcd_putc,"Uno"); 
         break;
         case '2':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"2");
            lcd_gotoxy(6,2);
            printf(lcd_putc,"Dos"); 
         break;
         case '3':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"3");
            lcd_gotoxy(6,2);
            printf(lcd_putc,"Tres"); 
         break;
         case '4':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"4");
            lcd_gotoxy(5,2);
            printf(lcd_putc,"Cuatro"); 
         break;
         case '5':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"5");
            lcd_gotoxy(4,2);
            printf(lcd_putc,"Cinco"); 
         break;
         case '6':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"6");
            lcd_gotoxy(6,2);
            printf(lcd_putc,"Seis"); 
         break;
         case '7':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"7");
            lcd_gotoxy(5,2);
            printf(lcd_putc,"Siete"); 
         break;
         case '8':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"8");
            lcd_gotoxy(6,2);
            printf(lcd_putc,"Ocho"); 
         break;
         case '9':
            printf(lcd_putc,"\f");
            lcd_gotoxy(7,1);
            printf(lcd_putc,"9");
            lcd_gotoxy(5,2);
            printf(lcd_putc,"Nueve");         
         break;
         case '*':
            printf(lcd_putc,"\f");
            lcd_gotoxy(1,1);
            printf(lcd_putc,"Bienvenidos a");
            lcd_gotoxy(3,2);
            printf(lcd_putc,"ELE 646T"); 
         break;
         case '#':
            printf(lcd_putc,"\f");
            lcd_gotoxy(5,1);
            printf(lcd_putc,"Adios");
            lcd_gotoxy(3,2);
            printf(lcd_putc,"ELE 646T");
         break;
      }
      }      
}
