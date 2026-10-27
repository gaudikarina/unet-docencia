#include <18F4550.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(crystal=20MHz)

// Configuración de pines para el LCD
#define LCD_ENABLE_PIN  PIN_D0
#define LCD_RS_PIN      PIN_D1
#define LCD_RW_PIN      PIN_D2
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7

// Configuración de pines para las entradas del Driver L293B
#define MOT_IZQ_IN1     PIN_B2
#define MOT_IZQ_IN2     PIN_B3
#define MOT_DER_IN3     PIN_B4
#define MOT_DER_IN4     PIN_B5

#include <lcd.c>          

// Variables globales de estado (Banderas asíncronas para las ISR)
// Se declaran volátiles para alertar al compilador que cambian por hardware
volatile int1 flag_bumper_izq = 0;
volatile int1 flag_bumper_der = 0;

// Funciones de movimiento basadas en tu tabla de verdad
void avanzar() {
   output_high(MOT_IZQ_IN1); output_low(MOT_IZQ_IN2);
   output_high(MOT_DER_IN3); output_low(MOT_DER_IN4);
}

void retroceder() { 
   output_low(MOT_IZQ_IN1);  output_high(MOT_IZQ_IN2);
   output_low(MOT_DER_IN3);  output_high(MOT_DER_IN4);
}

void quiebro_derecha() {
   output_high(MOT_IZQ_IN1); output_low(MOT_IZQ_IN2); // Izquierdo avanza
   output_low(MOT_DER_IN3);  output_high(MOT_DER_IN4); // Derecho retrocede
}

void quiebro_izquierda() {
   output_low(MOT_IZQ_IN1);  output_high(MOT_IZQ_IN2); // Izquierdo retrocede
   output_high(MOT_DER_IN3); output_low(MOT_DER_IN4); // Derecho avanza
}

void parar() {
   output_low(MOT_IZQ_IN1); output_low(MOT_IZQ_IN2);
   output_low(MOT_DER_IN3); output_low(MOT_DER_IN4);
}

// =========================================================================
// RUTINAS DE SERVICIO DE INTERRUPCIÓN (ISR)
// =========================================================================

// Interrupción Externa 0 (Pin RB0) - Bumper Izquierdo
#int_ext
void isr_bumper_izquierdo() {
   // Operación ultra rápida: Únicamente levanta la bandera de colisión
   flag_bumper_izq = 1; 
}

// Interrupción Externa 1 (Pin RB1) - Bumper Derecho
#int_ext1
void isr_bumper_derecho() {
   // Operación ultra rápida: Únicamente levanta la bandera de colisión
   flag_bumper_der = 1;
}

// =========================================================================
// PROGRAMA PRINCIPAL
// =========================================================================
void main() {
    char tecla;
    int16 timeout;
    
    // Configuración inicial de registros para el 18F4550
    #byte SPPCON = 0xFB8
    SPPCON = 0x00;        // Desactivar SPP para liberar Puerto D
    setup_adc_ports(NO_ANALOGS); // Pines como digitales

    set_tris_d(0x00); // Puerto D como salida (LCD)
    
    // Configuración del Puerto B: 
    // RB0 (INT0) y RB1 (INT1) como ENTRADAS (1)
    // RB2 a RB5 como SALIDAS (0) para controlar el puente en H
    // Código binario resultante para TRISB: 0b00000011 -> 0x03
    set_tris_b(0x03); 
    
    lcd_init(); 
    delay_ms(100);
    
    // Configuración de los flancos de disparo de las interrupciones externas
    // L_TO_H = Flanco de subida, H_TO_L = Flanco de bajada (Requerido para Pull-up)
    ext_int_edge(0, H_TO_L); // Configura INT0 por flanco de bajada
    ext_int_edge(1, H_TO_L); // Configura INT1 por flanco de bajada
    
    // Habilitación de las interrupciones a nivel de periféricos y global
    enable_interrupts(INT_EXT);  // Habilitar Interrupción Externa INT0
    enable_interrupts(INT_EXT1); // Habilitar Interrupción Externa INT1
    enable_interrupts(GLOBAL);   // Habilitar interruptor maestro de interrupciones
    
    // Estado Inicial Seguro del Robot
    parar(); 
    lcd_putc("\fNavegando...");
    avanzar(); // Iniciar la marcha constante hacia adelante

    while(TRUE) {
        
        // --- EVALUACIÓN DE EVENTO: COLISIÓN IZQUIERDA (INT0) ---
        if(flag_bumper_izq == 1) {
            parar(); // Detiene inmediatamente la marcha
            
            // Actualización de Telemetría en el LCD
            lcd_putc("\fObstaculo Izq\nEvasion: Der");
            
            // Ejecución de la Maniobra de Evasión (Giro de escape)
            quiebro_derecha();
            delay_ms(2000); // Retardo controlado de manera síncrona en el main
            
            // Restablecimiento del Lazo Principal Seguro
            flag_bumper_izq = 0; // Limpiar la bandera para el próximo evento
            lcd_putc("\fNavegando...");
            avanzar();
        }
        
        // --- EVALUACIÓN DE EVENTO: COLISIÓN DERECHA (INT1) ---
        if(flag_bumper_der == 1) {
            parar(); // Detiene inmediatamente la marcha
            
            // Actualización de Telemetría en el LCD
            lcd_putc("\fObstaculo Der\nEvasion: Izq");
            
            // Ejecución de la Maniobra de Evasión (Giro de escape en sentido opuesto)
            quiebro_izquierda();
            delay_ms(2000); // Retardo controlado de manera síncrona en el main
            
            // Restablecimiento del Lazo Principal Seguro
            flag_bumper_der = 0; // Limpiar la bandera para el próximo evento
            lcd_putc("\fNavegando...");
            avanzar();
        }
        
        delay_ms(10); // Estabilización mínima del lazo principal
    }
}
