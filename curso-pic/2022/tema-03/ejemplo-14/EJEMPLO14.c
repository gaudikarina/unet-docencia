#include <16F877.h>
#include <stdlib.h>
#use delay (clock=4000000)
#use standard_io(B,D)
const int display[8]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07};
int d,b;
#INT_EXT
serv_int(){
    b=display[d];
    output_D(b);     
}

void main (){
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ext);
   ext_int_edge(H_TO_L);   
   port_b_pullups(1);
   while(1){
         d=rand()%7+1;      
   }
}   


