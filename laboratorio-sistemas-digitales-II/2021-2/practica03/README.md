# Práctica 3: Diseño de aplicaciones con el conversor análogo - digital y la interfaz de comunicación serie SCI. (USART).

*Enunciado del Laboratorio de Sistemas Digitales II, Julio 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Gestionar la configuración del conversor análogo digital.

2. Gestionar la configuración de la interfaz de comunicación serie SCI del PIC 18F4550.

3. Implementar conversión analógica a digital con un microcontrolador PIC 18F4550.

4. Implementar el uso de la interfaz de comunicación serie SCI del PIC 18F4550.

5. Resolver problema específico con manejo de la conversión análoga digital y la interfaz de comuni-
cación serie SCI del PIC 18F4550.

## Pre-Laboratorio
1. Investigar el funcionamiento del sensor LM35 e indicar la relación de temperatura/Nro digital.

2. Investigar el funcionamiento del sensor MPXA6115A e indicar la relación de presión/Nro digital.

3. Investigar el funcionamiento del sensor HIH5030 e indicar la relación de Humedad/Nro digital.

4. Investigar el funcionamiento del conversor análogo digital que maneja el PIC 18F4550.

5. Listar las directivas del compilador para el conversor análogo digital que maneja el PIC 18F4550.

6. Listar las funciones en C que se utilizan para el conversor análogo digital que maneja el PIC 18F4550.

7. Explicar en que consiste la interfaz de comunicación serie SCI y como funciona en el PIC 18F4550.

8. Listar las directivas de CCS para el manejo de la interfaz de comunicación serie SCI del PIC
18F4550.

9. Listar las funciones de CCS para el manejo de la interfaz de comunicación serie SCI del PIC 18F4550.

## Laboratorio
En un invernadero es necesario medir la temperatura, humedad y presión ambiental, diseñe un
sistema de monitoreo con el PIC 18F4550 con las siguientes características:
1. Las variables físicas deben ser visualizadas en el sitio de sensado a través de un LCD.

2. Las variables físicas deben ser visualizadas en la sala de control en donde se encuentra un micro-
controlador que recibirá los datos por puerto serial conectado a un LCD.

3. Se desea encender un led en el invernadero cuando la variable física sobrepase los valores indicados
en la tabla ??.
Se recomienda utilizar las interrupciones de CAD y de USART, para la resolución de la práctica. Para la

Cuadro 1: Variables Físicas máximas

Variable Física        Valor   Unidad
Temperatura             70       ◦C
Presión             90      kPa
Humedad               50      %RH

realización de la práctica se cuenta con los siguientes materiales:
Microcontroladores PIC 18F4550.

LM35.

MPXA6115A.

HIH5030.

Leds.

## Entregas:
## Pre-Informe
Deberá ser colocado en el aula virtual en el espacio denominado Entregas, en la tarea denominada
Pre Laboratorio 03, hasta la fecha indicada en el cronograma.

## Laboratorio
1. El grupo deberá entregar un informe técnico de acuerdo al instructivo publicado en el aula virtual,
el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada Informes
de Laboratorio 03 hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Video Tutorial:Creación de
Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula
virtual, el mismo deberá ser montado en youtube, de forma oculta y enlazado al aula virtual en
el espacio denominado Entregas, en la tarea denominada Videos de Laboratorio 03 hasta la fecha
indicada en el cronograma.
