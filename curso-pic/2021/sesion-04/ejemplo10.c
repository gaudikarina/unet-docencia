#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,D,C)
#include <lcd.c>

const char a[7]={'a','b','i','e','r','t','a'};
const char c[7]={'c','e','r','r','a','d','a'};

int 	b,i;
short	b4=0,b5=0,b6=0,b7=0;


void estado(short z){
	if (z==0)
			printf(lcd_putc,"%s",c);
	else
			printf(lcd_putc,"%s",a);
}

#INT_RB
serv_int(){
	b4=input(PIN_B4);
	b5=input(PIN_B5);
	b6=input(PIN_B6);
	b7=input(PIN_B7);
	lcd_gotoxy(1,1);
	printf(lcd_putc,"S1:");
	estado(b4);
	lcd_gotoxy(1,2);
	printf(lcd_putc,"S2:");
	estado(b5);
	delay_ms(500);
	lcd_gotoxy(1,1);
	printf(lcd_putc,"S3:");
	estado(b6);
	lcd_gotoxy(1,2);
	printf(lcd_putc,"S4:");
	estado(b7);
	delay_ms(500);
	}
void main (){
	enable_interrupts(GLOBAL);
	enable_interrupts(int_rb);
	lcd_init();
	lcd_gotoxy(1,1);
	printf(lcd_putc,"S1:");
	estado(b4);
	lcd_gotoxy(1,2);
	printf(lcd_putc,"S2:");
	estado(b5);
	delay_ms(500);
	lcd_gotoxy(1,1);
	printf(lcd_putc,"S3:");
	estado(b6);
	lcd_gotoxy(1,2);
	printf(lcd_putc,"S4:");
	estado(b7);
	delay_ms(500);
	while(1);
}