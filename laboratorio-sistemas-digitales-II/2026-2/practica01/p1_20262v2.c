#include <18F4550.h>
#device  high_ints= TRUE
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#use delay(clock=4000000)
#use standard_io(A,B,C,D)
#include <lcd.c>
#include "kbd_pc.c"

const char p[4] = "2101";
char tecla[4];
char d = 0;
int n = 0;
int i = 1;

short z0=0, z1=0, z2=0, z4=0, z5=0, z6=0, z7=0, b4, b5, b6, b7;

short clave();
void  alarma();

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

// clave(): bloqueante. Se usa SOLO en estado Desarmado, donde no hay
// zonas que vigilar (las interrupciones estan deshabilitadas alli).
short clave(){
   short p1;
   n = 0;
   d = 0;
   while (n < 4) {
      d = kbd_getc();
      if (d != 0 && d != 'C') {
         if (n == 0) lcd_putc("\fCodigo");
         tecla[n] = d;
         lcd_gotoxy(1 + n, 2);
         lcd_putc('*');
         n++;
         d = 0;
      }
   }
   if ((tecla[0] == p[0]) && (tecla[1] == p[1]) &&
       (tecla[2] == p[2]) && (tecla[3] == p[3]))
      p1 = 1;
   else
      p1 = 0;
   return (p1);
}

void alarma(){
   while (i < 100) {
      output_high(pin_A0);
      delay_us(125 + i);
      output_low(pin_A0);
      delay_us(125 + i);
      i++;
   }
   i = 1;
}

void main(){
   short prompt_mostrado;
   short alarma_activa;
   int8  zona_disp;
   int8  zona_last_mostrada;

   lcd_init();
   kbd_init();
   port_b_pullups(true);

   while (1) {

      // ---------------- ESTADO DESARMADO ----------------
      output_high(pin_A1);
      output_low(pin_A2);
      lcd_putc("\fSistema Desarmado");
      lcd_gotoxy(1,2);
      lcd_putc("Codigo");

      if (clave() == 1) {

         // ---------------- TRANSICION A ARMADO ----------------
         ext_int_edge(0, H_TO_L);
         ext_int_edge(1, H_TO_L);
         ext_int_edge(2, H_TO_L);

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

         output_low(pin_A1);
         output_high(pin_A2);

         // ---------------- ESTADO ARMADO ----------------
         n = 0;
         prompt_mostrado = 0;
         alarma_activa = 0;
         zona_disp = 255;
         zona_last_mostrada = 255;

         while (1) {

            if (z0 == 1) { zona_disp = 0; alarma_activa = 1; z0 = 0; }
            if (z1 == 1) { zona_disp = 1; alarma_activa = 1; z1 = 0; }
            if (z2 == 1) { zona_disp = 2; alarma_activa = 1; z2 = 0; }
            if (z4 == 1) { zona_disp = 4; alarma_activa = 1; z4 = 0; }
            if (z5 == 1) { zona_disp = 5; alarma_activa = 1; z5 = 0; }
            if (z6 == 1) { zona_disp = 6; alarma_activa = 1; z6 = 0; }
            if (z7 == 1) { zona_disp = 7; alarma_activa = 1; z7 = 0; }

            if (alarma_activa) {
               // Solo redibuja si la zona mostrada cambio (evita parpadeo)
               if (n == 0 && zona_disp != zona_last_mostrada) {
                  lcd_putc("\fZona ");
                  lcd_putc(zona_disp + '0');
                  lcd_gotoxy(1,2);
                  lcd_putc("Codigo");
                  zona_last_mostrada = zona_disp;
               }
               alarma();          // pulso de sirena; llamado cada vuelta -> suena de forma continua
               prompt_mostrado = 0;
            } else {
               if (n == 0 && !prompt_mostrado) {
                  lcd_putc("\fSistema Armado");
                  lcd_gotoxy(1,2);
                  lcd_putc("Codigo");
                  prompt_mostrado = 1;
               }
            }

            d = kbd_getc();
            if (d != 0 && d != 'C') {
               if (n == 0) {
                  lcd_putc("\fCodigo");
               }
               tecla[n] = d;
               lcd_gotoxy(1 + n, 2);
               lcd_putc('*');
               n++;

               if (n == 4) {
                  if ((tecla[0] == p[0]) && (tecla[1] == p[1]) &&
                      (tecla[2] == p[2]) && (tecla[3] == p[3])) {
                     // ---------------- TRANSICION A DESARMADO ----------------
                     disable_interrupts(int_EXT);
                     disable_interrupts(int_EXT1);
                     disable_interrupts(int_EXT2);
                     disable_interrupts(int_RB);
                     z0=0; z1=0; z2=0; z4=0; z5=0; z6=0; z7=0;
                     break;
                  } else {
                     lcd_putc("\fCodigo Incorrecto");
                     n = 0;
                     prompt_mostrado = 0;
                     zona_last_mostrada = 255;   // fuerza redibujar la zona si la alarma sigue activa
                  }
               }
            }
         }

      } else {
         lcd_putc("\fCodigo Incorrecto");
      }
   }
}
