#include <16f876.h>
#fuses XT,NOWDT
int1 cambio=0;            //Variable de control de cambio

#int_ccp2
void ccp2_int(){          //Función de interrupción
  if(++cambio==1){
    setup_ccp2(CCP_COMPARE_CLR_ON_MATCH); //Modo Comparación, cambio a 0
  } else{
    setup_ccp2(CCP_COMPARE_SET_ON_MATCH); //Modo Comparación, cambio a 1
  }
  set_timer1(0);                          //Borrado de TMR1
  CCP_2 = 199;                         //Inicialización del registro CCPR2 para un Duty del 50%
}
void main() {
disable_interrupts(global);
setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);    //Configuración TMR1
setup_ccp2(CCP_COMPARE_SET_ON_MATCH); //Configuración inicial modulo CCP
CCP_2 = 199;                         //Inicialización del registro CCPR2 para un Duty del 50%
enable_interrupts(int_ccp2);     //Habilitación interrupción modulo CCP2
enable_interrupts(global);        //Habilitación interrupción general
do {
  } while (TRUE);
 }

