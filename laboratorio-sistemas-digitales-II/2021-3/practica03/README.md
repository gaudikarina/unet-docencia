# Práctica 3: Diseño de aplicaciones con el módulo I2C y el módulo CCP en microcontrolador PIC.

*Enunciado del Laboratorio de Sistemas Digitales II, Septiembre 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Gestionar la configuración del módulo CCP del PIC 18F4550.

2. Implementar el uso del módulo CCP con un microcontrolador PIC 18F4550.

3. Gestionar la configuración de la interfaz inter circuitos del PIC 18F4550.

4. Implementar el uso de la interfaz inter circuitos del PIC 18F4550.

5. Resolver problema específico combinando el manejo del módulo CCP con la interfaz inter circuitos
del PIC 18F4550.

## Pre-Laboratorio
1. Explicar los tres modos de trabajo del módulo CCP en el PIC 18F4550.

2. Explicar el procedimiento de configuración para cada modo de trabajo del módulo CCP del PIC
18F4550.

3. Indique las funciones en C asociadas al módulo CCP del PIC 18F4550.

4. Explicar en que consiste la interfaz inter circuitos y como funciona en el PIC 18F4550.

5. Listar las directivas de CCS para el manejo de la interfaz inter circuitos del PIC 18F4550.

6. Listar las funciones de CCS para el manejo de la interfaz interfaz inter circuitos del PIC 18F4550.

7. Investigar el funcionamiento del sensor CNY70 y como conectarlo para detección de blanco y negro.

## Laboratorio
Se desea controlar dos motores DC utilizando el módulo CCP del microcontrolador PIC 02
18F4550. Los motores actuarán según tres sensores: dos LDR y un sensor reflectivo (CNY70) como se
muestra en la tabla 1:

Cuadro 1: Comportamiento de los Motores DC01 y DC02

LDR1       LDR2     CNY70 MOTOR DC01                              MOTOR DC02
Obscuridad Obscuridad Blanco Giro horario (velocidad                Giro anti-horario (veloci-
10 %)                                  dad 100 %)
Obscuridad Obscuridad Negro Giro horario (velocidad                 Giro anti-horario (veloci-
20 %)                                  dad 80 %)
Obscuridad    Luz     Blanco Giro horario (velocidad                Giro anti-horario (veloci-
30 %)                                  dad 70 %)
Obscuridad    Luz     Negro Giro anti-horario (veloci-              Giro horario (velocidad
dad 10 %)                              100 %)
Luz     Obscuridad Blanco Giro anti-horario (veloci-             Giro horario (velocidad
dad 80 %)                              20 %)
Luz     Obscuridad Negro Giro anti-horario (veloci-              Giro horario (velocidad
dad 70 %)                              30 %)
Luz        Luz     Blanco Giro anti-horario (veloci-             Giro horario (velocidad
dad 40 %)                              60 %)
Luz        Luz     Negro Giro horario (velocidad                 Giro anti-horario (veloci-
60 %)                                  dad 40 %)

Los sensores se encuentran conectados a un microcontrolador PIC 01 18F4550 y sus datos hacia
los motores deben ser enviados a través del protocolo I2 C hacia el PIC 02, de acuerdo como se muestra
en la figura 1

Figura 1: Diagrama de Distribución.

## Restricciones de diseño:
Los PWM deben ser realizados utilizando el módulo PWM de los CCP de los microcontroladores
y se debe utilizar solo el protocolo I2 C para la comunicación.

## Entregas:
## Laboratorio
1. El grupo deberá entregar un informe técnico de acuerdo al Instructivo publicado en el aula virtual,
el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada Informes
de Laboratorio 03 hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Instructivo para la realización
del Video de Laboratorio que se encuentra en el aula virtual, el mismo deberá ser montado en
youtube (modo oculto) y enlazado al aula en el espacio Entregas, en la tarea denominada Videos
de Laboratorio 03 hasta la fecha indicada en el cronograma.
