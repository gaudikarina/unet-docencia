#include <16f877.h>
#device adc=10
#use delay(clock=4000000)
#include <lcd.c>
int16 Ch0,Ch1;
float V1, V2;
void main(){
   lcd_init();
   setup_adc(ADC_CLOCK_DIV_8);
   setup_adc_ports(AN0_AN1_AN3);
   while(1){
      set_adc_channel(0);
      Ch0=read_adc();
      delay_us(20);
      set_adc_channel(1);
      Ch1=read_adc();
      delay_us(20);
      V1=5.0*Ch0/1024.0;// cuando se utiliza valores con decimales es necesario que los valores enteros se expresen con un decimal
      V2=5.0*Ch1/1024.0;
      lcd_gotoxy(4,1);
      printf(lcd_putc,"Canal 0");
      lcd_gotoxy(1,2);
      printf(lcd_putc,"ADC=%4ld",Ch0);
      lcd_gotoxy(10,2);
      printf(lcd_putc,"V=%1.2f",V1);
      delay_ms(2000);
      lcd_gotoxy(4,1);
      printf(lcd_putc,"Canal 1");
      lcd_gotoxy(1,2);
      printf(lcd_putc,"ADC=%4ld",Ch1);
      lcd_gotoxy(10,2);
      printf(lcd_putc,"V=%1.2f",V2);
      delay_ms(2000);
   }
 }
