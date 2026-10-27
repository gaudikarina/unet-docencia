#include <18F4550.h>
#device  high_ints= TRUE
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#use delay (clock=4000000)
#include <string.h>
#use standard_io(A,B,C,D)
#include <lcd.c>
#include <kbd_pc.c>

int ledrv, i = 1;
short z0 = 0, z1 = 0, z2 = 0, z4 = 0, z5 = 0, z6 = 0, z7 = 0, b4, b5, b6, b7;
short armado = 0;
const char p[4] = "2101";

// IMPORTANTE: tecla[] y r[] deben declararse con tamaño explicito.
// "char tecla[];" (sin tamano) no reserva memoria real y provoca
// que las escrituras tecla[n]=d se salgan del arreglo y corrompan
// variables vecinas (muy probablemente 'n'), haciendo que clave()
// crea que ya recibio 4 digitos sin haber esperado ninguno.
char tecla[4];
char r[4];          // ajustar tamano segun lo que use kbd_pc.c internamente
char d = 0, a[] = "*", T;
int n = 0;

short clave();
void  alarma();
void  desarmar();

#int_EXT
void Interrupcion0()
{
   z0 = 1;
}

#int_RB high
void Puerta_abierta()
{
   b4 = input(PIN_B4);
   b5 = input(PIN_B5);
   b6 = input(PIN_B6);
   b7 = input(PIN_B7);
   if (b4 == 1)
      z4 = 1;
   else if (b5 == 1)
      z5 = 1;
   else if (b6 == 1)
      z6 = 1;
   else if (b7 == 1)
      z7 = 1;
}

#int_EXT1
void Interrupcion1()
{
   z1 = 1;
}

#int_EXT2
void Interrupcion2()
{
   z2 = 1;
}

short clave()
{
   short p1;
   lcd_putc("\f Codigo");
   n = 0;
   d = 0;
   while (n < 4) {
      d = kbd_getc();
      if (d != 0 && d != 'C') {
         tecla[n] = d;
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

void alarma()
{
   while (i < 100) {
      output_high(pin_A0);
      delay_us(125 + i);
      output_low(pin_A0);
      delay_us(125 + i);
      i++;
   }
   i = 1;
}

// ---------------------------------------------------------------
// Rutina de desarmado: deshabilita TODAS las interrupciones externas
// (ahora incluye Zona 0/INT0, que ya no queda encendida por defecto),
// limpia banderas y regresa al estado inicial.
// ---------------------------------------------------------------
void desarmar()
{
   disable_interrupts(int_EXT);      // Zona 0 (INT0)
   disable_interrupts(int_EXT1);     // Zona 1
   disable_interrupts(int_EXT2);     // Zona 2
   disable_interrupts(int_RB);       // Zonas 4-7
   z0 = 0; z1 = 0; z2 = 0; z4 = 0; z5 = 0; z6 = 0; z7 = 0;
   armado = 0;
   output_low(pin_A2);
   output_high(pin_A1);
   lcd_putc("\f Sistema Desarmado");
   delay_ms(500);
}

void main()
{
   port_b_pullups(true);
   kbd_init();
   lcd_init();
   ledrv = 1;

   // Todas las interrupciones externas quedan deshabilitadas hasta armar.
   // (No se llama enable_interrupts(GLOBAL) aqui: se activa recien
   // en el momento del armado, junto con las fuentes individuales.)

   while (1) {

      // ---------------- ESTADO DESARMADO ----------------
      output_high(pin_A1);
      output_low(pin_A2);
      lcd_putc("\f Sistema Desarmado");
      delay_ms(100);
      T=0;
      while(T==0){
      clave();
      }

      if (clave() == 1) {

         // ---------------- TRANSICION A ARMADO ----------------
         // Flanco configurado ANTES de habilitar cada interrupcion,
         // para evitar un disparo espurio con el flanco por defecto.
         ext_int_edge(0, L_TO_H);
         ext_int_edge(1, L_TO_H);
         ext_int_edge(2, L_TO_H);

         enable_interrupts(GLOBAL);
         enable_interrupts(int_EXT);     // Zona 0
         enable_interrupts(int_EXT1);    // Zona 1
         enable_interrupts(int_EXT2);    // Zona 2
         enable_interrupts(int_RB);      // Zonas 4-7

         output_low(pin_A1);
         output_high(pin_A2);
         armado = 1;
         lcd_putc("\f Sistema Armado");
         delay_ms(500);

         // ---------------- ESTADO ARMADO ----------------
         while (armado) {

            if (z0 == 1) { lcd_putc("\f Zona 00"); alarma(); z0 = 0; }
            if (z1 == 1) { lcd_putc("\f Zona 01"); alarma(); z1 = 0; }
            if (z2 == 1) { lcd_putc("\f Zona 02"); alarma(); z2 = 0; }
            if (z4 == 1) { lcd_putc("\f Zona 04"); alarma(); z4 = 0; }
            if (z5 == 1) { lcd_putc("\f Zona 05"); alarma(); z5 = 0; }
            if (z6 == 1) { lcd_putc("\f Zona 06"); alarma(); z6 = 0; }
            if (z7 == 1) { lcd_putc("\f Zona 07"); alarma(); z7 = 0; }

            lcd_putc("\f Sistema Armado");

            if (clave() == 1) {
               desarmar();
            }
         }
      }
   }
}
