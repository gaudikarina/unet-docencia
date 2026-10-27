# Práctica 2: Manejo de interrupciones externas del microcontrolador PIC 18F4550.

*Enunciado del Laboratorio de Sistemas Digitales II, Julio 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Gestionar la configuración de interrupciones externas.

2. Manejar los niveles de prioridad en interrupciones externas.

3. Resolver un problema especifico con manejo de interrupciones externas.

## Pre-Laboratorio
1. Investigar los tipos de interrupciones externas que maneja el PIC 18F4550.

2. Explicar la priorización de interrupciones en el PIC 18F4550.

3. Listar las directivas del compilador para interrupciones del pic 18F4550.

4. Listar las funciones en C que se utilizan para interrupciones externas del pic 18F4550.

## Laboratorio
En una empaquetadora de fruta se tienen 4 bandas transportadoras de alimentos, las cuales trans-
portan 4 frutas hacia 4 cajas de depósito como se indica en la figura 1. Las frutas tienen una prioridad
de empaquetamiento, los depósitos tiene una capacidad máxima y las bandas manejan 4 velocidades
diferentes como se indica en la tabla 1.

Cuadro 1: Características de la línea de empaquetamiento

Fruta       Prioridad        Capacidad Velocidad
Fresa           01              10      100 ms
Mango           02              20      150 ms
Pera           02              15       75 ms
Manzana          03              05      200 ms

Se desea realizar una aplicación de monitoreo con las siguientes características:

Figura 1: Empaquetadora de Frutas

1. Cuente la cantidad de fruta que va entrando a cada caja, para ello debe tomar en cuenta la prioridad
de la fruta, cada vez que una fruta cae en el deposito se enciende un led por 100 ms y luego se
apaga.

2. En un LCD gráfico con controlador KS0108, se debe visualizar el conteo de cada depósito.

3. Una vez lleno un depósito se debe visualizar en el LCD gráfico la palabra FULL y debe parar la
banda transportadora, por lo tanto se paraliza el conteo.

4. Para reiniciar el conteo de la banda transportadora, se debe presionar un interruptor que pone
en marcha de nuevo el motor, en ese momento, en el LCD se debe reiniciar el conteo de la fruta
correspondiente.

Diseñe la aplicación de monitoreo que cumpla con estos requerimientos. Para ello cuenta con los siguientes
materiales:

Generador de Pulsos a las frecuencias indicadas.

Un LCD gráfico con controlador KS0108.

Un microcontrolador PIC 18F4550.

Leds (un color diferente por cada fruta).

Pulsadores.

## Restricciones de diseño:
Solo debe utilizar interrupciones externas del PIC 18F4550.

## Entregas:
## Pre-Informe
Deberá ser colocado en el aula virtual en el espacio denominado Entregas, en la tarea denominada
Pre Laboratorio 02, hasta la fecha indicada en el cronograma.

## Laboratorio
1. El grupo deberá entregar un informe técnico de acuerdo al instructivo publicado en el aula virtual,
el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada Informes
de Laboratorio 02 hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Video Tutorial:Creación de
Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula
virtual, el mismo deberá ser montado en youtube, de forma oculta y enlazado al aula virtual en
el espacio denominado Entregas, en la tarea denominada Videos de Laboratorio 02 hasta la fecha
indicada en el cronograma.
