#include <18f4550.h>
#fuses HSPLL,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN//definición de fusibles de configuración
#use delay(clock=2000000)
//!#use standard_io(B)
#use standard_io(C)
//!#define lcd_data_port getenv("sfr:portd")
//!#define lcd_enable_pin pin_d0
//!#define lcd_rs_pin pin_d1
//!#define lcd_rw_pin pin_d2
//#define use_portb_kbd TRUE
//!#include <hdm64gs12gau.c>
//!#include <graphics.c>
#include <glcd1.c>
#include <kbd_4.c>
//#include <kbd4x4.c>

void main()
{
   char k;
   char text[]="Prueba";
   char tecla[]="Tecla:";
   char it[2];
   int x;
   port_b_pullups(true);
   glcd_init(ON);
   kbd_init();
   glcd_text57(30,5,text, 1, 1);
   delay_ms(500);
   glcd_text57(30,5,text, 1, 0); 
   while(true)
   {
     k=kbd_getc();
      if (k!=0)
      {
        glcd_text57(30,5,tecla, 1, 0); 
        glcd_text57(76,5,it, 1, 0);
        glcd_text57(30,5,tecla, 1, 1);
        sprintf(it,"%c",k);
       glcd_text57(76,5,it, 1, 1);       
      }
   }
   
}
