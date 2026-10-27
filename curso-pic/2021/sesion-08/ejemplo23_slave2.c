#include <16F877.h>
#use delay(clock=4000000)
#use i2c(slave,sda=PIN_C4,scl=PIN_C3,address=0x20)          //Configuración I2C
#include <lcd.c>

int estado,dato1;

  
#INT_SSP
serv_int(){
	 estado=i2c_isr_state();
	 if((estado>0)&&(estado<0x80))
	 dato1=i2c_read();
	 }
void main() {
 	enable_interrupts(GLOBAL);
  	enable_interrupts(int_ssp);
    lcd_init();
	printf(lcd_putc,"\fesperando",dato1);
	while(1){
	
	if (dato1>3)	 printf(lcd_putc,"\fALARMA V> %U",dato1);
   	else  printf(lcd_putc,"\fNormal V= %U",dato1);
	delay_ms(100);
	}
}