#include <16F877.h>
#device adc=10
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#include <LCD.C>

int ql,qh;
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

     ql=q/4;
   qh=make8(q,1);
   printf("%u",ql);
	 printf(lcd_putc,"%u",ql);     
      delay_ms(500);
      }
}
