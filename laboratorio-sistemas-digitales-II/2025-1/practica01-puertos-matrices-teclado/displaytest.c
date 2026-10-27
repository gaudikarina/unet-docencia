#include <18F4550.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20000000)
#use fast_io(B)
#use fast_io(D)
#use fast_io(E)

// Configuración de puertos
#define LED_ROWS PORTB // Cathode rows (RB0-RB6, shared)
#define LED_COLS1 PORTD // Anode columns matrix 1 (RD0-RD4)
#define LED_COLS2 ((PORTD & 0xE0) | PORTE) // Anode columns matrix 2 (RD5-RD7, RE0-RE1)

// Patrones para dígitos 0-9 en matriz 5x7 (anode columns, cathode rows)
const int8 digit_patterns[10][7] = {
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 0
    {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 1
    {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F}, // 2
    {0x0E, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0E}, // 3
    {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02}, // 4
    {0x1F, 0x10, 0x10, 0x1E, 0x01, 0x11, 0x0E}, // 5
    {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E}, // 6
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}, // 7
    {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E}, // 8
    {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C}  // 9
};

// Prototipo
void display_number(int8 number);

// Mostrar un número (00-99) en ambas matrices
void display_number(int8 number) {
    int8 tens = number / 10; // Dígito de las decenas
    int8 units = number % 10; // Dígito de las unidades
    
    for (int8 row = 0; row < 7; row++) {
        output_b(0xFF); // Apagar filas
        output_d(0x00); // Apagar columnas
        output_e(0x00);
        output_b(~(1 << row)); // Activar una fila (cátodo) en bajo
        output_d((digit_patterns[tens][row] & 0x1F) | // Matriz 1 (RD0-RD4)
                 ((digit_patterns[units][row] << 5) & 0xE0)); // Matriz 2 (RD5-RD7)
        output_e((digit_patterns[units][row] >> 3) & 0x03); // Matriz 2 (RE0-RE1)
        delay_us(500); // 500us por fila para brillo
        output_b(0xFF); // Apagar fila
        output_d(0x00); // Apagar columnas
        output_e(0x00);
    }
}

void main() {
    // Configuración inicial
    setup_adc_ports(NO_ANALOGS);
    set_tris_b(0x00); // Filas LED (cátodos, salidas)
    set_tris_d(0x00); // Columnas LED (ánodos, salidas, RD0-RD7)
    set_tris_e(0x00); // Columnas LED (ánodos, salidas, RE0-RE1)
    output_b(0xFF); // Apagar filas (cátodos en alto)
    output_d(0x00); // Apagar columnas (ánodos en bajo)
    output_e(0x00);
    
    while (TRUE) {
        // Contar de 00 a 99
        for (int8 number = 0; number <= 99; number++) {
            int32 start_time = 0;
            while (start_time < 50000) { // 1s por número (1000000us)
                display_number(number);
                start_time += 3500; // ~3.5ms por ciclo (7 filas * 500us)
            }
        }
    }
}
