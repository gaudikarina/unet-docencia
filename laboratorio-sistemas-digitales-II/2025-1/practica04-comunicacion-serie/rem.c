#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device adc=10
#use delay (clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#include <math.h>
#include <lcd.c>
#include <stdlib.h>
#use standard_io(C)
char it[44];
float l;
#int_RDA
serv_int()
{          

        if(kbhit()){
          gets(it);
         }
        
}

void main() {
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   lcd_init();
   While (1) {   
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Luz= %sLux", it);
      delay_ms(500);
      l=atof(it);
      if (l>50){
         output_high(pin_C0);
         delay_ms(150);
         output_low(pin_C0);
         delay_ms(150);
      }
   }
}
