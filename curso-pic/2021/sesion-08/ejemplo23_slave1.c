 #include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B)
#use i2c(slave,sda=PIN_C4,scl=PIN_C3,address=0x10)

int   dato=0,i=1,j=0,estado;

void alarma(){
   while(i<100){
   output_high(pin_B3);
   delay_us(125+i);
   output_low(pin_B3);
   delay_us(125+i);
   i++;
   }
   i=1;
}
#INT_SSP
serv_int(){
    estado=i2c_isr_state();
    if((estado>0)&&(estado<0x80))
    dato=i2c_read();
   }

void main (){
   enable_interrupts(GLOBAL);
   enable_interrupts(int_ssp);
   output_low(pin_B3);
   delay_us(200);
   while(1){
   if (dato>3) alarma();

}
}
