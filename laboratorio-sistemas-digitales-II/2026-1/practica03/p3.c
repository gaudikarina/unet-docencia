/**
 * ----------------------------------------------------------------------------
 * UNIVERSIDAD NACIONAL EXPERIMENTAL DEL TÁCHIRA
 * DEPARTAMENTO DE INGENIERÍA ELECTRÓNICA
 * ASIGNATURA: LABORATORIO DE SISTEMAS DIGITALES II (Prof. Gaudi Morantes)
 * * PRÁCTICA 3: Adquisición de Datos y Telemetría Multicanal (Firmware Base)
 * Microcontrolador: PIC18F4550 | Oscilador: Externo 20 MHz
 * ----------------------------------------------------------------------------
 */

#include <18F4550.h>
#device ADC=10 // Configura el ADC a resolución nativa de 10 bits (0 - 1023)

// Configuración de Fusibles para Cristal Externo de 20MHz sin división de CPU
#fuses HS, NOWDT, NOPROTECT, NOLVP, PUT, BROWNOUT

#use delay(crystal=20000000) // Indica al compilador la frecuencia de 20MHz

// --- CONFIGURACIÓN DE PUERTOS Y PERIFÉRICOS ---
#define LED_ALERTA   PIN_B0
#define BUZZER       PIN_B1

// Definición de Pines para la Librería LCD Nativa del Puerto D
#define LCD_ENABLE_PIN  PIN_D0
#define LCD_RS_PIN      PIN_D1
#define LCD_RW_PIN      PIN_D2
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7

#include <lcd.c> // Inclusión de la librería estándar de gestión del LCD
#include <stdio.h>

// --- DECLARACIÓN DE VARIABLES GLOBALES ---
int16 raw_sensor = 0;   // Lectura ADC cruda del canal AN0 (0 a 1023)
int16 raw_setpoint = 0; // Lectura ADC cruda del canal AN1 (0 a 1023)

float voltios_sensor = 0.0;
float valor_fisico = 0.0; // Valor final escalado a la unidad del grupo
float porcentaje_sensor = 0.0; // Variable normalizada a % para comparaciones
float porcentaje_setpoint = 0.0; // Umbral de control escalado de 0.0 a 100.0%

char string_linea1[16]; // Buffer de caracteres para la línea 1 del LCD
char string_linea2[16]; // Buffer de caracteres para la línea 2 del LCD

// Variables de control para la alarma asíncrona del buzzer
int1  alarma_activa = 0; 
int8  contador_buzzer = 0;

void main() 
{
    // --- INICIALIZACIÓN DE HARDWARE ---
    set_tris_b(0x00); // Configura todo el Puerto B como salidas (LED y Buzzer)
    output_low(LED_ALERTA); // Inicializa los actuadores apagados
    output_low(BUZZER);
    
    lcd_init(); // Inicializa los registros internos de la pantalla LCD
    
    // --- CONFIGURACIÓN AVANZADA DEL ADC (20 MHz) ---
    // ADCON1: AN0 y AN1 analógicos. VREF+ = VDD (5V), VREF- = VSS (0V)
    setup_adc_ports(AN0_TO_AN1 | VSS_VDD); 
    
    // ADCON2: Reloj de conversión = FOSC/32 (Para 20MHz, 1 TAD = 1.6us > 0.7us mín)
    // Tiempo de adquisición automático = 8 TAD (8 * 1.6us = 12.8us > 2.4us mín)
    setup_adc(ADC_CLOCK_DIV_32 | ADC_TAD_MUL_8);

    // Mensaje de bienvenida inicial en el LCD
    lcd_putc("\f   UNET - LSD II\n  PRACTICA 3 ADC");
    delay_ms(1500);
    lcd_putc("\f"); // Limpia la pantalla para iniciar el lazo síncrono

    while(TRUE) 
    {
        // --------------------------------------------------------------------
        // PASO 1: ADQUISICIÓN Y PROCESAMIENTO DEL CANAL AN0 (SENSOR ASIGNADO)
        // --------------------------------------------------------------------
        set_adc_channel(0); // Selecciona físicamente el multiplexor en AN0
        delay_us(20);       // Retardo síncrono de seguridad para estabilidad del muestreo
        raw_sensor = read_adc(); // Dispara conversión y retorna entero de 10-bits
        
        // Conversión matemática cruda a Voltaje base del ADC
        voltios_sensor = (raw_sensor * 5.0) / 1023.0;
        
        /**
         * ====================================================================
         * NOTA PEDAGÓGICA PARA LOS GRUPOS (ZONA DE MODIFICACIÓN ESTUDIANTIL):
         * Aquí cada grupo deberá aplicar la ecuación matemática de su sensor 
         * basándose en la instrumentación física diseñada en el pre-lab.
         * * También deben definir cómo calculan el 'porcentaje_sensor' para 
         * poder contrastarlo equitativamente con el Setpoint (0 - 100.0%).
         * ====================================================================
         */
         
        // [EJEMPLO GENÉRICO DE REFERENCIA - LM35 (10mV/C) directo a 0-5V]
        valor_fisico = voltios_sensor; // Expresado en °C (Ej. 0 a 150 °C)
        porcentaje_sensor = (valor_fisico / 5) * 100.0; // Normalizado a %

        // Construcción de la cadena de texto para la Línea 1
        sprintf(string_linea1, "Var: %5.1f V", voltios_sensor); 


        // --------------------------------------------------------------------
        // PASO 2: ADQUISICIÓN Y PROCESAMIENTO DEL CANAL AN1 (SETPOINT DE CONTROL)
        // --------------------------------------------------------------------
        set_adc_channel(1); // Selecciona el multiplexor en el potenciómetro de AN1
        delay_us(20);       // Tiempo de adquisición síncrono
        raw_setpoint = read_adc();
        
        // Escalado directo de 0 a 1023 hacia un rango estricto de 0.0 a 100.0 %
        porcentaje_setpoint = (raw_setpoint * 100.0) / 1023.0;
        
        // Construcción de la cadena de texto para la Línea 2
        sprintf(string_linea2, "Set: %5.1f %% ", porcentaje_setpoint);


        // --------------------------------------------------------------------
        // PASO 3: ACTUALIZACIÓN DINÁMICA DE LA TELEMETRÍA EN LCD
        // --------------------------------------------------------------------
        lcd_gotoxy(1, 1);       // Ubica el cursor al inicio de la Línea 1
        printf(lcd_putc, "%s", string_linea1); // Imprime el buffer del sensor
        
        lcd_gotoxy(1, 2);       // Ubica el cursor al inicio de la Línea 2
        printf(lcd_putc, "%s", string_linea2); // Imprime el buffer del setpoint


        // --------------------------------------------------------------------
        // PASO 4: LÓGICA DE CONTROL BASE Y ACCIONAMIENTO DE ALARMAS
        // --------------------------------------------------------------------
        if (porcentaje_sensor > porcentaje_setpoint) 
        {
            output_high(LED_ALERTA); // Enciende el LED de forma fija
            alarma_activa = 1;       // Habilita la bandera de oscilación del buzzer
        } 
        else 
        {
            output_low(LED_ALERTA);  // Apaga el indicador visual
            alarma_activa = 0;       // Desactiva la bandera
            output_low(BUZZER);      // Garantiza que el buzzer quede apagado
        }

        // --------------------------------------------------------------------
        // PASO 5: RUTINA ACÚSTICA INTERMITENTE CONTINUA (ANTI-BLOQUEO)
        // --------------------------------------------------------------------
        // En lugar de un delay largo, dividimos el retardo general en ráfagas.
        // Esto genera tonos sin pausar las lecturas analógicas.
        for(contador_buzzer = 0; contador_buzzer < 100; contador_buzzer++)
        {
            if(alarma_activa)
            {
                output_toggle(BUZZER); // Conmuta el pin generando una onda cuadrada
            }
            delay_ms(1); // 10 iteraciones * 10ms = Los 100ms totales de refresco requeridos
        }
    }
}
