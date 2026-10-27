#INCLUDE <16F876.h>
#use delay(clock=4000000)
#fuses XT,NOWDT
#use standard_io(B) 

#int_TIMER0
void TIMER0_isr(void) {
   output_toggle(PIN_B0);
   set_timer0 (0x1B);  }               //Se recarga el timer0

void main() {
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);   //Configuración timer0

  set_timer0 (0x1B);                    //Carga del timer0
  enable_interrupts(INT_TIMER0);       //Habilita interrupción timer0
  enable_interrupts(global);           //Habilita interrupción general

  while (1);         //bucle infinito
}


