#include <18F4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#use delay (clock=4000000)

// Definiciones de tiempos basándonos en una base de 250ms
#define NEGRA 2
#define CORCHEA 1

int i = 0;
int tic = 0; // Contador de unidades de tiempo (corcheas)

const int pr2_val[7] = {79, 59, 39, 44, 46, 52, 29}; // G3, C4, G4, F4, E4, D4, C5
const int16 dc_val[7] = {160, 120, 80, 90, 94, 106, 60};

// Arreglo de la melodía (índices de los arreglos anteriores)
int melody[] = {0, 1, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 2, 3, 4, 3, 5};

// Arreglo de duraciones (en unidades de corchea)
int duration[] = {NEGRA, NEGRA, NEGRA, CORCHEA, CORCHEA, CORCHEA, NEGRA, 
                  NEGRA, CORCHEA, CORCHEA, CORCHEA, NEGRA, NEGRA, 
                  CORCHEA, CORCHEA, CORCHEA, NEGRA};

#INT_CCP1
void ccp1_isr() {
   tic++; // Esta interrupción saltará cada 250ms (una corchea)
}

void main () {
   // Configuración PWM en CCP2 (Pin RC1)
   setup_ccp2(CCP_PWM);
   
   // Configuración Comparación en CCP1 para el TEMPO
   // Reloj 4MHz -> Fosc/4 = 1MHz. T1_DIV_BY_4 -> 250kHz.
   // Para 250ms (0.25s): 0.25 * 250,000 = 62500
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_4); 
   setup_ccp1(CCP_COMPARE_RESET_TIMER);
   CCP_1 = 62500; // Interrupción cada 250ms (Corchea)
   
   enable_interrupts(INT_CCP1);
   enable_interrupts(GLOBAL);

   while(1) {   
      // Actualizamos los registros del PWM con la nota actual
      setup_timer_2(T2_DIV_BY_16, pr2_val[melody[i]], 1);
      set_pwm2_duty(dc_val[melody[i]]); 
      
      // Esperamos a que el "tic" alcance la duración de la nota
      if (tic >= duration[i]) {
         tic = 0; // Reiniciamos contador de tiempo
         i++;     // Pasamos a la siguiente nota
         
         if (i >= 17) i = 0; // Reiniciar melodía
         
         // Breve pausa de silencio entre notas para que no suenen pegadas
         set_pwm2_duty(0);
         delay_ms(20); 
      }
   }   
}
