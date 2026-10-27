 #include <16F877.h>
#use delay (clock=20000000)
#use standard_io(B)

int   pulso,i;

#INT_TIMER0
void serv_int(void){
      output_toggle(PIN_B3);
      set_timer0(pulso);
       if (i==0){
                  pulso++;
                  if (pulso==241) i=1;
               }
         else{
                  pulso--;
                  if(pulso==46) i=0;
            }
      }

void main (){
   output_low(pin_B3);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8);
   enable_interrupts(GLOBAL);
   enable_interrupts(int_timer0);
   set_timer0(47);
   pulso=47;
   i=0;
   while(1){

         delay_ms(20);
   }
}
