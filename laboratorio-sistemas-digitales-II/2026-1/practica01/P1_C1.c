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

#define a     PIN_A5
#define LED     PIN_E2

#include <lcd.c>          
#include "kbd_pc.c"  // Tu librería local adaptada al Puerto C

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

void main() {
    char tecla;
    int16 timeout;
    
    // Configuración inicial de registros para el 18F4550
    #byte SPPCON = 0xFB8
    SPPCON = 0x00;        // Desactivar SPP para liberar Puerto D
    setup_adc_ports(NO_ANALOGS); // Pines como digitales
    set_tris_a(0x20); // Puerto D como salida (LCD)
    set_tris_e(0x00); 

    set_tris_d(0x00); // Puerto D como salida (LCD)
    set_tris_b(0x00); // Puerto B como salida (Motores)
    kbd_init();       // Inicializar teclado en Puerto C
    
    lcd_init(); 
    delay_ms(100);
    
    parar(); // Asegurar que los motores arranquen apagados
    lcd_putc("\fRobot Listo...\nUse: 1,2,4,5,6,8");

    while(TRUE) {
    
        if(!input(a)){
         parar();
         
         while(1){
            lcd_putc("\fBloqueado");
            output_high(LED); 
             delay_ms(200);
            output_low(LED);
             delay_ms(200);
         
         }
        
        }
        
        
        
        
        
        if(kbd_kbhit()) {
            tecla = kbd_getc(); 
            
            if(tecla != 0) { 
                
                // --- EVALUACIÓN DE LAS TECLAS MAPEADAS ---
                switch(tecla) {
                    case '1': // Secuencia Autónoma de Evasión
                        lcd_putc("\fModo: Autonomo\nAvanzando...");
                        avanzar();
                        delay_ms(1200); // 1.2 segundos
                        
                        lcd_putc("\fModo: Autonomo\nQuiebro Der ->");
                        quiebro_derecha();
                        delay_ms(400);  // 0.4 segundos
                        
                        lcd_putc("\fModo: Autonomo\nAvanzando...");
                        avanzar();
                        delay_ms(1200); // 1.2 segundos
                        
                        lcd_putc("\fModo: Autonomo\n<- Quiebro Izq");
                        quiebro_izquierda();
                        delay_ms(400);  // 0.4 segundos
                        
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
