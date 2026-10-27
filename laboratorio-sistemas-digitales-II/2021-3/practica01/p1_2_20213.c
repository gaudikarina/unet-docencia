#include <18F4550.h>
#device  high_ints= TRUE
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#use delay (clock=4000000)
#include <string.h>
#use standard_io(A,B,C)  
int ledrv,i=1;
short b4=0,b5=0,b6=0,b7=0,estadop=0;
void alarma();
#int_EXT 
void Interrupcion0()
{   
   clear_interrupt(int_EXT1); //El bit bandera toma el valor de 1
   clear_interrupt(int_EXT2);
   estadop=0;
   if (ledrv==1){      
      ledrv=2;
      enable_interrupts(int_EXT1);
      ext_int_edge(1,L_TO_H);
      enable_interrupts(int_EXT2);
      ext_int_edge(2,L_TO_H);
      enable_interrupts(int_RB);  
      estadop=0;
   }
   else if (ledrv==2){
      estadop=0;
      ledrv=1;
      disable_interrupts(int_RB); 
      disable_interrupts(int_EXT1);
      disable_interrupts(int_EXT2);
 //     disable_interrupts(GLOBAL);
      i=951;
      estadop=0;
      }
      estadop=0;
 }

#int_RB high
void Puerta_abierta()
{   
   b4=input(PIN_B4);
   b5=input(PIN_B5);
   b6=input(PIN_B6);
   b7=input(PIN_B7);
   if (b4==1||b5==1||b6==1||b7==1)
    estadop=1;
}

#int_EXT1 
void Interrupcion1()
{   
 //  estadop=0;
   if (ledrv==2)
      estadop=1;
  }

#int_EXT2 
void Interrupcion2()
{
//   estadop=0;
    if (ledrv==2)
      estadop=1;

}
void alarma(){
   while(i<100){
   output_high(pin_A0);
   delay_us(125+i);
   output_low(pin_A0);
   delay_us(125+i);
   i++;
   }
   i=1;
}
void main()
{
   enable_interrupts(int_EXT);
   ext_int_edge(0,H_TO_L);
   enable_interrupts(GLOBAL);
   port_b_pullups(true);
   ledrv=1;
   estadop=0;
   while(1){
    output_C(ledrv);
    output_D(estadop);
    if (estadop==1) {
      i=1;
      alarma();
    }
   }
}
