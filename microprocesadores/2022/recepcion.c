#include <18F4550.h>
#device high_ints=TRUE
#use delay (internal =4000000)
#use standard_io(A,B,C,D,E)// puertos B,C,D como entradas y salidas
#use rs232(BAUD=9600, XMIT=PIN_C6, RCV=PIN_C7)//configurar EUSART Remoto
#include <stdlib.h>
#include <string.h>
char lee[100],leido[30];
int ban=0;
#int_RDA
void leer()
{

   if(kbhit())
   {
      
      output_high(PIN_C0);
      delay_ms(1000);
      output_low(PIN_C0);//ban=1;
      delay_ms(1000);
 //     gets(lee);
   }
      //clear_interrupt(INT_RDA);
return;
}

void main()
{
char lectura;
enable_interrupts(GLOBAL);
enable_interrupts(INT_RDA);
setup_adc_ports(NO_ANALOGS);
   while(1)
   {  //gets(lee);
      //puts(lee); //Enviar por RC6/TX      
      //printf("Main ON"); //Enviar por RC6/TX
      //delay_ms(1000);
      //lectura=atoi(lee);
      /*for(int i=0;i<24;i++)
      {
      if(lee[i]=="|")
      {
      strncpy(leido[i], lee, 3);
      }
      strncpy(leido, lee, 3);
      }*/
      if(lee!="100|200|300|400|500|600|")
      {
      output_high(PIN_C1);
      }
      else
      {
      output_low(PIN_C1);
      }
   }
return;
}
