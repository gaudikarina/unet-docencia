# PRÁCTICA 2

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Abril 2025). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

Manejo de interrupciones externas del microcontrolador PIC 18F4550.


Objetivos

- Configurar y utilizar interrupciones externas en el PIC18F4550.

- Aplicar niveles de prioridad para interrupciones.

- Implementar un sistema embebido basado en eventos y manejo de señales cuadradas.

- Visualizar estados del sistema mediante un LCD 16x2.

## Pre-Laboratorio:

- Investigar los tipos de interrupciones externas que maneja el PIC 18F4550.

- Explicar cómo se configuran los niveles de prioridad de interrupciones.

- Identificar las directivas del compilador CCS para interrupciones externas.

- Estudiar el uso de interrupts, enable_interrupts(), y ext_int_edge() en CCS.

- Diseñar el mapa de conexión de señales cuadradas de eventos.
Laboratorio:

El sistema simula una empaquetadora de frutas con cuatro bandas (Fresa, Mango, Pera, Manzana), cada una con un sensor que genera una señal cuadrada conectada a una interrupción externa del PIC18F4550. Cada detección incrementa un contador específico por fruta, mostrado en un LCD. Un botón de parada de emergencia (en RB0, INT0) tiene la máxima prioridad y detiene todas las bandas, mostrando "EMERGENCIA" en el LCD. Los contadores no tienen límite (no hay capacidad máxima de 20). El LCD muestra los contadores de frutas y un mensaje de conflicto cuando dos o más interrupciones se superponen. Cada escenario varía en la asignación de interrupciones, prioridades, o condiciones para destacar conflictos y prioridades.

Fruta 
Prioridad 
Velocidad (tiempo entre detecciones) 
Fresa 
Alta (1) 
 250 ms 
Mango 
 Alta (2) 
 200 ms 
Pera 
Baja(3) 
 150 ms 
 Manzana 
Baja (3) 
100 ms 
Conexiones Base:

- 4 entradas para interrupciones externas (RB0, RB1, RB2, RB3).

- LCD 16x2 (modo 4 bits).

- 4 LEDs (uno por fruta) para indicar detección.

- 1 botón de parada de emergencia (RB0).

Interrupciones:

- INT0: Parada de emergencia (siempre alta prioridad).

- INT1, INT2, RBIF: Asignadas según el escenario, con prioridades configurables.
LCD: Muestra contadores (Fresa, Mango, Pera, Manzana) y mensajes:

- Normal: "F:x M:y P:z A:w" (x, y, z, w son contadores).

- Emergencia: "EMERGENCIA".

- Conflicto: "CONFLICTO" (cuando interrupciones se superponen).

## Detección de Conflictos

Un conflicto ocurre cuando dos o más interrupciones se disparan simultáneamente o una interrupción de baja prioridad es interrumpida por una de mayor prioridad. Esto se detecta:

- En Alta Prioridad: Si múltiples banderas (INT0IF, INT1IF, INT2IF) están activas al entrar al manejador de interrupciones de alta prioridad.

- En Baja Prioridad: Si RBIF se dispara mientras se procesa otra interrupción o si múltiples pines RB cambian.

- Visualización: Mostrar "CONFLICTO" en el LCD durante 100ms.

Figura 01. Empaquetadora de Frutas

## Grupos

## Grupo 4

## RBIF para Frutas de Baja Prioridad

- Descripción: Asigna Fresa a INT1, Mango a INT2, y ambas Pera y Manzana a RBIF (RB4, RB5). Parada de emergencia en INT0. Enfocado en saturar RBIF para mostrar conflictos.

- Configuración de Interrupciones:

- INT0 (RB0): Parada de Emergencia (máxima prioridad).

- INT1 (RB1): Fresa (alta prioridad, INT1IP = 1).

- INT2 (RB2): Mango (alta prioridad, INT2IP = 1).

- RBIF (RB4): Pera (baja prioridad, RBIP = 0).

- RBIF (RB5): Manzana (baja prioridad).

- Conflicto: Detectado si RB4 y RB5 cambian simultáneamente o si RBIF es interrumpido por INT0/INT1/INT2.

## Grupo 3

## Todas las Frutas en RBIF

- Descripción: Asigna todas las frutas a RBIF (Fresa en RB4, Mango en RB5, Pera en RB6, Manzana en RB7). Parada de emergencia en INT0. Enfocado en mostrar conflictos dentro de RBIF y la prioridad de INT0.

- Configuración de Interrupciones:

- INT0 (RB0): Parada de Emergencia (máxima prioridad).

- RBIF (RB4): Fresa (baja prioridad, RBIP = 0).

- RBIF (RB5): Mango (baja prioridad).

- RBIF (RB6): Pera (baja prioridad).

- RBIF (RB7): Manzana (baja prioridad).

- Conflicto: Detectado si múltiples pines RB4-RB7 cambian simultáneamente.

## Grupo 2

## Prioridad Baja para INT2

- Descripción: Asigna Fresa a INT1, Mango a INT2 (baja prioridad), Pera a RBIF (RB4), Manzana a RBIF (RB5). Parada de emergencia en INT0. Enfocado en mostrar INT2 con baja prioridad.

- Configuración de Interrupciones:

- INT0 (RB0): Parada de Emergencia (máxima prioridad).

- INT1 (RB1): Fresa (alta prioridad, INT1IP = 1).

- INT2 (RB2): Mango (baja prioridad, INT2IP = 0).

- RBIF (RB4): Pera (baja prioridad, RBIP = 0).

- RBIF (RB5): Manzana (baja prioridad).

- Conflicto: Detectado si INT1IF e INT2IF están activos o si RBIF coincide con INT2.

## Grupo 1

## Conflictos por Concurrencia de Interrupciones Externas

Descripción: Asigna Fresa a INT1, Mango a INT2, Pera a RBIF (RB4), Manzana a RBIF (RB5). Parada de emergencia en INT0. Enfocado en conflictos por señales externas concurrentes, visualizando prioridades y superposiciones.

Configuración de Interrupciones:

- INT0 (RB0): Parada de Emergencia (máxima prioridad).

- INT1 (RB1): Fresa (alta prioridad, INT1IP = 1).

- INT2 (RB2): Mango (alta prioridad, INT2IP = 1).

- RBIF (RB4): Pera (baja prioridad, RBIP = 0).

- RBIF (RB5): Manzana (baja prioridad).

Conflicto: Detectado si INT1IF e INT2IF están activos simultáneamente, RB4 y RB5 cambian juntos, o RBIF coincide con INT1/INT2. Muestra "CONFLICTO" en LCD por 100ms.

## Entregas:

- Video: El grupo realizará un video explicativo de la solución de la práctica como se indica en el Instructivo de Video Defensa para el Laboratorio de Sistemas Digitales II que
 se encuentra en el aula virtual, el mismo, deberá ser enlazado al aula
 en el espacio de las Actividades Evaluativas denominado Entrega de Video Práctica 02, hasta la fecha indicada en el
 cronograma.
