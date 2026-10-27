#include <18F4550.h>
#device high_ints=TRUE
#FUSES INTRC_IO, NOPROTECT, NOWDT, NOBROWNOUT, PUT, NOLVP, NOPBADEN
#device adc=10
#use delay(clock=4000000)
#use standard_io(A,B,C,D)
#include <lcd.c>
#include <math.h>


// Canales ADC según el esquema:
// AN0 -> Temperatura (salida acondicionada del AD8495, termopar tipo K)
// AN1 -> Humedad relativa (HIH-5030)
// AN2 -> Nivel (Sharp GP2Y0A21)

float leer_temperatura(void) {
   float temp_c;
   int16 q;
   set_adc_channel(0);
   delay_us(20);              // tiempo de adquisición
//   vout = (float)read_adc() * 5.0 / 1023.0;   // 10 bits, Vref = 5V
   q=read_adc();
   // AD8495: Vout = 1.25V + 0.005 V/°C * Temp
   temp_c=5.0*q/5.115;

   return temp_c;
}

float leer_humedad(void) {
   float vout, humedad;
   set_adc_channel(1);
   delay_us(20);
   vout = (float)read_adc() * 5.0 / 1023.0;

   // HIH-5030 (sin compensación de temperatura): Vout = Vsupply*(0.0062*RH + 0.16)
   humedad = (vout / 5.0 - 0.16) / 0.0062;
   return humedad;
}

float leer_nivel(void) {
   float vout, distancia_cm, nivel_pct;
   set_adc_channel(2);
   delay_us(20);
   vout = (float)read_adc() * 5.0 / 1023.0;

   // Aproximación típica GP2Y0A21 (rango util 10-80 cm)
   if (vout < 0.1) vout = 0.1;   // evita división por valores casi nulos
   distancia_cm = 27.86 * pow(vout, -1.15);

   // Escalado de distancia a nivel de llenado (ajustar según altura real del silo)
   // Ejemplo: 0 cm = silo lleno (100%), 80 cm = silo vacio (0%)
   nivel_pct = 100.0 - (distancia_cm / 80.0) * 100.0;
   if (nivel_pct < 0) nivel_pct = 0;
   if (nivel_pct > 100) nivel_pct = 100;

   return nivel_pct;
}

void main() {
   float temperatura, humedad, nivel;

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_TO_AN2 | VSS_VDD);

   lcd_init();
   lcd_putc('\f');

   while(TRUE) {
      temperatura = leer_temperatura();
      humedad     = leer_humedad();
      nivel       = leer_nivel();

      lcd_gotoxy(1,1);
      printf(lcd_putc, "T:%5.2fC H:%4.1f%%", temperatura, humedad);

      lcd_gotoxy(1,2);
      printf(lcd_putc, "Nivel: %5.1f%%", nivel);

      delay_ms(500);
   }
}
