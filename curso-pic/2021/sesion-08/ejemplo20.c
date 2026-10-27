#include <16F877.h>
#device adc=10
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, bits=8)
#include <LCD.C>

void main() {
   int16 q;
   float p;
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   lcd_init();
   While (1) {
      set_adc_channel(0);
      delay_us(10);
      q = read_adc();
      p = 5.0 * q / 1024.0;
      printf(lcd_putc, "\fADC = %4ld", q);
      printf(lcd_putc, "\nVoltage = %01.2fV", p);
      printf("ADC = %4ld ", q);
      printf("Voltage = %01.2fV\r", p);  // El \r permite cambiar de línea.
      delay_ms(100);
      }
}
