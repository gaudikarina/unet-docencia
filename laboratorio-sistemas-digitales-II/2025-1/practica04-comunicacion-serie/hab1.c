#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device adc=10
#use delay (clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,stream=Remoto)
#use rs232(baud=9600, xmit=pin_e1, rcv=pin_e2,stream=PC)
#include <math.h>
#include <lcd.c>
#use standard_io(E)
int16 q;
float p,r,n,l,l1=0;
char c=0;

void enviarserial(){
     //    fprintf(PC,"\f Sala Monitoreo\r");
     //   fprintf(PC,"%1.2f",l);
      fprintf(Remoto,"%1.2f\r",l); 
}
void main() {   
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   lcd_init();
   output_low(PIN_E0);
   While (1) {
      q = read_adc();
      p = 5.0 * q / 1024.0;
      r = 5.0*p/(5.0-p);
      n=(log10(r)-2.1053)/-0.8583;
      l=pow(10,n);
      if (l!=l1){
         enviarserial();
         l1=l;
      }
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Luz = %01.2f Lux", l);          
   }
}
