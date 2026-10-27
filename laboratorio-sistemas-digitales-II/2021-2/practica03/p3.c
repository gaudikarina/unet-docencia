#include <18f4550.h>
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#device adc=10
#use delay (clock=20000000)
#include <math.h>
#include <lcd.c>
void main() {
   int16 q;
   float p,r,l;
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   While (1) {
      q = read_adc();
      p = 5.0 * q / 1024.0;
      r = pow(p, -1.993);
      l=54.935*r;
      printf(lcd_putc,"ADC = %4ld ", q);
      printf(lcd_putc,"Voltage = %01.2fV\r", p);  // El \r permite cambiar de línea.
      delay_ms(500);
      printf(lcd_putc,"\fLuz = %01.2fLux", l);
      }
}
