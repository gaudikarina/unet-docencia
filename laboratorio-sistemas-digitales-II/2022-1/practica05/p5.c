#include <18F4550.h>
#fuses XT,NOMCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,CPUDIV1,VREGEN
#use delay (clock=4000000)
#use standard_io(C)  
int i=19;
const int pr2[8]={141,139,238,119,212,94,178,158};
const int16 dc[8]={284,280,477,239,425,190,358,319};
int16 nota[2][24]={{pr2[2],pr2[4],pr2[2],pr2[6],pr2[5],pr2[5],pr2[2],pr2[4],
                    pr2[2],pr2[7],pr2[6],pr2[6],pr2[2],pr2[3],pr2[0],pr2[6],
                    pr2[5],pr2[4],pr2[4],pr2[1],pr2[0],pr2[6],pr2[7],pr2[6]},
                    {dc[2],dc[4],dc[2],dc[6],dc[5],dc[5],dc[2],dc[4],
                    dc[2],dc[7],dc[6],dc[6],dc[2],dc[3],dc[0],dc[6],
                    dc[5],dc[4],dc[4],dc[1],dc[0],dc[6],dc[7],dc[6]}};
//int16 nota[2][16]={{pr2[2],pr2[4],pr2[2],pr2[6],pr2[5],pr2[5],pr2[2],pr2[4]},pr2[2],pr2[7],pr2[6],pr2[6],pr2[2],pr2[3],pr2[0],pr2[6]},{dc[2],dc[4],dc[2],dc[6],dc[5],dc[5],dc[2],dc[4],dc[2],dc[7],dc[6],dc[6],dc[2],dc[3],dc[0],dc[6]}};

#INT_CCP1
void ccp1(){
   output_toggle(PIN_C0);
   i++;
}

void main (){
   setup_ccp1(CCP_COMPARE_RESET_TIMER);
   setup_ccp2(CCP_PWM);
   setup_timer_1(T1_internal|T1_DIV_BY_8);
   ccp_1=62500;
   enable_interrupts(int_ccp1);
   enable_interrupts(GLOBAL);
   while(1){   
         setup_timer_2(T2_DIV_BY_16,nota[0][i],1);
         set_pwm2_duty(nota[1][i]); 
         if (i>23)
            i=0;
   }   
}
