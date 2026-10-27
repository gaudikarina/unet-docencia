#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NODEBUG,CPUDIV1
#use delay(clock=4000000)
#device high_ints=true
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, bits=8)
#include <hdm64gs12gau.c>
#include <graphics.c>
int16 q;
float p;
char dato;
#use standard_io(C)
// 0.001=(PR2 + 1)*4*(1/4MHZ)*16
//PR2=61.5=62
//PWMDC=(CCPRXL:CCPXCON<5:4>)TOSC(TMR2 Prescale Value)
//CCPRXL = PWM / (Tosc * Prescaler)
// CCPRXL = 0.001 / ((1/4MHZ)*16)= 250 ->100% DC

void main() {
   setup_timer_2(T2_DIV_BY_16,255,1);
   setup_ccp1(CCP_PWM); 
   while(1){
    for(q=0;q<1024;q++){
       set_pwm1_duty(q);
       delay_ms(25);
       printf("%Ld\r",q);
      }
   }
      
}
