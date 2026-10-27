#include<16f877.h>
#use delay(clock=4M)
#use standard_io(B)
#include <lcd.c>
int b7;
#INT_RB
void serv_int(){
   b7=input_state(PIN_B7);
   if (b7==1){
       lcd_gotoxy(1,1);
       printf(lcd_putc,"Flanco de Subida");}
   else{
       lcd_gotoxy(1,1);
       printf(lcd_putc,"Flanco de Bajada");}
}
void main(){
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   port_b_pullups(1);
   lcd_init();
   while(1);
}
