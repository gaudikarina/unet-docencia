# Práctica 2: Diseño de aplicaciones con el conversor análogo - digital y el módulo USART en microcontrolador PIC.

*Enunciado del Laboratorio de Sistemas Digitales II, Septiembre 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Gestionar la configuración del conversor análogo digital.

2. Gestionar la configuración del módulo USART del PIC 18F4550.

3. Implementar conversión analógica a digital con un microcontrolador PIC 18F4550.

4. Implementar el uso del módulo USART del PIC 18F4550.

5. Resolver problema específico con manejo de la conversión análoga digital y módulo USART del PIC
18F4550.

## Pre-Laboratorio
1. Investigar el funcionamiento del sensor de temperatura RTD PT-100, su diagrama de acondiciona-
miento e indicar la relación de temperatura/nro digital.

2. Investigar el funcionamiento del LDR, su diagrama de acondicionamiento e indicar la relación de
intensidad de luz/nro digital.

3. Investigar el funcionamiento del sensor HIH5030, diagrama de acondicionamiento e indicar la rela-
ción de humedad/nro digital.

4. Investigar el funcionamiento del conversor análogo digital que maneja el PIC 18F4550.

5. Listar las directivas del compilador para el conversor análogo digital que maneja el PIC 18F4550.

6. Listar las funciones en C que se utilizan para el conversor análogo digital que maneja el PIC 18F4550.

7. Explicar en que consiste el módulo USART y como funciona en el PIC 18F4550.

8. Listar las directivas de CCS para el manejo del módulo USART del PIC 18F4550.

9. Listar las funciones de CCS para el manejo del módulo USART del PIC 18F4550.

## Laboratorio
En una habitación cerrada es necesario realizar un monitoreo del ambiente con las siguientes
características:

1. La temperatura de la habitación:

a) Se debe mostrar simultáneamente en la habitación en un LCD gráfico y en la sala de monitoreo
a través de transmisión serial, para ello utilice la herramienta VIRTUAL TERMINAL para
simular la conexión con el PC.
b) Si el valor de la temperatura sube los 200 ◦ C, se debe activar una luces secuenciales intermi-
tentes en la habitación y un mensaje de temperatura ALERTA TEMPERATURA ALTA en
la PC.

2. La humedad de la habitación:

a) Se debe mostrar simultáneamente en la habitación en un LCD y en la sala de monitoreo
a través de transmisión serial, para ello utilice la herramienta VIRTUAL TERMINAL para
simular la conexión con el PC.
b) Si el valor de la humedad baja de 50 % RH, se debe activar sirena en la habitación y un
mensaje de alerta humedad relativa baja en la PC.

3. La luz de la habitación:

a) Establezca al menos 3 niveles de luz (Alta Normal Baja, por ejemplo).
b) Se debe mostrar simultáneamente en la habitación en un LCD y en la sala de monitoreo
a través de transmisión serial, para ello utilice la herramienta VIRTUAL TERMINAL para
simular la conexión con el PC.
c) Si la luz es muy baja, se debe activar una luces de emergencia en la habitación y un mensaje
de revisar iluminación en la PC.

4. A 200 metros de la habitación se encuentra una sala remota donde se observan en un LCD gráfico
las mismas mediciones de la habitación, en la figura 1 se muestra un esquema físico de distribución.

5. Si se presiona la tecla “M” desde la PC, debe aparecer un menú que permite configurar los efectos
en las luces secuenciales (mínimo tres efectos) y encender o apagar las lámparas de emergencia.

## Restricciones de diseño:
Todas las conversiones análogas - digital deben ser de 10 bits y se debe mostrar dos decimales
de precisión en las medidas, no se aceptarán mediciones de 8 bits, si se resuelve el problema utilizando
variables enteras de 8 bits en lugar de flotantes para la medición se tomará como no entregada la práctica.
En la habitación solo debe haber un pic conectado a los tres sensores. El envio de datos a la sala de
monitoreo es a través del protocolo RS-232, simulado con la herramienta VIRTUAL TERMINAL.

Figura 1: Diagrama de Distribución.

## Entregas:
## Laboratorio
1. El grupo deberá entregar un informe técnico de acuerdo al Instructivo publicado en el aula virtual,
el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada Informes
de Laboratorio 02 hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Video Tutorial:Creación de
Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula
virtual, el mismo deberá ser montado en flipgrid y enlazado al aula en el espacio Entregas, en la
tarea denominada Videos de Laboratorio 02 hasta la fecha indicada en el cronograma.
