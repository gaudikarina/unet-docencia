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
#define MOT_IZQ_IN1     PIN_B0
#define MOT_IZQ_IN2     PIN_B1
#define MOT_DER_IN3     PIN_B2
#define MOT_DER_IN4     PIN_B3

// Definición de pines de seguridad y LED testigo
#define ESTOP_PIN       PIN_A5   // Pin INT0 para la interrupción
#define LED_TESTIGO     PIN_E2   // Pin para el LED de alerta intermitente

#include <lcd.c>          
#include "kbd_pc.c"  // Tu librería local adaptada al Puerto C

// Variable global volatile para compartir el estado con la ISR
// Usar volatile asegura que el compilador no 'optimice' la variable
// asumiendo que no cambia fuera del flujo principal de código.
volatile int1 estop_triggered = 0;

// Funciones de movimiento basadas en tu tabla de verdad
void parar() {
   // Solo apagar si no está ya en modo de parada crítica para evitar parpadeos
   if (!estop_triggered) {
       output_low(MOT_IZQ_IN1); output_low(MOT_IZQ_IN2);
       output_low(MOT_DER_IN3); output_low(MOT_DER_IN4);
   }
}

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

// -------------------------------------------------------------------------
// PROTOCOLO DE PARADA DE EMERGENCIA POR HARDWARE (INT_EXT)
// Esta función se ejecuta INMEDIATAMENTE cuando RA5 detecta un 0 lógico.
// Rompe cualquier 'delay_ms()' o bucle en curso en el flujo principal.
// -------------------------------------------------------------------------
#INT_EXT
void estop_isr() {
    estop_triggered = 1; // Establecer bandera global de parada crítica
}

// -------------------------------------------------------------------------
// Función principal (main)
// -------------------------------------------------------------------------
void main() {
    char tecla;
    int16 timeout;
    
    // Configuración inicial de registros para el 18F4550
    #byte SPPCON = 0xFB8
    SPPCON = 0x00;        // Desactivar SPP para asegurar Puerto D digital

    // IMPORTANTE: Asegurar pines digitales. Por defecto arrancan en analógico.
    setup_adc_ports(NO_ANALOGS); 
    
    // Configuración de TRIS
    set_tris_a(0x20);     // RA5 (INT0) como entrada digital
    set_tris_d(0x00);     // Puerto D como salida (LCD)
    set_tris_b(0x00);     // Puerto B como salida (Motores)
    set_tris_e(0xFB);     // RE2 como salida (LED testigo)
    
    output_low(LED_TESTIGO); // Inicializar LED testigo apagado
    
    // Configuración de Interrupciones Externas
    enable_interrupts(INT_EXT);        // Habilitar INT0 en RA5
    ext_int_edge(H_TO_L);             // Detectar flanco de bajada (Pulsador presionado a masa)
    enable_interrupts(GLOBAL);         // Habilitar interrupciones globales

    kbd_init();       // Inicializar teclado en Puerto C
    
    lcd_init(); 
    delay_ms(100);
    
    parar(); // Asegurar que los motores arranquen apagados
    lcd_putc("\fRobot Listo...\nUse: 1,2,4,5,6,8");

    while(TRUE) {
        // -----------------------------------------------------------------
        // VERIFICACIÓN DEL ESTADO DE EMERGENCIA (SONDEO)
        // -----------------------------------------------------------------
        // Este bloque gestiona la respuesta de seguridad una vez activada
        // la interrupción. También mantiene la compatibilidad con el
        // pulsador por si el micro se reinicia con la interrupción desactivada.
        if (estop_triggered || !input(ESTOP_PIN)) {
            // 1. Apagar por completo ambos motores (RB0-RB3 en 0)
            output_low(MOT_IZQ_IN1); output_low(MOT_IZQ_IN2);
            output_low(MOT_DER_IN3); output_low(MOT_DER_IN4);
            
            lcd_putc("\f!!! PARADA !!!\n  URGENTE [A5]");
            
            // -------------------------------------------------------------
            // BUCLE BLOQUEANTE DE ALERTA Y SEGURIDAD
            // Este bucle no tiene escape. El teclado y todo el control
            // quedan completamente bloqueados hasta que el micro sea reiniciado.
            // -------------------------------------------------------------
            while(1) {
                output_high(LED_TESTIGO); // LED testigo encendido
                delay_ms(200);           // Retardo de 200ms
                output_low(LED_TESTIGO);  // LED testigo apagado
                delay_ms(200);           // Retardo de 200ms
            }
        } else {
            // El resto de la lógica del programa se ejecuta solo si
            // NO se ha detectado la parada de emergencia.
            
            if(kbd_kbhit()) { 
                tecla = kbd_getc(); 
                
                if(tecla != 0) { 
                    
                    // --- EVALUACIÓN DE LAS TECLAS MAPEADAS ---
                    switch(tecla) {
                        case '1': // Secuencia Autónoma de Evasión
                            // NOTA: Gracias a la interrupción externa, la secuencia
                            // se romperá instantáneamente al presionar RA5, sin
                            // esperar a que terminen estos delay_ms(1200).
                            lcd_putc("\fModo: Autonomo\nAvanzando...");
                            avanzar();
                            delay_ms(1200); 
                            
                            lcd_putc("\fModo: Autonomo\nQuiebro Der ->");
                            quiebro_derecha();
                            delay_ms(400);  
                            
                            lcd_putc("\fModo: Autonomo\nAvanzando...");
                            avanzar();
                            delay_ms(1200); 
                            
                            lcd_putc("\fModo: Autonomo\n<- Quiebro Izq");
                            quiebro_izquierda();
                            delay_ms(400);  
                            
                            lcd_putc("\fModo: Autonomo\nFin Secuencia");
                            parar();
                            break;

                        case '2': // Avanzar
                            lcd_putc("\fMoviendo:\nAvanzar ^");
                            avanzar();
                            break;
                            
                        case '8': // Retroceder
                            lcd_putc("\fMoviendo:\nRetroceder v");
                            retroceder();
                            break;
                            
                        case '4': // Giro Izquierda
                            lcd_putc("\fGiro:\n<- Izquierda");
                            quiebro_izquierda();
                            break;
                            
                        case '6': // Giro Derecha
                            lcd_putc("\fGiro:\nDerecha ->");
                            quiebro_derecha();
                            break;
                            
                        case '5': // Parar
                            lcd_putc("\fMotores:\nDetenidos [X]");
                            parar();
                            break;
                            
                        default: // Cualquier otra tecla no mapeada
                            lcd_putc("\fTecla Invalida\nUse: 1,2,4,5,6,8");
                            break;
                    }
                    
                    // --- ESPERA OPTIMIZADA PARA SIMULACIÓN (PROTEUS) ---
                    timeout = 0;
                    while(kbd_kbhit() && (timeout < 100)) { 
                        delay_ms(10); 
                        timeout++;
                    }
                    // -----------------------------------------------------
                    
                    delay_ms(20); 
                }
            }
            
            // Respiro para el procesador de Proteus
            delay_ms(10); 
        }
    }
}
