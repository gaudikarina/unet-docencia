#include <16F877.h>
#device adc=10
#use delay (clock=4000000)
#use standard_io(B)

#include<lcd.c>
#include<math.h>

float   V;
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
      printf(lcd_putc,"\fNcad= %ld",Ncad);
      printf(lcd_putc,"\nVoltaje= %1.3fV",V);
      delay_ms(100);
   }
}
