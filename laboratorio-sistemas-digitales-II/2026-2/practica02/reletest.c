#include <18F4550.h>
#FUSES HS,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP,NOPBADEN
#use delay(clock=4000000)
#use standard_io(A,B,C,D)
#define RELE PIN_B4

void main() {
   output_low(RELE);   // Estado inicial: relé desactivado

   while(TRUE) {
      output_high(RELE);   // Activa el relé (energiza la bobina)
      delay_ms(2000);

      output_low(RELE);    // Desactiva el relé
      delay_ms(2000);
   }
}
