#include <16F877.h>
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, bits=8)
#include <LCD.C>

char ch;

#int_rda
void serial_isr() {
    ch=getchar();
    puts("Recibido");
}

void main()
{
lcd_init();
   enable_interrupts(global);
   enable_interrupts(int_rda);
while(1)  {
   printf(lcd_putc, "\n\r Valor %c",ch);
    }
}
