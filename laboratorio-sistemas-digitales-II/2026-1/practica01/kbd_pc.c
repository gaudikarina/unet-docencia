///////////////////////////////////////////////////////////////////////////
////                     KBD_PUERTOC.C                                 ////
////          Driver de teclado optimizado para Puerto C               ////
///////////////////////////////////////////////////////////////////////////

#define FILA_0   PIN_C0
#define FILA_1   PIN_C1
#define FILA_2   PIN_C2
#define FILA_3   PIN_C4 

#define COL_0    PIN_C5
#define COL_1    PIN_C6
#define COL_2    PIN_C7

char const KEYS[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

void kbd_init() {
    set_tris_c(0xE0); // RC0-RC2, RC4 salidas | RC5-RC7 entradas
}

// Función de escaneo directo
char kbd_scan() {
    int8 const pines_filas[4] = {FILA_0, FILA_1, FILA_2, FILA_3};
    int8 const pines_columnas[3] = {COL_0, COL_1, COL_2};
    int8 f, c;

    output_high(FILA_0);
    output_high(FILA_1);
    output_high(FILA_2);
    output_high(FILA_3);

    for(f = 0; f < 4; f++) {
        output_low(pines_filas[f]); 
        delay_us(10); // Tiempo suficiente para que el modelo del PIC en Proteus reaccione

        for(c = 0; c < 3; c++) {
            if(input(pines_columnas[c]) == 0) {
                output_high(pines_filas[f]); 
                return KEYS[f][c]; // Retorna la tecla inmediatamente sin delays pesados aquí
            }
        }
        output_high(pines_filas[f]); 
    }
    return 0;
}

int1 kbd_kbhit() {
    if(kbd_scan() != 0) {
        return TRUE;
    }
    return FALSE;
}

char kbd_getc() {
    return kbd_scan();
}
