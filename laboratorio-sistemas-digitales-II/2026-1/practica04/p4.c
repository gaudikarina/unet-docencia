#include <18F4550.h>
#fuses HS, NOWDT, NOPROTECT, NOLVP, PUT
#use delay(crystal=20000000)

// Configuración de pines para el módulo LCD 16x2 (Mismo hardware común)[cite: 3]
#define LCD_ENABLE_PIN  PIN_D0
#define LCD_RS_PIN      PIN_D1
#define LCD_RW_PIN      PIN_D2
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7
#include <lcd.c>

// Configuración del Puerto Serie USART (Hardware nativo)[cite: 1]
// xmit=PIN_C6 -> Transmisión del PIC (TX)
// rcv=PIN_C7  -> Recepción del PIC (RX)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, errors)

// Prototipos de funciones de control de motores[cite: 3]
void detener_motores();
void avanzar();

// Variables globales del sistema
char caracter_recibido = ' ';
int1 estado_robot = 0; // 0: Detenido, 1: Avanzando

void main() {
    // Configuración de Registros de Dirección (Tris)[cite: 3]
    set_tris_b(0xF0); // RB0-RB3 como salidas para los motores del Driver L293D[cite: 3]
    set_tris_a(0x20); // RA5 como entrada digital (Pulsador de Emergencia)[cite: 3]
    set_tris_e(0x00); // Puerto E como salidas digitales (LED Alerta)[cite: 3]
    
    // Inicialización de periféricos
    lcd_init();
    detener_motores();
    
    // Mensaje de bienvenida en pantalla
    lcd_putc("\f* PIC UART BASE *");
    delay_ms(1000);
    lcd_putc("\fNAV: PARADO\nEsperando...");

    while(TRUE) {
        
       
        // =====================================================================

        // Lectura NO BLOQUEANTE del búfer de recepción serie
        if(kbhit()) {
            caracter_recibido = getc(); // Extrae el carácter sin detener el flujo
            
            // Intérprete de comandos
            switch(caracter_recibido) {
                case 'A': // Comando para avanzar
                    avanzar();
                    estado_robot = 1;
                    // Enviar confirmación de telemetría hacia la PC
                    printf("STATE: AVANZA\r\n");
                    break;
                    
                case 'P': // Comando para parar
                    detener_motores();
                    estado_robot = 0;
                    // Enviar confirmación de telemetría hacia la PC
                    printf("STATE: PARADO\r\n");
                    break;
            }
            
            // Actualización dinámica del LCD
            lcd_putc("\f"); // Limpiar pantalla
            if(estado_robot == 1) {
                lcd_putc("NAV: AVANZA");
            } else {
                lcd_putc("NAV: PARADO");
            }
            lcd_gotoxy(1, 2);
            printf(lcd_putc, "Last Char: '%c'", caracter_recibido);
        }
        
        delay_ms(50); // Pequeña ventana de tiempo para estabilidad
    }
}

// Implementación de funciones de control de potencia[cite: 3]
void detener_motores() {
    output_low(PIN_B0);
    output_low(PIN_B1);
    output_low(PIN_B2);
    output_low(PIN_B3);
}

void avanzar() {
    output_high(PIN_B0); // Motor Izquierdo Adelante[cite: 3]
    output_low(PIN_B1);
    output_high(PIN_B2); // Motor Derecho Adelante[cite: 3]
    output_low(PIN_B3);
}
