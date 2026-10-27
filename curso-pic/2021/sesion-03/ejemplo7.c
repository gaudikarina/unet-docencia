#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(D)
#include <kbd.c>

int i,D;
char T;

void main(){
	output_B(0);
	kbd_init();
	while(1){
		T=kbd_getc();
		switch(T)
		{
		case '1':
			output_B(1);
			break;
		case '2':
			output_B(3);
			break;
		case '3':
			output_B(7);
			break;
		case '4':
			output_B(15);
			break;
		case '5':
			output_B(31);
			break;
		case '6':
			output_B(63);
			break;
		case '7':
			output_B(127);
			break;
		case '8':
			output_B(255);
			break;
		case '9':
			for(i=0;i<=10;i++){
	
			output_B(0);
			delay_ms(50);
			output_B(255);
			delay_ms(50);
			}
			break;
		case '*':
			i=0;
			D=0x80;
			for(i=0;i<=7;i++){
			output_B(D);
			delay_ms(500);
			D>>=1;
			}
			break;
		case '#':
			i=0;
			D=1;
			for(i=0;i<=7;i++){
			output_B(D);
			delay_ms(500);
			D<<=1;
			}
			break;
		}
	}
}