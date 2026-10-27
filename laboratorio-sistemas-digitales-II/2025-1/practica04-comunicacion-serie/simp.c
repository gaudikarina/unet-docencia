#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#device adc=10
#use delay(clock=40000000)
#use rs232(baud=9600, xmit=pin_e1, rcv=pin_e2, stream=PC)
#include <lcd.c>
#use standard_io(E)
char c;

#int_RDA
void serv_int() {
    if (kbhit(PC)) {
        c = fgetc(PC);
        output_high(PIN_E0)
        
        // Aquí puedes hacer algo con c, como encender un LED o mostrar en LCD
    }
}

void main() {
    enable_interrupts(INT_RDA);
    enable_interrupts(GLOBAL);
    lcd_init();

    while (1) {
        // Puedes agregar un mensaje en el LCD para verificar que el programa está corriendo
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "Esperando...");
        delay_ms(1000);
    }
}

