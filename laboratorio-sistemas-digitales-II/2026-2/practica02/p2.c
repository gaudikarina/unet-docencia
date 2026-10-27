#include <18F4550.h>
#device high_ints=TRUE
#FUSES INTRC_IO, NOPROTECT, NOWDT, NOBROWNOUT, PUT, NOLVP, NOPBADEN
#device adc=10
#use delay(clock=4000000)
#use standard_io(A,B,C,D)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, ERRORS)
#include <lcd.c>
#include <tones_mod.c>
#include <math.h>
#include <string.h>

// Pines de indicadores y actuador
#define LED_TEMP    PIN_B0
#define LED_HUM     PIN_B1
#define LED_NIVEL   PIN_B2
#define BUZZER      PIN_B3
#define ACTUADOR    PIN_B4

// Umbrales de alerta y bandas de histéresis
#define TEMP_UMBRAL    40.0
#define TEMP_HIST       2.0
#define HUM_UMBRAL     70.0
#define HUM_HIST        3.0
#define NIVEL_UMBRAL   85.0
#define NIVEL_HIST      3.0

// Rango de calibración del sensor de nivel (Sharp GP2Y0A21)
#define DIST_MIN_CM    10.0
#define DIST_MAX_CM    80.0

// Estados de alarma (con memoria, para aplicar histéresis)
int1 alarma_temp     = FALSE;
int1 alarma_hum      = FALSE;
int1 alarma_nivel    = FALSE;
int1 actuador_estado = FALSE;

// Variables compartidas con la interrupción de recepción USART
volatile char  caracter_rx;
volatile int1  hay_caracter = FALSE;

#INT_RDA
void isr_recepcion_usart(void) {
   caracter_rx  = getc();
   hay_caracter = TRUE;
}

float leer_temperatura(void) {
   float temp_c;
   int16 q;
   set_adc_channel(0);
   delay_us(20);
   q = read_adc();
   // AD8495 (calibración validada): temp_c = 5.0 * lectura_adc / 5.115
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

// Interpolación lineal genérica: recta que pasa por (x1,y1) y (x2,y2)
float escalar_lineal(float x, float x1, float y1, float x2, float y2) {
   float m, b;
   m = (y2 - y1) / (x2 - x1);
   b = y1 - m * x1;
   return m * x + b;
}

float leer_nivel(void) {
   float vout, distancia_cm, nivel_pct;
   set_adc_channel(2);
   delay_us(20);
   vout = (float)read_adc() * 5.0 / 1023.0;
   if (vout < 0.1) vout = 0.1;   // evita división por valores casi nulos

   // Aproximación típica GP2Y0A21 (rango util 10-80 cm)
   distancia_cm = 27.86 * pow(vout, -1.15);

   if (distancia_cm < DIST_MIN_CM) distancia_cm = DIST_MIN_CM;
   if (distancia_cm > DIST_MAX_CM) distancia_cm = DIST_MAX_CM;

   // Recta que pasa por (DIST_MIN_CM, 100%) y (DIST_MAX_CM, 0%)
   nivel_pct = escalar_lineal(distancia_cm, DIST_MIN_CM, 100.0, DIST_MAX_CM, 0.0);
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
}

// Sonido armónico de alerta (dos notas encadenadas), mientras exista
// alguna alarma activa. Usa tones_mod.c (TONE_PIN remapeado a RB3).
void sonar_alarma(void) {
   if (alarma_temp || alarma_hum || alarma_nivel) {
      generate_tone(A_NOTE[1], 150);
      generate_tone(E_NOTE[2], 150);
   }
}

// Procesa el carácter capturado por la interrupción USART (no bloqueante)
void procesar_comando_remoto(void) {
   if (hay_caracter) {
      hay_caracter = FALSE;

      if (caracter_rx == 'A') {
         actuador_estado = !actuador_estado;
         output_bit(ACTUADOR, actuador_estado);

         if (actuador_estado)
            printf(">> COMANDO 'A': ACTUADOR ACTIVADO\r");
         else
            printf(">> COMANDO 'A': ACTUADOR DESACTIVADO\r");
      }
   }
}

// Único punto de verdad: calcula la prioridad y el mensaje de estado
// una sola vez, y lo envía simultáneamente al LCD y al USART.
void mostrar_estado(float temperatura, float humedad, float nivel) {
   char msg_estado[26];
   int8 prioridad;

   if (alarma_temp)       prioridad = 1;
   else if (alarma_hum)   prioridad = 2;
   else if (alarma_nivel) prioridad = 3;
   else                   prioridad = 0;

   switch(prioridad) {
      case 1:  strcpy(msg_estado, "T ALTA"); break;
      case 2:  strcpy(msg_estado, "H ALTA");     break;
      case 3:  strcpy(msg_estado, "N ALTO");       break;
      default: strcpy(msg_estado, "NORMAL");           break;
   }

   // LCD
   lcd_gotoxy(1,1);
   printf(lcd_putc, "T:%5.2fC H:%4.1f%%", temperatura, humedad);
   lcd_gotoxy(1,2);
   printf(lcd_putc, "N:%5.2f%% %s",nivel, msg_estado);

   // USART (misma información, mismo instante, misma variable prioridad)
   printf("\fSILO - SALA DE MONITOREO\r\n");
   printf("T:%5.2fC  H:%5.2f%%  N:%5.2f%%\r\n", temperatura, humedad, nivel);
   printf("%s\r", msg_estado);
}

void main() {
   float temperatura, humedad, nivel;
   int16 contador_tx = 0;

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_TO_AN2 | VSS_VDD);

   output_low(LED_TEMP);
   output_low(LED_HUM);
   output_low(LED_NIVEL);
   output_low(BUZZER);
   output_low(ACTUADOR);

   lcd_init();
   lcd_putc('\f');

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);

   while(TRUE) {
      temperatura = leer_temperatura();
      humedad     = leer_humedad();
      nivel       = leer_nivel();

      evaluar_alarmas(temperatura, humedad, nivel);

      // LED y buzzer: reacción instantánea, cada 50 ms (indicadores de hardware simple)
      output_bit(LED_TEMP,  alarma_temp);
      output_bit(LED_HUM,   alarma_hum);
      output_bit(LED_NIVEL, alarma_nivel);
      sonar_alarma();
      procesar_comando_remoto(); 
      mostrar_estado(temperatura, humedad, nivel);
   }
}
