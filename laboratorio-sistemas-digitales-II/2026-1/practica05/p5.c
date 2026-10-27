#include <18F4550.h>
#fuses XT, NOMCLR, NOWDT, NOPROTECT, NOLVP, NODEBUG, CPUDIV1, VREGEN
#device ADC=10 // Configura el ADC a resolución nativa de 10 bits (0 - 1023)

#use delay(clock=4000000)

// Configuración del módulo ADC para lectura en RA0

// Configuración de pines para la pantalla LCD 16x2 (Puerto D)
#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN     PIN_D1
#define LCD_RW_PIN     PIN_D2
#define LCD_DATA4      PIN_D4
#define LCD_DATA5      PIN_D5
#define LCD_DATA6      PIN_D6
#define LCD_DATA7      PIN_D7
#include <lcd.c>

// Definiciones de Duración
#define NEGRA   2
#define CORCHEA 1

// =============================================================================
// TABLAS DE DATOS - GAME OF THRONES (Fosc = 4MHz, Prescaler TMR2 = 16)
// =============================================================================
const int total_notas = 10;

// Valores de PR2 para fijar la frecuencia de cada nota
const int pr2_val[6] = {158, 237, 200, 178, 211, 255}; 
// Ciclo de trabajo al 50% (Duty Cycle)
const int16 dc_val[6] = {318, 476, 402, 358, 424, 510}; 

// Nombres de las notas para visualización en el LCD
char note_names[6][4] = {"G4 ", "C4 ", "Eb4", "F4 ", "D4 ", "G3 "};

// Secuencia de la melodía: G4(N), C4(N), Eb4(C), F4(C), G4(N), C4(N), Eb4(C), F4(C), D4(N), G3(N)
int melody[10]   = {0, 1, 2, 3, 0, 1, 2, 3, 4, 5};
int duration[10] = {NEGRA, NEGRA, CORCHEA, CORCHEA, NEGRA, NEGRA, CORCHEA, CORCHEA, NEGRA, NEGRA};

// Variables Globales (marcadas como volatile al modificarse dentro de ISRs)
int i = 0;                        // Índice de la nota actual
volatile int tic = 0;             // Contador de unidades de tiempo
volatile int1 estado_play = 1;     // 1: Reproduciendo, 0: Pausado
int16 lectura_adc = 0;           // Valor leído en RA0
int16 base_tempo = 62500;        // Valor de comparación para CCP

// Prototipos de Funciones para Control de Motores (L293D)
void detener_motores();
void avanzar();

// =============================================================================
// RUTINAS DE INTERRUPCIÓN (ISRs)
// =============================================================================

// 1. Interrupción Externa por Flanco de Bajada en RB0 (Pulsador Play / Pausa)
#INT_EXT
void ext_isr() {
   estado_play = !estado_play; // Alternar estado Play/Pausa
   
   if(!estado_play) {
      set_pwm2_duty(0); // Silenciar inmediatamente el buzzer al pausar
   }
}

// 2. Interrupción por Comparación CCP1 (Base de Tiempo / Ritmo)
#INT_CCP1
void ccp1_isr() {
   if(estado_play) {
      tic++; // Solo avanza el conteo si el sistema está en Play
   }
}

// =============================================================================
// PROGRAMA PRINCIPAL
// =============================================================================
void main() {
   // Configuración de Puertos E/S
   set_tris_a(0x01); // RA0 como entrada analógica (AN0)
   set_tris_b(0x01); // RB0 como entrada digital (INT0), RB1-RB4 como salidas de motor
   set_tris_c(0x00); // RC1 y RC2 como salidas
   set_tris_d(0x00); // Puerto D para el LCD

   // Habilitación de Pull-ups internas del Puerto B (RB0 a VCC dinámicamente)
   port_b_pullups(TRUE);

   // Configuración de Interrupción Externa INT0 (RB0) por Flanco de Bajada (Flanco H_TO_L)
   ext_int_edge(H_TO_L);

   // Inicialización del Convertidor Analógico-Digital (ADC)
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0);
   set_adc_channel(0);

   // Inicialización del LCD
   lcd_init();
   lcd_putc("\f* GAME OF THRONES *");
   lcd_gotoxy(1, 2);
   lcd_putc("Iniciando...");
   delay_ms(1000);

   // Configuración CCP1 en Modo Comparación (Tempo/Ritmo)
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
   setup_ccp1(CCP_COMPARE_RESET_TIMER);
   CCP_1 = 62500; // ~250ms inicial

   // Configuración CCP2 en Modo PWM (Generación de Tono)
   setup_ccp2(CCP_PWM);

   // Habilitación Global de Interrupciones
   enable_interrupts(INT_EXT);  // Interrupción por RB0
   enable_interrupts(INT_CCP1); // Interrupción por CCP1
   enable_interrupts(GLOBAL);   // Habilitador general

   detener_motores();

   while(TRUE) {
      // -----------------------------------------------------------------------
      // 1. Lectura de RA0 (Control Maestro de Tempo en Tiempo Real)
      // -----------------------------------------------------------------------
      lectura_adc = read_adc();
      // Mapeo del ADC (0-1023) a un rango de tiempos (30000 a 65000 tics de Timer1)
      base_tempo = 30000 + ((int32)lectura_adc * 35000) / 1023;
      CCP_1 = base_tempo; // Actualización directa del registro de comparación

      // -----------------------------------------------------------------------
      // 2. Máquina de Estados (Actualización de Hardware y Telemetría LCD)
      // -----------------------------------------------------------------------
      if(estado_play) {
         // Cargar frecuencia y duty cycle de la nota activa
         avanzar();
         setup_timer_2(T2_DIV_BY_16, pr2_val[melody[i]], 1);
         set_pwm2_duty(dc_val[melody[i]]);

         // Telemetría en el LCD
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "Nota: %s  PLAY ", note_names[melody[i]]);
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "Tempo: %4Lu ms", (base_tempo / 250));

         // Control de duración de la nota
         if(tic >= duration[i]) {
            tic = 0;
            i++;
            
            if(i >= total_notas) {
               i = 0; // Reiniciar melodía
            }

            // Silencio breve entre notas
            set_pwm2_duty(0);
            delay_ms(25);
         }
      } else {
         // Telemetría en Pausa
         detener_motores();
         lcd_gotoxy(1, 1);
         lcd_putc("Nota: ---  PAUSA");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "Tempo: %4Lu ms", (base_tempo / 250));
         delay_ms(100);
      }
   }
}

// =============================================================================
// FUNCIONES DE CONTROL DE MOTORES (DRIVER L293D - PUERTO B)
// =============================================================================
void detener_motores() {
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   output_low(PIN_B4);
}

void avanzar() {
   output_high(PIN_B1); // Motor Izquierdo Adelante
   output_low(PIN_B2);
   output_high(PIN_B3); // Motor Derecho Adelante
   output_low(PIN_B4);
}
