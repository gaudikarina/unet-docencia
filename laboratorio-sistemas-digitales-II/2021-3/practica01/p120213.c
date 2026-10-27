#include<18f4550.h>
#fuses XT, NOWDT,CPUDIV1
#use delay(clock=4000000)
#define use_portb_kbd TRUE
#include <kbd_4.c>
#include<hdm64gs12gaudi.c>
#include <graphics.c>
#include <bofa1.h>
#use standard_io(B,D,C)
unsigned long page = 0;
unsigned int8 i,j,m=64;
char T[];
char inicio[]="Selecciona:";
char retirocc[]="1.RetCC";
char retiroca[]="2.RetCA";
char transf[]="3.Trans";
char cambioc[]="4.CambClav";
char saldocc[]= "SaldoCC.5";
char saldoca[]= "SaldoCA.6";
char otransf[]="OTrans.8";
char error[]="CLAVE ERRADA";
char tecla[];
char bofac[];
char men[]="prueba";
short b1;
char r[],d=0,a[]="*";
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
         glcd_writeByte(GLCD_LEFT, bofa1[j+page]);
         glcd_writeByte(GLCD_RIGHT, bofa1[j+page+m]);
        }
        page += 128;  
   }
}
void menu(){
      glcd_text57(30,0,inicio, 1, 1);
      glcd_text57(0,20,retirocc, 1, 1);
      glcd_text57(0,30,retiroca, 1, 1);
      glcd_text57(0,40,transf, 1, 1);
      glcd_text57(0,50,cambioc, 1, 1);
      glcd_text57(70,20,saldocc, 1, 1);
      glcd_text57(70,30,saldoca, 1, 1);
      glcd_text57(74,50,otransf, 1, 1); 
}
short pin(){
      short p1;
      char men1[]="Introduzca PIN";
      char men2[]="finalice con ENTER";
      n=0;
      d=0;
      a="*";
      glcd_fillScreen(OFF);
      glcd_text57(10,20,men1, 1, 1);
      glcd_text57(10,30,men2, 1, 1);
      while((d==0) && (n<=4)){
         d=kbd_getc();        
         if(d!=0 && d!='C'){
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
   char B[];
   port_b_pullups(true);
   glcd_init(ON);
   kbd_init();
   logo();
   delay_ms(500);
   glcd_fillScreen(OFF);
  while(true)
   {
     menu();
     T=0;
     while(T==0){
     T=kbd_getc();
     }
     switch(T){
       case '1':{
       b1=pin();
       men="RETIRO CC";
       break;}
       case '2':{
       b1=pin();
       men="RETIRO CA";
         break;}
       case '3':{
       b1=pin();
       men="TRANSFERENCIA";
       break;  }    
     case '4':{
       b1=pin();
       men="CAMBIAR CLAVE";
      break;}
     case '5':{
       b1=pin();
       men="SALDO CC";
      break;}
     case '6':{
      b1=pin();
      men="SALDO CA";
      break;}
     case '8':{
       b1=pin();
       men="SERVICIOS";
      break;}
    default:{
      b1=pin();
      men="FUNCION NP";
     break; }    
     }
     if (b1==1){
         glcd_fillScreen(OFF);
         glcd_text57(10,20,men, 1, 1);
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
