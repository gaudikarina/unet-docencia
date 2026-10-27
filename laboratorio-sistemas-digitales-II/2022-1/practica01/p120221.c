#include<18f4550.h>
#fuses XT, NOWDT,CPUDIV1
#use delay(clock=4000000)
#define use_portb_kbd TRUE
#include <kbd_4.c>
#include<hdm64gs12gaudi.c>
#include <graphics.c>
#include <teleg.h>
#include <digitel.h>
#include <pantalla.h>
#include <chatw.h>
#include <smsm.h>
#include <contac.h>
#use standard_io(B,D,C)
unsigned long page = 0;
unsigned int8 i,j,m=64;
int l=0;
char T[];
char tecla[];
char men[]="prueba";
char error[]="CLAVE ERRADA";
short b1;
char d=0,a[]="*";
int n=0;
const char p[4]="2101";
void logo(){
for(i = 0; i < 8; ++i){
        output_low(GLCD_DI);                      // Modo comando
        glcd_writeByte(GLCD_LEFT, 0b01000000);    // 0x40 hasta 0x7F (posicion del cursor por pagina 0-63)
        glcd_writeByte(GLCD_RIGHT, 0b01000000);
        glcd_writeByte(GLCD_LEFT, i | 0b10111000);// Escoje la direccion de la pagina
        glcd_writeByte(GLCD_RIGHT, i | 0b10111000);
        output_high(GLCD_DI);  
        for(j=0; j<64; j++){
         glcd_writeByte(GLCD_LEFT,digitel[j+page]);
         glcd_writeByte(GLCD_RIGHT,digitel[j+page+m]);
        }
        page += 128;  
   }
}
void menu(){
page=0;
m=64;
for(i = 0; i < 8; ++i){
        output_low(GLCD_DI);                      // Modo comando
        glcd_writeByte(GLCD_LEFT, 0b01000000);    // 0x40 hasta 0x7F (posicion del cursor por pagina 0-63)
        glcd_writeByte(GLCD_RIGHT, 0b01000000);
        glcd_writeByte(GLCD_LEFT, i | 0b10111000);// Escoje la direccion de la pagina
        glcd_writeByte(GLCD_RIGHT, i | 0b10111000);
        output_high(GLCD_DI);  
        for(j=0; j<64; j++){
         glcd_writeByte(GLCD_LEFT,pantalla[j+page]);
         glcd_writeByte(GLCD_RIGHT,pantalla[j+page+m]);
        }
        page += 128;  
   }
}
void whatsapp(){
page=0;
m=64;
for(i = 0; i < 8; ++i){
        output_low(GLCD_DI);                      // Modo comando
        glcd_writeByte(GLCD_LEFT, 0b01000000);    // 0x40 hasta 0x7F (posicion del cursor por pagina 0-63)
        glcd_writeByte(GLCD_RIGHT, 0b01000000);
        glcd_writeByte(GLCD_LEFT, i | 0b10111000);// Escoje la direccion de la pagina
        glcd_writeByte(GLCD_RIGHT, i | 0b10111000);
        output_high(GLCD_DI);  
        for(j=0; j<64; j++){
         glcd_writeByte(GLCD_LEFT,chatw[j+page]);
         glcd_writeByte(GLCD_RIGHT,chatw[j+page+m]);
        }
        page += 128;  
   }
}
void telegram(){
page=0;
m=64;
for(i = 0; i < 8; ++i){
        output_low(GLCD_DI);                      // Modo comando
        glcd_writeByte(GLCD_LEFT, 0b01000000);    // 0x40 hasta 0x7F (posicion del cursor por pagina 0-63)
        glcd_writeByte(GLCD_RIGHT, 0b01000000);
        glcd_writeByte(GLCD_LEFT, i | 0b10111000);// Escoje la direccion de la pagina
        glcd_writeByte(GLCD_RIGHT, i | 0b10111000);
        output_high(GLCD_DI);  
        for(j=0; j<64; j++){
         glcd_writeByte(GLCD_LEFT,teleg[j+page]);
         glcd_writeByte(GLCD_RIGHT,teleg[j+page+m]);
        }
        page += 128;  
   }
}
void sms(){
page=0;
m=64;
for(i = 0; i < 8; ++i){
        output_low(GLCD_DI);                      // Modo comando
        glcd_writeByte(GLCD_LEFT, 0b01000000);    // 0x40 hasta 0x7F (posicion del cursor por pagina 0-63)
        glcd_writeByte(GLCD_RIGHT, 0b01000000);
        glcd_writeByte(GLCD_LEFT, i | 0b10111000);// Escoje la direccion de la pagina
        glcd_writeByte(GLCD_RIGHT, i | 0b10111000);
        output_high(GLCD_DI);  
        for(j=0; j<64; j++){
         glcd_writeByte(GLCD_LEFT,smsm[j+page]);
         glcd_writeByte(GLCD_RIGHT,smsm[j+page+m]);
        }
        page += 128;  
   }
}
void agenda(){
page=0;
m=64;
for(i = 0; i < 8; ++i){
        output_low(GLCD_DI);                      // Modo comando
        glcd_writeByte(GLCD_LEFT, 0b01000000);    // 0x40 hasta 0x7F (posicion del cursor por pagina 0-63)
        glcd_writeByte(GLCD_RIGHT, 0b01000000);
        glcd_writeByte(GLCD_LEFT, i | 0b10111000);// Escoje la direccion de la pagina
        glcd_writeByte(GLCD_RIGHT, i | 0b10111000);
        output_high(GLCD_DI);  
        for(j=0; j<64; j++){
         glcd_writeByte(GLCD_LEFT,contac[j+page]);
         glcd_writeByte(GLCD_RIGHT,contac[j+page+m]);
        }
        page += 128;  
   }
}
short pin(){
      short p1;
      char men1[]="Introduzca PIN";
      n=0;
      d=0;
      a="*";
      glcd_fillScreen(OFF);
      glcd_text57(10,20,men1, 1, 1);
  //    glcd_text57(10,30,men2, 1, 1);
      while((d==0) && (n<4)){
         d=kbd_getc();        
         if(d!=0 ){
//!            sprintf(r,"%c",d);
//!            glcd_text57(10+5*n,40,r, 1, 1);
            glcd_text57(42+5*n,40,a, 1, 1);
               tecla[n]=d;
               n++;
               d=0;
            }
           }
     if((tecla[1]==p[1])&&(tecla[2]==p[2])&&(tecla[3]==p[3])&&(tecla[0]==p[0]))
       p1=1;       
       else
       p1=0;
      return(p1); 
}
void main(){
   port_b_pullups(true);
   glcd_init(ON);
   kbd_init();
   logo();
   delay_ms(1500);
   glcd_fillScreen(OFF);
  while(true)
   {
     menu();
     T=0;
     while(T==0){
     T=kbd_getc();
     }
     switch(T){
       case 'W':{
       b1=pin();
       l=1;
       break;}
       case 'T':{
       b1=pin();
       l=2;
         break;}
       case 'A':{
       b1=pin();
       l=3;
       break;  }    
     case 'S':{
       b1=pin();
       l=4;
      break;}
      case ('1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9'||'*'||'#'):{
      men="Funcion No Permitida";
     break; }    
     }
     if (b1==1){
         glcd_fillScreen(OFF);
         switch (l){
         case 1: whatsapp();break;
         case 2: telegram();break;
         case 3: agenda();break;
         case 4: sms();break;
         default: glcd_text57(10,20,men, 1, 1); break;
         }
         delay_ms(1000);  
         glcd_fillScreen(OFF);
      }
      else {
         glcd_fillScreen(OFF);
         glcd_text57(10,20,error, 1, 1);
         delay_ms(1000); 
         glcd_fillScreen(OFF);
         
      }  
    }
}
