#include <18f4550.h>
#fuses XT,NOMCLR,NOWDT,NODEBUG,CPUDIV1
#use delay(clock=4000000)
#device high_ints=true
#use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7, bits=8)
char dato;
int16 q;
#use standard_io(C)
#int_RDA high
serv_int()
{
     dato=getchar();     
     puts("Recibido");   
}
// 0.001=(PR2 + 1)*4*(1/4MHZ)*16
//PR2=61.5=62
//PWMDC=(CCPRXL:CCPXCON<5:4>)TOSC(TMR2 Prescale Value)
//CCPRXL = PWM / (Tosc * Prescaler)
// CCPRXL = 0.001 / ((1/4MHZ)*16)= 250 ->100% DC
void main() {
   setup_timer_2(T2_DIV_BY_4,249,1);
   setup_ccp1(CCP_PWM); 
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   printf("***********************************\r");
   printf("CONTROL VELOCIDAD MOTOR DC POR PWM \r");
   printf("OPCION 1: 20%% \t");
   printf("OPCION 2: 40%%\t");
   printf("OPCION 3: 60%%\r ");
   printf("OPCION 4: 80%%\t ");
   printf("OPCION 5: 100%%\r ");
    While (1) { 
     switch (dato){
      case '1': 
//!      for(q=0;q<250;q++){
//!       set_pwm1_duty(q);
//!       delay_ms(25);
//!       printf("%Ld\r",q);
//!      }    
      q=200;
      break;
       case '2': 
          q=250;
         break;  
      case '3': 
         q=500;
         break;
      case '4': 
        q=750;
         break;
      case '5':
        q=1000;
         break;
      default:
         break;         
      }
      set_pwm1_duty(q); 
    }
}
