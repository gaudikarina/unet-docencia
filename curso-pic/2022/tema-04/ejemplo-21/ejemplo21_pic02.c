 #include <16F877.h>
#use delay(clock=4000000)
#use standard_io(B)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, bits=8)
#include <LCD.C>

int i;

#int_RDA
serv_int()
{
   i=GETC();
}

void main() {

   lcd_init();
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

for (;;) {
     lcd_gotoxy(1,1);
     printf(lcd_putc,"\frecibiendo=%u",i);
    delay_ms(500);
   }
}
