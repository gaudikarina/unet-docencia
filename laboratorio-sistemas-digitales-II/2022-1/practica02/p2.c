#include <18F4550.h>
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#use delay (clock=4000000)
#include<hdm64gs12gaudi.c>
#include <graphics.c>
#include <string.h>
#use standard_io(A,B,C,D,E)  
int c1=0,c2=0,c3=0,c4=0,i=1;
short b4=0,b5=0,b6=0,b7=0,estadoa=0,f=0,parada=0;
char cc1[1];
char cc2[1];
char cc3[1];
char cc4[1];
char v[6];
char A[]="ALARMA";
char P[]="PARADA";
char L2[]="L2";
char L3[]="L3";
char L4[]="L4";
char L1[]="L1";


void alarma();
void menu();
#int_EXT 
void Interrupcion0()
{   
   if(estadoa==1){
         output_low(pin_E0);
         estadoa=0;  
         c1=0;
         c2=0;
         c3=0;
         c4=0;
         output_A(0);
}
}

#int_RB
void Lineas0104()
{   
   b4=input(PIN_B4);
   b5=input(PIN_B5);
   b6=input(PIN_B6);
   b7=input(PIN_B7);
   if (b4==1){
      if (c1<48)
         c1++;
      else
         output_high(pin_A0);
   }
   if (b5==1){
      if (c2<24)
           c2++;
      else
         output_high(pin_A1);  
   }
    if (b6==1){
      if (c3<36)
         c3++;
      else
         output_high(pin_A2);  
    }
   
   if (b7==1){
      if (c4<60)
         c4++;
      else
         output_high(pin_A3);  
   }
}

#int_EXT1 
void Interrupcion1()
{   
      if (estadoa==0){
      parada=1;
      disable_interrupts(int_RB);  
      }
}


#int_EXT2 
void Interrupcion2()
{
   if (parada==1){
   parada=0;
   enable_interrupts(int_RB);
   }
}
void alarma(){
   while(i<100){
   output_high(pin_E0);
   delay_us(125+i);
   output_low(pin_E0);
   delay_us(125+i);
   i++;
   }
   i=1;
}
void menu(){
      glcd_text57(20,10,L1, 1, 1);
      glcd_text57(40,10,L2, 1, 1);
      glcd_text57(60,10,L3, 1, 1);
      glcd_text57(80,10,L4, 1, 1);
      sprintf(cc1,"%d",c1);
      glcd_text57(20,20,cc1, 1, 1);
      sprintf(cc2,"%d",c2);
      glcd_text57(40,20,cc2, 1, 1);
      sprintf(cc3,"%d",c3);
      glcd_text57(60,20,cc3, 1, 1);
      sprintf(cc4,"%d",c4);
      glcd_text57(80,20,cc4, 1, 1);
}
void main()
{
   enable_interrupts(int_EXT);
   ext_int_edge(0,H_TO_L);
   enable_interrupts(int_EXT1);
   ext_int_edge(1,H_TO_L);
   enable_interrupts(int_EXT2);
   ext_int_edge(2,H_TO_L);
   enable_interrupts(int_RB);
   enable_interrupts(GLOBAL);
   port_b_pullups(true);
   estadoa=0;
   glcd_init(ON);
   glcd_fillScreen(OFF);
   while(1){
      if(parada==0){
         if (c1==48 && c2==24 && c3==36 && c4==60)
             estadoa=1;
      if(estadoa==0){
      menu();
      }
      else{
       menu();
       glcd_text57(30,40,A, 2, 1);
       alarma();}
 
    }
    else{
      menu();
      glcd_text57(30,40,P, 2, 1);  
   }
    delay_ms(500);
    glcd_fillScreen(OFF);
}
}

