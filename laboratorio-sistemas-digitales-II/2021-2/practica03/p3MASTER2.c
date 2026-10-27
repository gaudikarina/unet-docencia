#include <18f4550.h>
#fuses HSPLL,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#device adc=10
#use delay(clock=48000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#use standard_io(C)
#include <hdm64gs12gau3.c>
#include <graphics.c>
void main() {
   char it[4];
   int16 q;
   float p;
   char voltios[5];
   char t3[]="ADC=";
   char t4[]="Vol=";
   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(0);
   glcd_init(ON);
   While (1) {
      q = read_adc();
      p = 5.0 * q / 1024.0;
      glcd_text57(75,3,t3, 1, 1);
      sprintf(it,"%ld",q);  
      glcd_text57(100,3,it, 1, 1);
      glcd_text57(75,13,t4, 1, 1);
      sprintf(voltios,"%1.2f", p); 
      glcd_text57(100,13,voltios, 1, 1);
//!      glcd_text57(76,8,text2, 1, 1); 
//!      glcd_text57(76,8,text3, 1, 1); 
//!      printf("********************************************\r");
//!      printf("        ");
     // printf("  Nro Digital ADC = %4ld ", q);
//!      printf("Voltaje = %01.2fV\r", p);  // El \r permite cambiar de línea.
//!      sprintf(it,"%c",q);  
      puts(it);
      delay_ms(500);
      glcd_text57(75,3,t3, 1, 0);
      glcd_text57(100,3,it, 1, 0);
      glcd_text57(75,13,t4, 1, 0);
      glcd_text57(100,13,voltios, 1, 0);
      }
}
