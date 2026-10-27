# PRÁCTICA 1

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Abril 2025). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

Manejo de Puertos de Entrada-Salida del Microcontrolador PIC 18F4550


## Objetivos

- Configurar y gestionar puertos de entrada-salida digitales en el microcontrolador PIC 18F4550 utilizando el compilador CCS.

- Implementar lógica de programación para controlar periféricos digitales (teclado matricial y matrices LED 5x7).

- Diseñar una aplicación que resuelva un caso específico (Mes, Año, Siglo, Día u Hora) para un tablero de viaje en el tiempo, con entrada de datos por teclado y visualización en matrices LED.

- Aplicar técnicas de anti-rebote y polling para un manejo robusto de entradas.

## Pre-Laboratorio

Antes de la práctica, cada estudiante debe realizar las siguientes actividades:

- Investigar directivas en CCS para configurar puertos digitales (ej. #use port, set_tris_x, output_x, output_bit, input_x, input). Elaborar un cuadro comparativo que detalle:

- Función de la directiva.

- Ejemplo de uso (ej. set_tris_b(0x0F) configura RB0-RB3 como entradas y RB4-RB7 como salidas).

- Ventajas y limitaciones.

- Aplicaciones recomendadas.

- Analizar técnicas anti-rebote:

- Hardware: Condensador en paralelo, circuito Schmitt Trigger.

- Software: Retardo de confirmación, contador de rebotes, máquina de estados.

- Explicar cada técnica con un ejemplo práctico y recomendar una para el teclado matricial.

- Definir la técnica polling:

- Describir cómo funciona (lectura repetitiva de un puerto).

- Comparar con el uso de interrupciones.

- Explicar su uso en la lectura del teclado matricial.

- Estudiar la matriz LED 5x7:

- Describir su estructura (5 columnas, 7 filas, 35 LEDs).

- Explicar el modo de conexión (ánodo en filas, cátodo en columnas).

- Detallar el algoritmo de barrido (multiplexación por filas).

- Proponer un patrón para un dígito (ej. "0").

## Laboratorio

Se diseñará un tablero de viaje en el tiempo que muestra un parámetro temporal (Mes, Año, Siglo, Día u Hora) en dos matrices LED 5x7 (un dígito por matriz). Cada estudiante trabajará en un caso específico, implementando una solución única con las siguientes características:

- Entrada: Teclado matricial 4x3 para ingresar un valor numérico (0-9, tecla de confirmación, tecla para seleccionar conteo progresivo/regresivo).

- Salida: Dos matrices LED 5x7 para mostrar un valor de dos dígitos.

- Funcionalidad:

- Configurar el parámetro (Mes: 1-12, Año: 0-99, Siglo: 0-99, Día: 1-31, Hora: 0-23).

- Mostrar el valor ingresado en las matrices LED.

- Permitir elegir entre conteo progresivo (de 0 al valor) o regresivo (del valor a 0).

- Ejecutar el conteo, actualizando las matrices cada segundo.

- Restricciones:

- Usar solo puertos digitales del PIC 18F4550.

- Implementar anti-rebote en software para el teclado.

- Usar polling para la lectura del teclado (no librería predefinida).

## Materiales

- Microcontrolador PIC 18F4550.

- Teclado matricial 4x3.

- Dos matrices LED 5x7 (ánodo en filas, cátodo en columnas).

- Resistencias (330 Ω para LEDs, 10 kΩ para pull-up si es necesario).

- Compilador CCS.

## Asignación de Puertos

Configuración común para todos los casos:

- Teclado matricial:

- Filas: RC0-RC4 (salidas).

- Columnas: RC5-RC7 (entradas con pull-up).

- Matrices LED:

- Filas (compartidas): RB0-RB6 (salidas).

- Columnas matriz 1: RD0-RD4 (salidas).

- Columnas matriz 2: RD5-RD7, RE0-RE1 (salidas).

## Teclado Matricial 4x3

Tabla 01. Disposición del teclado matricial 4x3

## 1

 
## 2

 
## 3

 
## 4

 
## 5

 
## 6

 
## 7

 
## 8

 
## 9

 
## *

 
## 0

 
## #

 
- *: Conteo Ascendente

- #: Conteo Descendente

## Casos Asignados por Grupo

## Grupo 1: Mes

- Rango: 0-12.

- Inicio: Cada contador debe iniciar con un valor que será cargado por teclado.

- Confirmación doble: Requerir que el usuario presione * dos veces consecutivas para confirmar el valor ingresado.

- Memoria de último valor: Almacenar el último valor ingresado en una variable global y mostrarlo como valor inicial al reiniciar el caso.

## Grupo 2: Año

- Rango: 0-99.

- Inicio: Cada contador debe iniciar con un valor que será cargado por teclado.

- Entrada inversa: Permitir ingresar los dígitos en orden inverso (primero unidades, luego decenas). Ejemplo: Para 45, ingresar 5 y luego 4.

- Animación de inicio: Antes de iniciar el conteo, mostrar una animación en las matrices (un patrón de "ola" que enciende LEDs de izquierda a derecha) durante 3 segundos.

## Grupo 3: Día 

- Rango: 1-31.

- Inicio: Cada contador debe iniciar con un valor que será cargado por teclado.

- Tecla de borrado: Asignar la tecla 7 como borrado, permitiendo eliminar el último dígito ingresado (ej. si se ingresa 23 y se presiona 7, vuelve a 2).

- Indicador de progreso: Durante el conteo, encender un LED en RA1 cuando el conteo esté en la primera mitad del rango y apagarlo en la segunda mitad.

## Grupo 4: Hora 

- Rango: 0-23.

- Inicio: Cada contador debe iniciar con un valor que será cargado por teclado.

- Validación Estricta: Si se ingresa un valor fuera del rango (Ej.24), mostrar Er en las matrices led antes de permitir reintentar.

- Selección de conteo visual: Mostrar "UP" para conteo progresivo y "dn" para regresivo en las matrices antes de iniciar el conteo.

## Entrega

Video: Cada grupo realizará un video explicativo de la solución de la práctica, siguiendo el Instructivo de Video Defensa para el Laboratorio de Sistemas Digitales II disponible en el aula virtual. El video deberá ser enlazado en el espacio de Actividades Evaluativas denominado Entrega de Video Práctica 01, hasta la fecha indicada en la plataforma.
