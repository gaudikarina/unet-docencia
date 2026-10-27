#include <18F4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#use delay (clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,bits=8)
#include <stdlib.h>
#include "tones.c"   
float p[6],f[6]={700,327,180,98,64,639};
char a1[6];
int i,j=0,pulso;
char it[30],cit[30],it2[15];
char del[]="/";
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
   output_B(0);
   while(1){
      leerdatos();
      j=0;
      if(p[0]>f[0])
         j++;       
      if(p[1]>f[1])
         j++;
      if(p[2]>f[2])
         j++;
      if(p[3]>f[3])
         j++;
      if(p[4]>f[4])
         j++;
      if(p[5]>f[5])
         j++;
      switch (j){
         case 1:
               generate_tone(C_NOTE[0],500);
               break;
         case 2:
               generate_tone(C_NOTE[0],500);
               generate_tone(C_NOTE[1],500);
               break;
         case 3:
               generate_tone(C_NOTE[0],500);
               generate_tone(C_NOTE[1],500);
               generate_tone(C_NOTE[2],500);
               break;
        case 4:
               generate_tone(C_NOTE[0],500);
               generate_tone(C_NOTE[1],500);
               generate_tone(C_NOTE[2],500);
               generate_tone(C_NOTE[3],500);
               break;       
        case 5:
               generate_tone(C_NOTE[0],500);
               generate_tone(C_NOTE[1],500);
               generate_tone(C_NOTE[2],500);
               generate_tone(C_NOTE[3],500);
               generate_tone(D_NOTE[0],500);
               break;       
        case 6:
               generate_tone(C_NOTE[0],500);
               generate_tone(C_NOTE[1],500);
               generate_tone(C_NOTE[2],500);
               generate_tone(C_NOTE[3],500);
               generate_tone(D_NOTE[0],500);
               generate_tone(D_NOTE[1],500);
               break;             
      
      }
   }
     
         
} 
   



