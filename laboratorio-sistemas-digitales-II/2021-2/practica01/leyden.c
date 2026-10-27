//!#include<18f4550.h>
//!#fuses HS,NOWDT,NOPROTECT,NOLVP
//!#use delay(clock=4M)
//!#include<stdio.h>
//!#include<kbd4x4_1.c>
//!#include<hdm64gs12m.c>
//!#include<graphics.c>
//!#define use_portb_kbd
#include <18f4550.h>
#fuses NOWDT,NOPROTECT,NOLVP,NOCPD,NOBROWNOUT,NOPUT,NOMCLR,NODEBUG,HS,NOPBADEN
#use delay(clock=2000000)
//!#use standard_io(B)
#use standard_io(C)
//!#define lcd_data_port getenv("sfr:portd")
//!#define lcd_enable_pin pin_d0
//!#define lcd_rs_pin pin_d1
//!#define lcd_rw_pin pin_d2
#define use_portb_kbd TRUE
#include <hdm64gs12gau.c>
#include <graphics.c>
#include <kbd_4.c>
void configurar(){
   kbd_init();
   glcd_init(1);
   return;
}
void main(){
   char P[8]="Verisur", Cu[7]="a12345",a[]="Ingrese Clave",clv[6],Clvs[3][6]={{1,2,2,4,5,3},
                                                                                  {2,1,8,1,0,3},
                                                                                  {5,7,2,0,0,5}};
   int i=0;
   char s[]="*",k;
   char it[2];
   configurar();
   //port_b_pullups(0xFF);
   glcd_text57(45,0,P,1,1);
   glcd_text57(0,9,a,1,1);
      i=0;
         do{
            k=kbd_getc();
            if(k!=0){
                
                //for(i=0;i<6;i++){
                clv[i]=k;
                // if(k!=0){
                glcd_text57(i,18,s,1,1);
                
                //}
                // }
                sprintf(it,"%c",k);
                glcd_text57(i,30,it, 1, 1); 
               // glcd_text57(i,30,clv[i],1,1);
                i++;
                //delay_ms(200);
            }
            
            
         
         
         
         
         
         }while(true);

}
