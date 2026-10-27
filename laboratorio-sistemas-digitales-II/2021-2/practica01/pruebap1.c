#include <18f4550.h>
#fuses NOWDT,NOPROTECT,NOLVP,NOCPD,NOBROWNOUT,NOPUT,NOMCLR,NODEBUG,HS,NOPBADEN
#use delay(clock=2000000)
//!#use standard_io(B)
//!#use standard_io(D)
#define lcd_data_port getenv("sfr:portd")
#define lcd_enable_pin pin_d0
#define lcd_rs_pin pin_d1
#define lcd_rw_pin pin_d2
#define use_portb_kbd TRUE
#include <lcd.c>
#include <kbd_4.c>
void main()
{
   char k;
   int x;
   port_b_pullups(true);
   lcd_init();
   kbd_init();
   printf(lcd_putc,"Prueba Gau");
   delay_ms(200);
   printf(lcd_putc,"\f");
   while(true)
   {
      k=kbd_getc();
      x=k-48;
      if (k!=0)
      {
         lcd_gotoxy(1,1);
         printf(lcd_putc,"tecla pulsada: %c",k);
      }
   }
   
}

      
   
   
