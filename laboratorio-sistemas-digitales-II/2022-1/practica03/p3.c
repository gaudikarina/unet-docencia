#include <18F4550.h>
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#device adc=10
#use delay (clock=4000000)
#include<hdm64gs12gaudi.c>
#include <graphics.c>
#include <string.h>
#use standard_io(A,B,C,D,E)  
float tt,p[13],f[13]={0,0,0,0,0,0,0,0,0,180,98,64,639};
char a1[6];
int i;
int16 ncad,q,j;
short a[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
char T[]="TEMPERATURA CELSIUS";
char Al[]="ALARMA";
char T1[]="Al=";
char T2[]="Ag=";
char T3[]="Sn=";
char T4[]="Ca=";
char T5[]="Zn=";
char T6[]="Pu=";
char T7[]="Ra=";
char T8[]="Pb=";
char T9[]="Li=";
char T10[]="Na=";
char T11[]="K=";
char T12[]="Mg=";
void leeradc(){
      for (i=1;i<=12;i++){
           set_adc_channel(i-1);
           q=read_adc();
           p[i]=5.0*q/5.115;
           if(p[i]<f[i])
               a[i]=1; 
           else
               a[i]=0; 
      } 
}
void mostrarlcd(){
         glcd_text57(3,0,T, 1, 1);
      glcd_text57(0,15,T1, 1, 1);
      glcd_text57(0,35,T2, 1, 1);
      glcd_text57(0,55,T3, 1, 1);
      glcd_text57(64,15,T4, 1, 1);
      glcd_text57(64,35,T5, 1, 1);
      glcd_text57(64,55,T6, 1, 1);
      for (i=1;i<=3;i++){           
           if(a[i]==1){
             sprintf(a1,"%1.0f",p[i]);     }        
           else{
            a1="FUS";}a1="FUS";
           glcd_text57(18,15+20*(i-1),a1, 1, 1);
      } 
      for (i=4;i<=6;i++){           
           if(a[i]==1){
             sprintf(a1,"%1.0f",p[i]);  }           
           else{
            a1="FUS";}
           glcd_text57(82,15+20*(i-4),a1, 1, 1);
      } 
      delay_ms(500);
      glcd_fillScreen(OFF);             
      glcd_text57(3,0,T, 1, 1);      
      glcd_text57(0,15,T7, 1, 1);
      glcd_text57(0,35,T8, 1, 1);
      glcd_text57(0,55,T9, 1, 1);
      glcd_text57(64,15,T10, 1, 1);
      glcd_text57(64,35,T11, 1, 1);
      glcd_text57(64,55,T12, 1, 1);
      for (i=7;i<=9;i++){           
           if(a[i]==1){
             sprintf(a1,"%1.0f",p[i]);   }          
           else{
            a1="FUS";}
           glcd_text57(18,15+20*(i-7),a1, 1, 1);
      } 
      for (i=10;i<=12;i++){           
           if(a[i]==1){
             sprintf(a1,"%1.0f",p[i]);      }       
           else{
            a1="FUS";}
           glcd_text57(82,15+20*(i-10),a1, 1, 1);
      } 
      delay_ms(500);
      glcd_fillScreen(OFF); 
}
void main()
{
   setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   j=0;
   glcd_init(ON);
   while(1){
    leeradc();
    mostrarlcd();
    while(a[1]==0 && a[2]==0 && a[3]==0 && a[4]==0 && a[5]==0 && a[6]==0 && a[7]==0 && a[8]==0 && a[9]==0 && a[10]==0 && a[11]==0 && a[12]==0){ 
        glcd_text57(30,25,Al, 2, 1);
        leeradc();
      }   
      glcd_fillScreen(OFF); 
     }
}



