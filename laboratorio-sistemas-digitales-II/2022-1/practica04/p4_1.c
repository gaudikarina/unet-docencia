#include <18F4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#use delay (clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,bits=8)
#include <stdlib.h>
float p[6],f[6]={660.0,962.0,232.0,839.0,420.0,640.0};
int i,j=0;
short a[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
char it[30],cit[30],it2[15];
char del[]="#";
char d[]="\r";
void leerdatos();
#int_RDA 
void serv_int()
{              
       if(kbhit()){
          gets(it); 
   }
}
        
void leerdatos(){
      *it2= strtok(it,d);
      strcpy(cit,it);
      char * token = strtok(cit,del);
        while(token != NULL){
         p[0] = atof(token);
         token = strtok(NULL,del);
         p[1] = atof(token);
         token = strtok(NULL,del);
         p[2]  = atof(token); 
         token = strtok(NULL,del);
         p[3] = atof(token);
         token = strtok(NULL,del); 
         p[4] = atof(token);
         token = strtok(NULL,del);
         p[5]  = atof(token);
         token = strtok(NULL,del);   
        }
}

void main()
{
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   output_D(0);
   output_B(0);
   while(1){
      leerdatos();
      if(p[0]<f[0]){
         output_high(PIN_D0);
         output_low(PIN_B0);}
         else{
         output_low(PIN_D0);
         output_high(PIN_B0);}
      if(p[1]<f[1]){
         output_high(PIN_D1);
         output_low(PIN_B1);}
         else{
         output_low(PIN_D1);
         output_high(PIN_B1);}
      if(p[2]<f[2]){
         output_high(PIN_D2);
         output_low(PIN_B2);}
         else{
         output_low(PIN_D2);
         output_high(PIN_B2);}
      if(p[3]<f[3]){
         output_high(PIN_D3);
         output_low(PIN_B3);}
         else{
         output_low(PIN_D3);
         output_high(PIN_B3);}
      if(p[4]<f[4]){
         output_high(PIN_D4);
         output_low(PIN_B4);}
         else{
         output_low(PIN_D4);
         output_high(PIN_B4);}
      if(p[5]<f[5]){
         output_high(PIN_D5);
         output_low(PIN_B5);}
         else{
         output_low(PIN_D5);
         output_high(PIN_B5);}
   }
} 
   



