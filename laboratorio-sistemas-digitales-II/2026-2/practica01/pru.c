#include <18F4550.h>
#device  high_ints= TRUE
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#use delay(clock=4000000)
#use standard_io(A,B,C,D)
#include <lcd.c>

short z0=0, z1=0, z2=0, z4=0, z5=0, z6=0, z7=0, b4, b5, b6, b7;

#int_EXT
void Interrupcion0(){ z0 = 1; }

#int_RB high
void Puerta_abierta(){
   b4 = input(PIN_B4);
   b5 = input(PIN_B5);
   b6 = input(PIN_B6);
   b7 = input(PIN_B7);
   if (b4 == 0) z4 = 1;
   else if (b5 == 0) z5 = 1;
   else if (b6 == 0) z6 = 1;
   else if (b7 == 0) z7 = 1;
}

#int_EXT1
void Interrupcion1(){ z1 = 1; }

#int_EXT2
void Interrupcion2(){ z2 = 1; }

void main(){
   lcd_init();
   port_b_pullups(true);

   ext_int_edge(0, H_TO_L);
   ext_int_edge(1, H_TO_L);
   ext_int_edge(2, H_TO_L);

   // Lectura de referencia de RB4-RB7 ANTES de habilitar int_RB:
   // el periferico compara futuros cambios contra esta "foto" inicial.
   // Sin esto, el primer disparo puede ser espurio (falso positivo).
   b4 = input(PIN_B4);
   b5 = input(PIN_B5);
   b6 = input(PIN_B6);
   b7 = input(PIN_B7);
   clear_interrupt(int_RB);

   enable_interrupts(GLOBAL);
   enable_interrupts(int_EXT);
   enable_interrupts(int_EXT1);
   enable_interrupts(int_EXT2);
   enable_interrupts(int_RB);

   lcd_putc("\fEsperando zona...");

   while(1){
      if (z0 == 1) { lcd_putc("\fZona 0 !!"); z0 = 0; delay_ms(1500); lcd_putc("\fEsperando zona..."); }
      if (z1 == 1) { lcd_putc("\fZona 1 !!"); z1 = 0; delay_ms(1500); lcd_putc("\fEsperando zona..."); }
      if (z2 == 1) { lcd_putc("\fZona 2 !!"); z2 = 0; delay_ms(1500); lcd_putc("\fEsperando zona..."); }
      if (z4 == 1) { lcd_putc("\fZona 4 !!"); z4 = 0; delay_ms(1500); lcd_putc("\fEsperando zona..."); }
      if (z5 == 1) { lcd_putc("\fZona 5 !!"); z5 = 0; delay_ms(1500); lcd_putc("\fEsperando zona..."); }
      if (z6 == 1) { lcd_putc("\fZona 6 !!"); z6 = 0; delay_ms(1500); lcd_putc("\fEsperando zona..."); }
      if (z7 == 1) { lcd_putc("\fZona 7 !!"); z7 = 0; delay_ms(1500); lcd_putc("\fEsperando zona..."); }
   }
}
