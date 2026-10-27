#include <16F877.h>
#use delay(clock=4000000)
#use standard_io(B)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#include <LCD.C>

void main() {

  int i;

   lcd_init();
   
while(1){
   for (i=0;i<=10;i++) {
     PUTC(i);
     printf(lcd_putc,"\fenviando=%u",i);
     delay_ms(500);
       }
    }
}



