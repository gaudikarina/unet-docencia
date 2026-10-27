#include <16F877.h>
#use delay(clock=4000000)
#use i2c(Master,sda=PIN_C4,scl=PIN_C3)          //Configuración I2C
#include <lcd.c>
int i,valor;
  
void main() {
    lcd_init();
    for (i=1;i<=10;i++){
      i2c_start();                 //Inicializa la transmisión
      i2c_write(0x10);           
      i2c_write(i);              //Dato a escribir
      i2c_stop();                     //Finalización de la transmisión.
      printf(lcd_putc,"\fEnviando I2C=%u",i);
      delay_ms(500);
     }
}
