#include <18F4550.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20000000)
#use fast_io(B)
#use fast_io(C)
#use fast_io(D)
#use fast_io(E)

// Configuración de puertos
#define LED_ROWS PORTB // Cathode rows (RB0-RB6, shared)
#define LED_COLS1 PORTD // Anode columns matrix 1 (RD0-RD4)
#define LED_COLS2 ((PORTD & 0xE0) | PORTE) // Anode columns matrix 2 (RD5-RD7, RE0-RE1)

// Patrones para dígitos 0-9 en matriz 5x7 (anode columns, cathode rows)
const int8 digit_patterns[12][7] = {
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 0
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 1
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F}, // 2
    {0x0E, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0E}, // 3
    {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02}, // 4
    {0x1F, 0x10, 0x10, 0x1E, 0x01, 0x11, 0x0E}, // 5
    {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E}, // 6
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}, // 7
    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E}, // 8
    {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C}, // 9
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 10 (unused)
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}  // 11 (unused)
};

// Estados para la máquina de estados
#define IDLE 0
#define COUNT_UP 1
#define COUNT_DOWN 2

// Prototipos
void display_count(int8 count);
int8 read_keypad(void);

// Mostrar un conteo (0-99) en ambas matrices
void display_count(int8 count) {
    int8 tens = count / 10; // Dígito de decenas
    int8 units = count % 10; // Dígito de unidades
    
    for (int8 row = 0; row < 7; row++) {
        output_b(0xFF);
        output_d(0x00);
        output_e(0x00);
        output_b(~(1 << row));
        output_d((digit_patterns[tens][row] & 0x1F) |
                 ((digit_patterns[units][row] << 5) & 0xE0));
        output_e((digit_patterns[units][row] >> 3) & 0x03);
        delay_us(500);
        output_b(0xFF);
        output_d(0x00);
        output_e(0x00);
    }
}

// Leer teclado matricial con anti-rebote
char leer_teclado() {
    char key = 0; // 0 significa que no hay tecla presionada
    set_tris_c(0b11100000); // RC0-RC2, RC4 salidas, RC5-RC7 inputs

    // ======== Escanear RC0 (Fila 1: 1, 2, 3) ========
    // RC0=0, RC1=1, RC2=1, RC4=1, y mantenemos Cols (RC5-RC7) en 1
    output_c(0b11110110); 
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = '1'; }
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = '2'; }
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = '3'; }

    // ======== Escanear RC1 (Fila 2: 4, 5, 6) ========
    // RC0=1, RC1=0, RC2=1, RC4=1, y mantenemos Cols (RC5-RC7) en 1
    output_c(0b11110101); 
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = '4'; }
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = '5'; }
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = '6'; }

    // ======== Escanear RC2 (Fila 3: 7, 8, 9) ========
    // RC0=1, RC1=1, RC2=0, RC4=1, y mantenemos Cols (RC5-RC7) en 1
    output_c(0b11110011); 
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = '7'; }
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = '8'; }
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = '9'; }

    // ======== Escanear RC4 (Fila 4: *, 0, #) ========
    // RC0=1, RC1=1, RC2=1, RC4=0, y mantenemos Cols (RC5-RC7) en 1
    output_c(0b11100111); 
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = '*'; }
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = '0'; }
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = '#'; }

    // Apagar todas las filas al salir (volver a poner en bajo)
    output_c(0b00000000); 
    return key;
}

void main() {
    // Configuración inicial
    setup_adc_ports(NO_ANALOGS);
    set_tris_b(0b00000000); // Filas LED (cátodos, salidas)
    set_tris_c(0b11100000); // RC0-RC2, RC4 outputs, RC5-RC7 inputs
    set_tris_d(0b00000000); // Columnas LED (ánodos, RD0-RD7)
    set_tris_e(0b00000000); // Columnas LED (ánodos, RE0-RE1)
    output_b(0b11111111); // Apagar filas (cátodos en alto)
    output_c(0b00000000); // Apagar filas del teclado
    output_d(0b00000000); // Apagar columnas (ánodos en bajo)
    output_e(0b00000000);
    
    int8 count = 0; // Inicia en 00
    int1 key_pressed = 0; // Bandera para detectar liberación de tecla
    int8 state = IDLE; // Estado inicial
    int16 ms_counter = 0; // Contador de milisegundos
    
    while (TRUE) {
        // Manejo de teclas para cambiar estado
        int8 key = read_keypad();
        if (key != 0xFF && !key_pressed) { // Tecla presionada y no estaba presionada antes
            if (key == 10) { // * -> iniciar conteo ascendente
                state = COUNT_UP;
                key_pressed = 1;
            } else if (key == 11) { // # -> iniciar conteo descendente
                if (count == 0) {
                    count = 99; // Iniciar en 99 si count es 0
                }
                state = COUNT_DOWN;
                key_pressed = 1;
            }
            delay_ms(50); // Breve retardo para estabilidad
        } else if (key == 0xFF) { // Tecla liberada
            key_pressed = 0; // Resetear bandera
        }
        
        // Actualizar contador de tiempo (aproximación)
        ms_counter++;
        if (ms_counter >= 10) { // ~100ms (ajustado para conteo rápido)
            ms_counter = 0;
            
            // Lógica de conteo según estado
            if (state == COUNT_UP && count < 99) {
                count++;
            } else if (state == COUNT_DOWN && count > 0) {
                count--;
            } else if ((state == COUNT_UP && count >= 99) || 
                       (state == COUNT_DOWN && count <= 0)) {
                state = IDLE;
            }
        }
        
        // Refrescar display continuamente
        display_count(count);
        delay_us(100); // Breve retardo para controlar velocidad del bucle
    }
}
