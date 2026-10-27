#include <18F4550.h>
#device high_ints = TRUE
#FUSES HS, NOPROTECT, NOWDT, NOBROWNOUT, PUT, NOLVP, NOPBADEN

#use delay(clock=4000000)

void main() {
   setup_adc_ports(NO_ANALOGS); // Desactiva entradas analógicas
   set_tris_b(0x00);            // Configura el Puerto B como salida

   while(TRUE) {
      output_high(PIN_B4);
      delay_ms(500);

      output_low(PIN_B4);
      delay_ms(500);
   }
}
