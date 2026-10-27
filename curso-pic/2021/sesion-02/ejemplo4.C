#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(A,D,B,C)

int CL,CH,DL,DH,BH,BL,b;
const int display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int bcd_7seg(int a){
	b=display[a];
	return(b);
}

void	mostrar_display(){
	output_A(1);
	output_B(BL);
	delay_ms(3);
	output_A(0);
	output_B(0);
	output_A(2);
	output_B(BH);
	delay_ms(3);
	output_A(0);
	output_B(0);
	return;
}

short validar_bcd(int a){
	if (a>=10)
		b=0;
	else	
		b=1;
	return(b);	
}
void main (){
	while(1){
		CL=input_C()&15;
		CH=swap(input_C()&0XF0);
		DL=input_D()&15;
		DH=swap(input_D()&0XF0);
		if(validar_bcd(CL)&&validar_bcd(CH)&&validar_bcd(DL)&&validar_bcd(DH)){
				if(input_D()>input_C()){
					if((DL == 0)&&(CL != 0)){
						BH=DH-CH-1;
						BL=10-CL;
						BH=bcd_7seg(BH);
						BL=bcd_7seg(BL);
					}
					else{
					BH=DH-CH;
					BL=DL-CL;
					BH=bcd_7seg(BH);
					BL=bcd_7seg(BL);
					}
				}
				else
				{
					if((CL == 0)&&(DL != 0)){
					BH=CH-DH-1;
					BL=10-DL;
					BH=bcd_7seg(BH);
					BL=bcd_7seg(BL);
					}
					else{
					BH=CH-DH;
					BL=CL-DL;
					BH=bcd_7seg(BH);
					BL=bcd_7seg(BL);
					}
				}
		}
		else		
		BH=BL=0X79;
		mostrar_display();
	}
}		