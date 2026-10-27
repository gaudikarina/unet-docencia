#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(A,B)
//#use standard_io(B)

int A,B,i;
void main ()
{
	while (1){
	A=input_A();
	A&=3;
	switch(A)
	{
		case 0:
		output_B(0x00);
		delay_ms(500);
		output_B(255);
		delay_ms(500);
		break;
		case 1:
		output_B(0x55);
		delay_ms(500);
		output_B(0xAA);
		delay_ms(500);
		break;
		case 2:
		B=0xC0;
		for(i=0;i<=3;i++)
		{
			output_B(B);
			delay_ms(500);
			B>>=2;
		}
		break;
		case 3:
		B=3;
		for(i=0;i<=3;i++)
		{
			output_B(B);
			delay_ms(500);
			B<<=2;
		}
		break;
	}
	}
}
		