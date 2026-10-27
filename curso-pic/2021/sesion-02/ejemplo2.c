#include <16f877.h>
#use delay(clock=4000000)
#use standard_io(E,C)
int C;
void main()
{
	while(1){
	C=(input(pin_E0)&input(pin_E2))+(!(input(pin_E1))^input(pin_E0));
	output_C(C);
	}
}
