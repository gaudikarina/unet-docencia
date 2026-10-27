# PRÁCTICA 3

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Noviembre 2025). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

Conversión Analógica a Digital con PIC18F4550


Objetivos

- Configurar correctamente el módulo de conversión analógica a digital (ADC) del microcontrolador PIC18F4550.

- Implementar la lectura de señales analógicas desde sensores usando el ADC.

- Mostrar los valores medidos en un LCD alfanumérico.

- Resolver un problema de monitoreo utilizando entradas analógicas.

- Integrar sensores analógicos reales en una aplicación práctica de adquisición de datos.

## Pre-Laboratorio:

Cada estudiante debe investigar y documentar brevemente lo siguiente:

- Principio de funcionamiento del conversor analógico-digital del PIC18F4550.

- Directivas del compilador necesarias para configurar el ADC en lenguaje CCS de PICC.

- Funciones en C (CSS en PICC) utilizadas para manejar el ADC del PIC18F4550.

- Funcionamiento eléctrico del sensor asignado.

- Relación física → voltaje de salida del sensor asignado vs Variable física.

- Circuito de acondicionamiento de señal necesario para el sensor asignado (si es necesario)

Laboratorio:

En una planta experimental se requiere diseñar un sistema de monitoreo que permita visualizar diversas variables físicas utilizando sensores analógicos. Cada estudiante será responsable de una medición diferente (Ver tabla 01).

## Actividades:

- Diseñar un sistema de adquisición de datos utilizando el microcontrolador PIC18F4550.

- Leer cinco señales analógicas diferentes provenientes de cinco sensores, una por estudiante.

- Mostrar en un LCD alfanumérico de 16x2 los valores medidos en formato legible. Se deben actualizar periódicamente.

- Configurar correctamente el ADC para múltiples canales (AN0 a AN4, por ejemplo).

- Calcular y mostrar en el LCD el valor en unidades físicas (ej. lux, %, kPa, etc.), no solo el valor digital crudo (Voltios).

Tabla 01. Asignación de Sensores

Grupos 
Sensor asignado 
Variable medida 
01 
LDR (fotoresistor) 
Iluminancia (lux aproximado) 
03 
MPXA6115A6U 
Presión (kPa / psi) 
02 
HIH5030 
Humedad relativa (%) 
04 
GP2Y0A21 / GPE2D12 
Distancia (cm) 
## Entregas:

- Video: El estudiante realizará un video explicativo de la solución de la práctica como se indica en el Instructivo de Video Defensa para el Laboratorio de Sistemas Digitales II que
 se encuentra en el aula virtual, el mismo, deberá ser enlazado al aula
 en el espacio de las Actividades Evaluativas denominado Entrega de Video Práctica 03, hasta la fecha indicada en el
 cronograma.
