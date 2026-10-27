#include <18F4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device adc=10
#use delay (clock=4000000)
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,stream=Principal)
#use rs232(baud=9600, xmit=pin_c0, rcv=pin_c1,stream=Monitoreo1)
#use rs232(baud=9600, xmit=pin_d0, rcv=pin_d1,stream=Monitoreo2)
#include <string.h>
#use standard_io(A,B,C,D,E)  
float tt,p[13],f[13]={0,660,962,232,839,420,640,700,327,180,98,64,639};
char a1[6];
int i,j,pulso;
int16 ncad,q;
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
void alarma(){
   while(j<100){
   output_toggle(pin_A4);
   delay_us(125+j);
  
   j++;
   }
   j=1;
}
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
void mostrarserial(){
           fputs("\nSala Principal\n",Principal);
        for (i=1;i<=12;i++){
          if (i<=6){
                fprintf(Monitoreo1,"%1.0f#",p[i]);
                if(i==6){
                  fprintf(Monitoreo1,"\r");}
                }
                else{
                fprintf(Monitoreo2,"%1.0f/",p[i]);
                if(i==12){
                 fprintf(Monitoreo2,"\r");}
                }
          fprintf(Principal,"T[%d]= %1.0f\r\n",i,p[i]);                    
        
        }
}
void main()
{
   setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   while(1){
    leeradc();    
    mostrarserial();
    disable_interrupts(int_timer0);
    while(a[1]==0 && a[2]==0 && a[3]==0 && a[4]==0 && a[5]==0 && a[6]==0 && a[7]==0 && a[8]==0 && a[9]==0 && a[10]==0 && a[11]==0 && a[12]==0){ 
        fprintf(Principal,"%s\n\r",Al);
        leeradc();      
        alarma();        
      }   
    
     }
}



