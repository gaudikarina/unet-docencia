#include <16F877.h>
#include <stdlib.h>
#use delay (clock=4000000)
#use standard_io(B,D,C)

int b,i,BING,BLT,BLD,BHD,CLD;
const int display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int bcd_7seg(int a){
	b=display[a];
	return(b);
}
void bin_bcd (int a){
	int d,r;
	d=a/10;
	r=a%10;
	if	(d>9){
		CLD=d/10;
		BHD=d%10;
		BLD=r;
	}	
	else{
		BHD=d;
		BLD=r;
	}
}
	
void	mostrar_display(){
	output_C(4);
	output_D(BLD);
	delay_Us(500);
	output_C(0);
	output_D(0);
	output_C(2);
	output_D(BHD);
	delay_Us(500);
	output_C(0);
	output_D(0);
	output_C(1);
	output_D(BLT);
	delay_Us(500);
	output_C(0);
	output_D(0);
	return;
}
#INT_EXT
serv_int(){
		if((0<BING)&&(BING<=15))
		BLT=0X7C;
		else if((15<BING)&&(BING<=30))
			BLT=0X19;
			else if((30<BING)&&(BING<=45))
				BLT=0X54;
				else if((45<BING)&&(BING<=60))
					BLT=0X6F;
					else if((60<BING)&&(BING<=75))
						BLT=0X3F;
		bin_bcd(BING);
		BHD=bcd_7seg(BHD);
		BLD=bcd_7seg(BLD);
		BING=BING+7;
}



void main (){
	enable_interrupts(GLOBAL);
	enable_interrupts(int_ext);
	ext_int_edge(L_TO_H);
	
	while(1){
		BING=1;
		while(BING<=75){
		BING++;
		mostrar_display();
		}
	}
}	