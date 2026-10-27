#include <16F877.h>
#device adc=10
#use delay (clock=4000000)
#use standard_io(B)

#include<lcd.c>
#include<math.h>

float   V,T,R;
long   Ncad;
 
void main (){
   setup_adc(ADC_CLOCK_DIV_8);
   setup_adc_ports(AN0);
   lcd_init();
   
   while(1){
      set_adc_channel(0);
      delay_us(20);
      Ncad=read_adc();
      V=5.0*Ncad/1024.0;
	  R=10000.0*V/(5.0-V);
	  T=(1.0/((1.0/4050.0)*log(R/20000.0)+1.0/298.15)-273.15);
      printf(lcd_putc,"\fV= %1.3f Volts",V);
      printf(lcd_putc,"\nT= %4.2f C",T);
      delay_ms(100);
   }
}