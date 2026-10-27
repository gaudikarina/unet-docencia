#include <16F877.h>
#use delay (clock=4000000) 
#use standard_io(B,C,D,E)
int B,C1,R,U,D,C;
const int D1[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
// funci[on que transforma un valor binario en bdc y luego a 7 segmentos
//en este caso se van a restar dos numeros que oscilan entre 0 y 255 unidades
// por lo tanto el resultado de la resta estar[a entre 0 y 255 unidades
// para poder visualizar este valor en el display 7 segmentos se debe llevar el valor binario
// a formato BCD, esto se realiza con divisiones y resto entre 100 y 10 y asi se obtienen los valores de 
// las unidades, decenas y centenas del numero a mostrar en el display, una vez obetenido el numero en bcd es decir de 0 a 9, 
// se procede a llevarlo a su valor 7 segmentos para visualizarlo en el display a traves de la tabla definida como constante, en este caso con los valores equivalentes del 0 al 9
void binabcd7s(int R1){
       int a,cn,dc,un;
       cn=R1/100;
       a=R1%100;
       dc=a/10;
       un=a%10;
       C=D1[cn];
       D=D1[dc];
       U=D1[un];
      return; 
}
// la funci[on mostrar display permite realizar el algoritmo explicado en el tema para realizar el barrido y muestreo de cada dato en el display
// en este caso se utilizaran 3 displays ya que el resultado de la resta puede ser de 3 cifras
void mostrardisplay(void){
    output_D(0x00);    
    output_E(0x07);
    output_D(U);    
    output_E(0x06);
    delay_ms(3);
    output_D(0x00);    
    output_E(0x07);
    output_D(D);    
    output_E(0x05);
    delay_ms(3);   
    output_D(0x00);    
    output_E(0x07);
    output_D(C);    
    output_E(0x03);
    delay_ms(3);  
   return;  
}
void main(){
  // Como el puerto B es de entrada o lectura se van a activar las pull up internas 
port_b_pullups(1);
while(1){
   // lectura de los datos a restar por puerto
      B= input_B();
      C1= input_C();
 // Se comprueba que valor es mayor para que la resta sea siempre positiva
     if (B>=C1){
               R=B-C1;             
               }
      else
             {
             R=C1-B;
             }
//Obtenido el resultado de la resta se llama a la funcion para convertir el valor binario a 7 segmentos
     binabcd7s(R);
//se llama a la funcion de barrido de los displays en paralelo
      mostrardisplay();
   }
}

