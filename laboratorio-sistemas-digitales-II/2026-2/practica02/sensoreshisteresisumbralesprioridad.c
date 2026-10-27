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

// Pines de indicadores (según Distribución Física de Conexiones)
#define LED_TEMP   PIN_B0
#define LED_HUM    PIN_B1
#define LED_NIVEL  PIN_B2
#define BUZZER     PIN_B3

// Umbrales de alerta y bandas de histéresis
#define TEMP_UMBRAL    40.0
#define TEMP_HIST       2.0
#define HUM_UMBRAL     70.0
#define HUM_HIST        3.0
#define NIVEL_UMBRAL   85.0
#define NIVEL_HIST      3.0

// Estados de alarma (con memoria, para aplicar histéresis)
int1 alarma_temp  = FALSE;
int1 alarma_hum   = FALSE;
int1 alarma_nivel = FALSE;

float leer_temperatura(void) {
   float temp_c;
   int16 q;
   set_adc_channel(0);
   delay_us(20);              // tiempo de adquisición
   q = read_adc();
   // AD8495: Vout = 1.25V + 0.005 V/°C * Temp
   temp_c = 5.0 * q / 5.115;

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
   nivel_pct = 100.0 - (distancia_cm / 80.0) * 100.0;
   if (nivel_pct < 0) nivel_pct = 0;
   if (nivel_pct > 100) nivel_pct = 100;

   return nivel_pct;
}

// Actualiza el estado de cada alarma aplicando histéresis:
// se activa al superar el umbral, y solo se desactiva al bajar
// del umbral menos la banda de histéresis (evita parpadeo).
void evaluar_alarmas(float temperatura, float humedad, float nivel) {

   if (!alarma_temp && temperatura > TEMP_UMBRAL)
      alarma_temp = TRUE;
   else if (alarma_temp && temperatura < (TEMP_UMBRAL - TEMP_HIST))
      alarma_temp = FALSE;

   if (!alarma_hum && humedad > HUM_UMBRAL)
      alarma_hum = TRUE;
   else if (alarma_hum && humedad < (HUM_UMBRAL - HUM_HIST))
      alarma_hum = FALSE;

   if (!alarma_nivel && nivel > NIVEL_UMBRAL)
      alarma_nivel = TRUE;
   else if (alarma_nivel && nivel < (NIVEL_UMBRAL - NIVEL_HIST))
      alarma_nivel = FALSE;

   // Zumbador general: activo mientras exista al menos una alarma activa
   output_bit(BUZZER, alarma_temp || alarma_hum || alarma_nivel);
}

void main() {
   float temperatura, humedad, nivel;
   int8 prioridad;

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_TO_AN2 | VSS_VDD);

   output_low(LED_TEMP);
   output_low(LED_HUM);
   output_low(LED_NIVEL);
   output_low(BUZZER);

   lcd_init();
   lcd_putc('\f');

   while(TRUE) {
      temperatura = leer_temperatura();
      humedad     = leer_humedad();
      nivel       = leer_nivel();

      evaluar_alarmas(temperatura, humedad, nivel);

      // Cada LED refleja el estado individual de su propia variable
      output_bit(LED_TEMP,  alarma_temp);
      output_bit(LED_HUM,   alarma_hum);
      output_bit(LED_NIVEL, alarma_nivel);

      // Lógica de prioridad: cuando hay dos o más alarmas activas
      // al mismo tiempo, se resuelve el conflicto en este orden:
      // 1) Temperatura  2) Humedad  3) Nivel
      if (alarma_temp)
         prioridad = 1;
      else if (alarma_hum)
         prioridad = 2;
      else if (alarma_nivel)
         prioridad = 3;
      else
         prioridad = 0;

      // El buzzer general suena mientras exista alguna alarma activa
      output_bit(BUZZER, prioridad != 0);

      lcd_gotoxy(1,1);
      printf(lcd_putc, "T:%5.2fC H:%4.1f%%", temperatura, humedad);

      lcd_gotoxy(1,2);
      switch(prioridad) {
         case 1:
            printf(lcd_putc, "ALERTA: TEMP ALTA ");
            break;
         case 2:
            printf(lcd_putc, "ALERTA: HUMEDAD ALTA");
            break;
         case 3:
            printf(lcd_putc, "ALERTA: NIVEL ALTO ");
            break;
         default:
            printf(lcd_putc, "Nivel: %5.1f%%    ", nivel);
            break;
      }

      delay_ms(500);
   }
}
