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
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 10 (*, displays as 1)
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}  // 11 (#, displays as 1)
};

// Prototipos
void display_key(int8 key);
int8 read_keypad(void);

// Mostrar una tecla en ambas matrices
void display_key(int8 key) {
    int8 digit1, digit2;
    if (key == 10) { // * -> mostrar "10"
        digit1 = 1;
        digit2 = 0;
    } else if (key == 11) { // # -> mostrar "11"
        digit1 = 1;
        digit2 = 1;
    } else { // 0-9
        digit1 = key;
        digit2 = key;
    }
    
    for (int8 row = 0; row < 7; row++) {
        output_b(0xFF);
        output_d(0x00);
        output_e(0x00);
        output_b(~(1 << row));
        output_d((digit_patterns[digit1][row] & 0x1F) |
                 ((digit_patterns[digit2][row] << 5) & 0xE0));
        output_e((digit_patterns[digit2][row] >> 3) & 0x03);
        delay_us(500);
        output_b(0xFF);
        output_d(0x00);
        output_e(0x00);
    }
}

// Leer teclado matricial con anti-rebote
int8 read_keypad() {
    int8 key = 0xFF; // No tecla
    set_tris_c(0xE0); // RC0-RC2, RC4 outputs, RC5-RC7 inputs

    // Escanear RC0 (row 1: 1, 2, 3)
    output_c(0b00010110); // RC0=0, RC1=1, RC2=1, RC4=1
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = 1; } // 1
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = 2; } // 2
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = 3; } // 3

    // Escanear RC1 (row 2: 4, 5, 6)
    output_c(output_c(0b00010101)); // RC0=1, RC1=0, RC2=1, RC4=1
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = 4; } // 4
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = 5; } // 5
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = 6; } // 6

    // Escanear RC2 (row 3: 7, 8, 9)
    output_c(output_c(0b00010011)); // RC0=1, RC1=1, RC2=0, RC4=1
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = 7; } // 7
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = 8; } // 8
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = 9; } // 9

    // Escanear RC4 (row 4: *, 0, #)
    output_c(0x07); // RC0=1, RC1=1, RC2=1, RC4=0
    delay_us(200);
    if (!input(PIN_C5)) { delay_ms(20); if (!input(PIN_C5)) key = 10; } // *
    if (!input(PIN_C6)) { delay_ms(20); if (!input(PIN_C6)) key = 0; } // 0
    if (!input(PIN_C7)) { delay_ms(20); if (!input(PIN_C7)) key = 11; } // #

    output_c(0x00); // Apagar todas las filas
    return key;
}

void main() {
    // Configuración inicial
    setup_adc_ports(NO_ANALOGS);
    set_tris_b(0x00); // Filas LED (cátodos, salidas)
    set_tris_c(0xE0); // RC0-RC2, RC4 outputs, RC5-RC7 inputs
    set_tris_d(0x00); // Columnas LED (ánodos, RD0-RD7)
    set_tris_e(0x00); // Columnas LED (ánodos, RE0-RE1)
    output_b(0xFF); // Apagar filas (cátodos en alto)
    output_c(0x00); // Apagar filas del teclado
    output_d(0x00); // Apagar columnas (ánodos en bajo)
    output_e(0x00);
    
    int8 current_key = 0; // Inicia mostrando 00
    
    while (TRUE) {
        int8 key = read_keypad();
        if (key != 0xFF) { // Tecla presionada
            current_key = key;
        }
        display_key(current_key);
    }
}
