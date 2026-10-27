 #include <16F877.h>
#device adc=10
#use delay(clock=4000000)

#use standard_io(B)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, bits=8)
#include <LCD.C>
int caracter[30];
int i,qh,ql;
long j;
float p;

#int_RDA
serv_int()
{
   GETS(caracter);
}

void main() {

   lcd_init();
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

for (;;) {
     lcd_gotoxy(1,1);
	qh=caracter[1];
	ql=caracter[0];
	j=make16(qh,ql);
	p=j*5.0/1024.0;
     printf(lcd_putc,"\f%1.2f,%lu",p,j);
    delay_ms(300);
   }
}
