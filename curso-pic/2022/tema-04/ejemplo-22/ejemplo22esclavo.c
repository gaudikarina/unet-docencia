#include <16F877.h>
#use delay(clock=4000000)
#use i2c(slave,sda=PIN_C4,scl=PIN_C3,address=0x08)          //Configuración I2C
#include <lcd.c>
int estado,dato;

#INT_SSP
serv_int(){
    estado=i2c_isr_state();    
 if(estado==0)
   {
      dato=i2c_read();
   }
    if((estado>0)&&(estado<0x80))
   {   
    dato=i2c_read();
    }
}
void main() {
   enable_interrupts(int_ssp);
    enable_interrupts(GLOBAL);     
    lcd_init();
    while(1){
     printf(lcd_putc,"\frecibo I2C=%u",dato);
     delay_ms(100); 
    }

      
 }
