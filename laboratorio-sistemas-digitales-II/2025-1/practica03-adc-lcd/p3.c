#include <18f4550.h>
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#device adc=10
#use delay (clock=20000000)
#include <math.h>
#include <lcd.c>
void main() {
   int16 q;
   float p,r,n,l;
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   lcd_init();
   While (1) {
      q = read_adc();
      p = 5.0 * q / 1024.0;
      r = 5.0*p/(5.0-p);
      n=(log10(r)-2.1053)/-0.8583;
      l=pow(10,n);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fADC = %4ld ", q);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Voltage = %01.2f V\r", p);  // El \r permite cambiar de línea.
      delay_ms(500);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fLuz = %01.2f Lux", l);
      delay_ms(500);
      }
}
