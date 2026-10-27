#include <16F877.h>
#device adc=10
#use delay(clock=4000000)
#use standard_io(B)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#include <LCD.C>

void main() {

  long i;
	int il,ih;
   lcd_init();
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   
while(1){
     set_adc_channel(0);
      delay_us(10);
      i = read_adc();
	il=make8(i,0);
	ih=make8(i,1);
     
   	PUTC(il);
	putc(ih);
	putc(13);
	
     printf(lcd_putc,"\f%ld",i);
     delay_ms(300);
       }
    }




