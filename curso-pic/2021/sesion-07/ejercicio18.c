#include <16F877.h>
#device adc=10
#use delay (clock=4000000)
#use standard_io(B)


long Ncad;

#INT_ad
void serv_int(void){
			Ncad=read_adc();
			set_pwm1_duty(Ncad);
			
}
 		
void main (){
	setup_adc(ADC_CLOCK_DIV_8);
	setup_adc_ports(AN0);
	set_adc_channel(0);
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);
	set_timer1(0);
	setup_timer_2(T2_DIV_BY_1,255,1);
	setup_ccp1(CCP_PWM);
	setup_ccp2(CCP_COMPARE_RESET_TIMER);
	CCP_2=1000;
	enable_interrupts(GLOBAL);
	enable_interrupts(int_AD);
	while(1);
}