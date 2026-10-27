#include <16F877.h>
#use delay(clock=4000000)
#use i2c(slave,sda=PIN_C4,scl=PIN_C3,address=0x10)          //Configuración I2C
#include <lcd.c>

int estado,dato,dato1;
short i;
  
#INT_SSP
serv_int(){
	 estado=i2c_isr_state();
	 if((estado>0)&&(estado<0x80))
   {	
	 dato=i2c_read(0);
	 printf(lcd_putc,"\freci SLV1=%u",dato);
     delay_ms(500); 
	 }
}
void main() {
 	enable_interrupts(GLOBAL);
  	enable_interrupts(int_ssp);
    lcd_init();
	while(1);

		
 }
