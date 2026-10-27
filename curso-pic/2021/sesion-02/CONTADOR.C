#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(A,B)

int CL,CH,C,b,i,j,CLD,CHD;
const int display[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int bcd_7seg(int a){
   b=display[a];
   return(b);
}

void   mostrar_display(){
   output_A(1);
   output_B(CLD);
   delay_us(600);
   output_A(0);
   output_B(0);
   output_A(2);
   output_B(CHD);
   delay_us(1000);
   output_A(0);
   output_B(0);
   return;
}

void main (){
   while(1){
      CL=0;
      CH=0;
      i=j=0;
      for(i==0;i<=9;i++){
         for(j==0;j<=9;j++){
         CLD=bcd_7seg(CL);
         CHD=bcd_7seg(CH);
         mostrar_display();
         CL+=1;
         }
         CH+=1;
         CL=0;
         j=0;   
      }
      i=j=0;
      CL=9;
      CH=9;
      for(i==0;i<=9;i++){
         for(j==0;j<=9;j++){
         CLD=bcd_7seg(CL);
         CHD=bcd_7seg(CH);
         mostrar_display();
         CL-=1;
         }
         CH-=1;
         CL=9;
         j=0;
      }
   }   
}      
