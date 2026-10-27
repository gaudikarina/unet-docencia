# Práctica 1: Diseño de aplicaciones de manejo de los puertos E/S digital del microcontrolador PIC

*Enunciado del Laboratorio de Sistemas Digitales II, Mayo 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Gestionar la configuración de puertos a través de su posición de memoria.

2. Gestionar la configuración de puertos a través de las directivas del compilador CCS.

3. Manejar puertos de E/S del microcontrolador para resolver un problema especifico.

## Pre-Laboratorio
1. Investigar la estructura de los puertos de E/S del microcontrolador PIC e indicar su funcionamiento
pin a pin.

2. Explicar la configuración de puertos de acuerdo a su posición de memoria con ejemplos.

3. Explicar la configuración de puertos de acuerdo a las directivas del compilador con ejemplos.

4. Listar las funciones en C que se utilizan para manejo de puertos de E/S.

5. Investigar el funcionamiento, librerías y funciones en CCS, y modo de conexión de los siguientes
elementos:

a) Pulsadores,
b) Teclado 4x4,
c) LCD gráfico con controlador KS0108.

## Laboratorio
En una empresa de seguridad, un cliente solicita la realización de una cerradura digital con las
siguientes características:

1. Clave de 6 dígitos alfanumérica,

2. Menú de configuración de administrador que permita el cambio de clave, para ello el administrador
suministrará un código secreto único, que lo conducirá directamente al menú de cambio de clave,

3. En la pantalla de inicio debe verse el nombre de la empresa solicitante,

4. Si es empleado de la compañia, el empleado podrá suministrar los 6 últimos dígitos de su documento
de identidad, como clave de entrada (min=3 empleados),

5. Al introducir la clave debe visualizarse en la pantalla el símbolo *,

6. Si la clave ingresada es correcta deberá encenderse un led verde y sonar un pitido corto simulando
el sonido de la cerradura eléctrica,

7. Si la clave es errada deberá visualizarse un gráfico de alarma en la pantalla y deberá sonar una
alarma que bloquee el sistema, para salir de este estado se debe pulsar un interruptor de seguridad
al que solo se tiene acceso desde la sala de control.

Diseñe el sistema de seguridad que cumpla con estos requerimientos. Para ello cuenta con los siguientes
materiales:

Un Teclado 4x4

Un LCD gráfico con controlador KS0108

Un microcontrolador PIC 18F4550

## Restricciones de diseño:
Solo debe utilizar la configuración de E/S de los puertos, no se aceptarán soluciones donde se
utilice otro módulo del microcontrolador (Interrupciones, CCP, etc).

## Entregas:
## Pre-Informe
Deberá ser colocado en el aula virtual en el espacio denominado Entregas, en la tarea denominada
Pre Laboratorio 01, hasta la fecha indicada en el cronograma.

## Laboratorio
1. El grupo deberá entregar un informe técnico de acuerdo al instructivo publicado en el aula vir-
tual, el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada
Informes de Laboratorio 01 hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Video Tutorial:Creación de
Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula
virtual, el mismo deberá ser montado en youtube, de forma oculta y enlazado al aula virtual en
el espacio denominado Entregas, en la tarea denominada Videos de Laboratorio 01 hasta la fecha
indicada en el cronograma.
