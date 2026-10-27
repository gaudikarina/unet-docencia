#include <18f4550.h>
#fuses HSPLL,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#device adc=10
#use delay(clock=48000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#include <hdm64gs12gau3.c>
#include <graphics.c>
#include <stdlib.h>
int16 q;
float p;
char voltios[5];
char text[]="Recibido";
int j=0;//indice buffer
int const buff=4;
char dato=0x00;
char t3[]="ADC=";
char t4[]="Vol=";
char it[buff];//buffer recepcion datos
//Funciones
void adicionar(char c);// funcion adicionar caracter al buffer

#int_RDA
serv_int()
{
//!        dato=0x00;
//!        if(kbhit()){
//!          dato=getchar();
//!          adicionar(dato);
//!         }         
//!}
//!
//!void adicionar(char c){                  // Añade a buffer
//!               it[j++]=c;          // Añade caracter recibido al Buffer
//!      }
q=getc();
  }

void main() {

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
    glcd_init(ON);
   
   While (1) {
   j=0;
  // q=atol(it);  
   p = 5.0 * q/ 1024.0; 
   glcd_text57(76,5,text, 1, 1);
   glcd_text57(75,15,t3, 1, 1);
   sprintf(it,"%ld",q);  
   glcd_text57(100,15,it, 1, 1);
   glcd_text57(75,25,t4, 1, 1);
   sprintf(voltios,"%1.2f", p); 
   glcd_text57(100,25,voltios, 1, 1);
   delay_ms(500);
   glcd_text57(76,5,text, 1, 0);
   glcd_text57(75,15,t3, 1, 0);
   glcd_text57(100,15,it, 1, 0);
   glcd_text57(75,25,t4, 1, 0);
   glcd_text57(100,25,voltios, 1, 0);
   glcd_fillScreen(OFF);
   delay_ms(100);
      }
}

