#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,D)
#include <lcd.c>
#INT_EXT
void ser_int(void){
         printf(lcd_putc,"\f");
         lcd_gotoxy(5,1);
         printf(lcd_putc,"Activado");
         delay_ms(1000);
         printf(lcd_putc,"\f");
}
int i;

void main(){
     lcd_init();
     enable_interrupts(INT_EXT);
     enable_interrupts(GLOBAL);
     port_b_pullups(1);
     ext_int_edge( L_TO_H );    
   while(1){
       lcd_gotoxy(3,1);
       printf(lcd_putc,"ESPERANDO...");
         }
}
