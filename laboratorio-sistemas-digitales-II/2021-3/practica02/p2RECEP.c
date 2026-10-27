#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device adc=10
#use delay(clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7)
#include <hdm64gs12gau3.c>
#include <graphics.c>
#include <stdio.h>
#include <string.h>
#include <math.h>
char it[44];
char r[]="Sala Remota";
char t[6],h[6],l[6];
int   n,m,k,p;
//const int q=1;
char s[]="T";
char u[]="H";
char v[]="L";
char t1[]="Temp=";
char t2[]="Hum=";
char t3[]="Luz=";
void datos();
#int_RDA
serv_int()
{          

        if(kbhit()){
          gets(it);
         }
        
}
void mostrarlcd(){
      p=strlen(it);
      k=strcspn(it,s);
      n=strcspn(it,u);
      m= strcspn(it,v);  
      strncpy(t,it+1,4);  
      strncpy(h,it+1+n,4);
      strncpy(l,it+1+m,4);
      glcd_text57(30,15,t1, 1, 1);
      glcd_text57(30,35,t2, 1, 1);
      glcd_text57(30,55,t3, 1, 1);
     glcd_text57(65,15,t, 1, 1);
      glcd_text57(65,35,h, 1, 1);
      glcd_text57(65,55,l, 1, 1);
      delay_ms(1000);
      glcd_fillScreen(OFF);      
}

void main() {
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   glcd_init(ON);
   While (1) {
        glcd_text57(30,0,r, 1, 1);    
        mostrarlcd();
      }
}
