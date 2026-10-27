#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device adc=10
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,stream=Remoto)
#use rs232(baud=9600, xmit=pin_b0, rcv=pin_b1,stream=Monitoreo)
//#use standard_io(C)
#include <hdm64gs12gau3.c>
#include <graphics.c>
char a1[6];
char a2[6];
char a3[6];
int16 q1,q2,q3;
float p1,p2,p3;
char t1[]="Temp=";
char t2[]="Hum=";
char t3[]="Luz=";
char h[]="Habitacion";
void mostrarlcd(){
      glcd_text57(30,15,t1, 1, 1);
      glcd_text57(30,35,t2, 1, 1);
      glcd_text57(30,55,t3, 1, 1);
      sprintf(a1,"%3.2f",p1);  
      sprintf(a2,"%3.2f",p2);  
      sprintf(a3,"%3.2f",p3);
      glcd_text57(65,15,a1, 1, 1);
      glcd_text57(65,35,a2, 1, 1);
      glcd_text57(65,55,a3, 1, 1);
      delay_ms(1000);
      glcd_fillScreen(OFF);      
}
void enviarserial(){
         fprintf(Monitoreo,"Sala Monitoreo\r");
         fprintf(Monitoreo,"Temp=%1.2f\r",p1);
         fprintf(Monitoreo,"Hum=%1.2f\r",p2);
         fprintf(Monitoreo,"Luz=%1.2f\r",p3);
         fprintf(Remoto,"T%3.2fH%3.2fL%3.2f\r",p1,p2,p3); 
}
void main() {
   setup_adc_ports(AN0_TO_AN2);
   setup_adc(ADC_CLOCK_INTERNAL);
   glcd_init(ON);
   While (1) {
      glcd_text57(30,0,h, 1, 1);
      set_adc_channel(0);
      q1 = read_adc();
      set_adc_channel(1);
      q2 = read_adc();
      set_adc_channel(2);
      q3 = read_adc();
      p1= 5.0 * q1 / 1024.0;
      p2= 5.0 * q2 / 1024.0;
      p3= 5.0 * q3 / 1024.0;      
      enviarserial();
      mostrarlcd();
     }
}
