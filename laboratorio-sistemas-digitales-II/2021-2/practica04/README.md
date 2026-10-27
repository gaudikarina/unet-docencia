# Práctica 4: Diseñar aplicaciones con la interfaz intercircuito. (I2C).

*Enunciado del Laboratorio de Sistemas Digitales II, Julio 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Gestionar la configuración de la interfaz serie de periféricos del PIC 18F4550.

2. Implementar el uso de la interfaz serie de periféricos del PIC 18F4550.

3. Resolver problema específico con manejo de la interfaz serie de periféricos del PIC 18F4550.

## Pre-Laboratorio
1. Explicar en que consiste la interfaz intercircuito y como funciona en el PIC 18F4550.

2. Listar las directivas en ccs asociadas con la interfaz intercircuito.

3. Listar las funciones en ccs asociadas con la interfaz intercircuito.

## Laboratorio
En el invernadero de la práctica 03, se ubican los sensores en diferentes zonas como se indica en
la figura ??. Se debe realizar el monitoreo de las varíables físicas y deben ser visualizadas en la sala de
control, en donde se encuentra un microcontrolador conectado a un LCD gráfico que recibe a través del
puerto serial protocolo I2 C los datos de cada variable física. Cuando la variable física excede los valores
límites de la tabla ??, se debe visualizar en el LCD gráfico un mensaje de alerta y se debe encender el led
del sensor correspondiente. En cada área se visualiza el valor sensado en un LCD.

Cuadro 1: Variables Físicas máximas

Variable Física        Valor   Unidad
Temperatura             80       ◦C
Presión             50      kPa
Humedad               40      %RH

Para la realización de la práctica se cuenta con los siguientes materiales:

Figura 1: Ubicación sensores en invernadero

Microcontroladores PIC 18F4550.

LM35.

MPXA6115A.

HIH5030.

Leds.

## Entregas:
## Pre-Informe
Deberá ser colocado en el aula virtual en el espacio denominado Entregas, en la tarea denominada
Pre Laboratorio 04, hasta la fecha indicada en el cronograma.

## Laboratorio
1. El grupo deberá entregar un informe técnico de acuerdo al instructivo publicado en el aula virtual,
el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada Informes
de Laboratorio 04 hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Video Tutorial:Creación de
Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula
virtual, el mismo deberá ser montado en youtube, de forma oculta y enlazado al aula virtual en
el espacio denominado Entregas, en la tarea denominada Videos de Laboratorio 04 hasta la fecha
indicada en el cronograma.
