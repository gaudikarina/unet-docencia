#include <16F877.h>
#device adc=10
#use delay (clock=4000000)
#use standard_io(B)
#use i2c(Master,sda=PIN_C4,scl=PIN_C3)
#include<math.h>

int   V;
short estado;
long   Ncad;

void main (){
   delay_ms(1000);
   setup_adc(ADC_CLOCK_DIV_8);
   setup_adc_ports(AN0);
   while(1){
    set_adc_channel(0);
    Ncad=read_adc();
     V=5*Ncad/1024;
    i2c_start();                 //Inicializa la transmisión
       i2c_write(0x10);
    i2c_write(V);
    i2c_stop();
     delay_ms(1000);
   i2c_start();
     i2c_write(0x20);
    i2c_write(V);
     i2c_stop();

 }
}
