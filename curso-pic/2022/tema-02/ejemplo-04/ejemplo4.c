#include <16f877.h>
#use delay(clock=4000000)
#use standard_io(A,B)
int A,B;
const int D[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
void main(){
      // se abre un bucle infinito
      while(1){
      // Primero se lee el dato del puerto A y se aplica una and logica para asegurar que solo pasen los datos de los 4 bits menos significativos
      A=input_A()&0x0f;
      // Segundo se utiliza el valor del dato como puntero en el arreglo constante D decalrado anteriormente
      //De esta manera convertimos el valor que se esta leyendo del puerto en su equivalente en c[odigo de 7 segmentos
      //Utilizando una tabla predefinida de valores
      // como el problema indica que es en un solo display, se utiliza la base hexadecimal para mostrar el valor leido   
      B=D[A];
      // se envia el dato al puerto de salida donde esta conectado el display
      
      output_B(B);
      }      
}
