#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(A,B,C)
//Definicion de variables globales
int A1,A2,A3;
short b;
//Función que verifica que la entrada cumple el codigo BCD
short validar_bcd(int a){
   if (a>=10){
      b=0;
      }
   else   
      b=1;
   return(b);   
}
//Función principal del programa
void main (){
   while(1){
      A1=input_A()&15;
      A2=input_B()&15;
      A3=swap(input_B()&0XF0);// cambio de los 4 bits más significativos a menos significativos.
      if(validar_bcd(A1)&&validar_bcd(A2)&&validar_bcd(A3)){
         if(A1>A2){
            if(A1>A3)
            output_C(A1);
            else
            output_C(A3);
         }
         else
         {
         if(A2>A3)
         output_C(A2);
         else
         output_C(A3);
         }
      }
      else      
      output_C(0xf0);
   }
}      
