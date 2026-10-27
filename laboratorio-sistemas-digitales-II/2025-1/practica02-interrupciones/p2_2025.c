#include <18F4550.h>
#device  high_ints= TRUE
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#use delay (clock=20000000)
#include <lcd.c>
#use standard_io(A,B,C)  

int cf,cm,cp,ca;
short b4,b5,conflicto,parada;

#int_EXT 
void Interrupcion0()
{   
      disable_interrupts(int_RB); 
      disable_interrupts(int_EXT1);
      disable_interrupts(int_EXT2);
 //     disable_interrupts(GLOBAL);
     parada=1;
     cp=0;
      cm=0;
      ca=0;
      cf=0;
 }

#int_RB 
void Puerta_abierta()
{   
   b4=input(PIN_B4);
   b5=input(PIN_B5);   
   if (b4==1 && b5==0){
      cp+=1;
      conflicto=0;}
   if (b5==1 && b4==0){
      ca+=1;  
      conflicto=0;}
   if (b5==1 && b4==1)
      conflicto=1;
}
#int_EXT1 high
void Interrupcion1()
{   
   cf+=1;
  }

#int_EXT2 high 
void Interrupcion2()
{
   cm+=1;
}
void mostrar(){
   if (parada==0){
      if (conflicto==0){
         lcd_gotoxy(1,1);
         printf(lcd_putc, "\fFresa=%d",cf);
         lcd_gotoxy(9,1);
         printf(lcd_putc, "Mango=%d",cm);
         lcd_gotoxy(1,2);
         printf(lcd_putc, "Pera=%d",cp);
         lcd_gotoxy(9,2);
         printf(lcd_putc, "Apple=%d",ca);
         delay_ms(50);
      }else{
         lcd_gotoxy(1,1);
         printf(lcd_putc,"\f Conflicto ");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "Pera=%d",cp);
         lcd_gotoxy(9,2);
         printf(lcd_putc, "Apple=%d",ca);
         delay_ms(50);
         }
   }
   else{
      printf(lcd_putc,"\f emergencia");   
      delay_ms(100);
   }
}
   

void main()
{
   port_b_pullups(true);
   enable_interrupts(int_EXT);
   enable_interrupts(int_EXT1);
   enable_interrupts(int_EXT2);
   enable_interrupts(int_RB);
   ext_int_edge(0,H_TO_L);
   ext_int_edge(1, H_TO_L);
   ext_int_edge(2, H_TO_L);   
   enable_interrupts(GLOBAL);   
   lcd_init();
   cp=0;
   cm=0;
   ca=0;
   cf=0;
   conflicto=0;
   parada=0;
   while(1){
      mostrar();
   }
}
