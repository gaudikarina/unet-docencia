#include <16f877.h>
#device adc=10
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,bits=8)
#include<lcd.c>
char T=0;
int16 Ch2,Ch4,Ch6;
float V1, V2,V3;
#int_RDA
serv_int()
{
T=getc();
  }

void main(){
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   lcd_init();
   setup_adc(ADC_CLOCK_DIV_8);
   setup_adc_ports(ALL_ANALOG);
   while(1){
      set_adc_channel(2);
      Ch2=read_adc();
      delay_us(20);
      set_adc_channel(4);
      Ch4=read_adc();
      set_adc_channel(6);
      Ch6=read_adc();
      delay_us(20);
      V1=5.0*Ch2/1024.0;// cuando se utiliza valores con decimales es necesario que los valores enteros se expresen con un decimal
      V2=5.0*Ch4/1024.0;
      V3=5.0*Ch6/1024.0;
      switch(T){
         case '2':
         printf("*****Canal 2*****\r");
         printf("ADC=%4ld   ",Ch2);
         printf("V=%1.2f\r",V1);
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);
         printf(lcd_putc,"Canal 2");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ADC=%4ld",Ch2);
         lcd_gotoxy(10,2);
         printf(lcd_putc,"V=%1.2f",V1);
         delay_ms(2000); 
         break;
         case '4':
         printf("*****Canal 4*****\r");
         printf("ADC=%4ld   ",Ch4);
         printf("V=%1.2f\r",V2);
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);
         printf(lcd_putc,"Canal 4");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ADC=%4ld",Ch4);
         lcd_gotoxy(10,2);
         printf(lcd_putc,"V=%1.2f",V2);
         delay_ms(2000);
         break;
         case '6':
         printf("*****Canal 6*****\r");
         printf("ADC=%4ld   ",Ch6);
         printf("V=%1.2f\r",V3);
         printf(lcd_putc,"\f");
         lcd_gotoxy(4,1);
         printf(lcd_putc,"Canal 6");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ADC=%4ld",Ch6);
         lcd_gotoxy(10,2);
         printf(lcd_putc,"V=%1.2f",V3);
         delay_ms(2000); 
         break;
         default:
         printf("Presiona # Ch\r");
         printf(lcd_putc,"\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc,"Presiona # Ch");   
         delay_ms(2000);
         break;
      }
   }
}
