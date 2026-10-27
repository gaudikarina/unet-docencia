#include <16F877.h>
#use delay (clock=20000000)
#use standard_io(B)
#include <lcd.c>

int	pulso,i;
short b;
const int a[8]={1,2,5,10,20,50,100,200};


#INT_RB
serv_int(){
	b=input(pin_B7);
	if (b==1) pulso++;
	if (pulso==8) pulso=0;
	lcd_putc('\f');
	lcd_gotoxy(2,1);
	switch(pulso)
	{
		case 0:
		printf(lcd_putc,"F = 10 KHz");
		break;
		case 1:
		printf(lcd_putc,"F = 5 KHz");
		break;
		case 2:
		printf(lcd_putc,"F = 2 KHz");
		break;
		case 3:
		printf(lcd_putc,"F = 1 KHz");
		break;
		case 4:
		printf(lcd_putc,"F = 500 Hz");
		break;
		case 5:
		printf(lcd_putc,"F = 200 Hz");
		break;
		case 6:
		printf(lcd_putc,"F = 100 Hz");
		break;
		case 7:
		printf(lcd_putc,"F = 50 Hz");
		break;
		}
	}

#INT_TIMER0
void serv_int(void){
		output_toggle(PIN_B3);
		switch(pulso)
		{
		case 0:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);
		set_timer0(151);
		break;
		case 1:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);
		set_timer0(20);
		break;
		case 2:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8);
		set_timer0(105);
		break;	
		case 3:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16);
		set_timer0(103);
		break;
		case 4:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_32);
		set_timer0(100);
		break;
		case 5:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_64);
		set_timer0(60);
		break;	
		case 6:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_128);
		set_timer0(60);
		break;
		case 7:
		setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256);
		set_timer0(60);
		break;	
		
		}
}
		
	


void main (){
	pulso=0;
	output_low(pin_B3);
	lcd_init();
	lcd_gotoxy(2,1);
	printf(lcd_putc,"F = 10 KHz");
	setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);
	enable_interrupts(GLOBAL);
	enable_interrupts(int_timer0);
	enable_interrupts(int_rb);
	set_timer0(131);
	while(1);
}