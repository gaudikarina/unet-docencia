# PRÁCTICA 4

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Noviembre 2025). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

Diseñar aplicaciones de manejo de la transmisión síncrona serial.


Objetivos

- Gestionar la configuración del conversor analógico-digital del PIC 18F4550.

- Configurar la interfaz de comunicación serie SCI del PIC 18F4550.

- Implementar la conversión analógica a digital utilizando el microcontrolador PIC 18F4550.

- Utilizar la interfaz de comunicación serie SCI para transmitir datos.

- Resolver problemas específicos relacionados con la conversión analógica-digital y la comunicación serie.

## Pre-Laboratorio:

Cada estudiante debe investigar y documentar brevemente lo siguiente:

- Investigar el funcionamiento de los sensores asignados y la relación entre las variables medidas y los valores digitales.

- Estudiar el funcionamiento del conversor analógico-digital del PIC 18F4550.

- Listar las directivas del compilador y funciones en C utilizadas para el conversor analógico-digital y la interfaz de comunicación serie SCI.

- Familiarizarse con la pantalla LCD 16x2 y su uso en la visualización de datos.

Información Preliminar

## Configuración de dos puertos serie USART

- Por Hardware:

- Utiliza la configuración normal conocida, se le adiciona el parámetro stream el cual es el identificador del puerto serie.

- #use rs232(baud=9600, xmit=pin_c6, rcv=pin_c7,stream=Remoto)

- Por Software:

- Utiliza la misma configuración conocida
 pero en este caso se define dos pines cualesquiera del PIC como transmisor y
 receptor.

- #use rs232(baud=9600,
 xmit=pin_b0,
 rcv=pin_b1,stream=Monitoreo)

- Funciones:

- Las funciones que se utilizan son fputc, fputchar, fputs, fprintf, fgetc, fgetchar, fgets.

Recepción y Envío de Datos en Comunicación Serial

- Se envía y se recibe son variables de
 tipo char.

- Se debe definir la misma velocidad de
 reloj, tasa de baudios en el emisor y el trasmisor.

- La
 función de ccs de recepción reciben solo un dato tipo char ó
 carácter.

- Para recibir
 varios caracteres por comunicación serial se debe:

- Definir
 un
 arreglo de caracteres
 global.

- Utilizar
 la función kbhit() como
 variable de control para construir el arreglo.

- El
 puntero del arreglo debe inicializarse en el programa
 principal, de esta
 manera cada vez que llegue un dato se actualiza el arreglo.

- El
 puerto serie solo maneja datos tipo char, por lo tanto, deben realizar su
 conversión a tipo int, para su procesamiento matemático, utilicen la
 función atol() de la librería stdlib.h

Laboratorio:

En el laboratorio, cada estudiante implementará un sistema de monitoreo utilizando el PIC 18F4550 y los sensores asignados. El sistema debe incluir:

- Lectura de Sensores: Cada estudiante leerá los datos de su sensor y los convertirá a formato digital.

- Transmisión de Datos: Los datos se enviarán a una sala remota y a un PC.

- Detección de Alarmas: Se activarán alarmas (LEDs, zumbadores) si las variables medidas exceden los límites establecidos.

- Interacción con PC: El sistema recibirá comandos desde la PC para configurar efectos en luces y lámparas de emergencia.

## Actividades:

- Configuración del Microcontrolador: Cada estudiante configurará el PIC 18F4550 para leer su sensor y enviar datos.

- Visualización en LCD: Los datos se mostrarán en un LCD 16x2 en la habitación.

- Recepción de Datos en Sala Remota: Los datos se procesarán y mostrarán en un LCD 16x2 en la sala remota.

- Interacción con el Usuario: Desde la PC, el usuario podrá visualizar datos en tiempo real.

- Activación de alarmas: Cada caso tendrá valores de offset para activación alarmas visuales o sonoras.

## Asignación de Casos por Grupo

 Grupos 
Sensores Asignados 
Variables Medidas 
Alarmas 
Sala Remota 
PC (Virtual Terminal) 
01 
LDR,

MPXA6115A6U

 
Iluminancia,

Presión

 
Si lux>50

Si P<75 kPa

 
Led parpadea 

Alarma

 
Visualiza Valores con el titulo "Sala de Monitoreo" 
03 
MPXA6115A6U,

HIH5030

 
Presión,

Humedad

 
Si P>100 kPa

Si humedad<25%

 
Alarma

Led parpadea 

 
Visualiza Valores con el titulo "Sala de Monitoreo" 
02 
HIH5030,

GP2Y0A21

 
Humedad,

Distancia

 
Si humedad = 50%

Si distancia >50 cm

 
Alarma

Led parpadeante

 
Visualiza Valores con el titulo "Sala de Monitoreo" 
04 
GP2Y0A21, 

LDR

 
Distancia,

Iluminancia

 
Si distancia <30 cm, 

Si lux<70

 
Led parpadea 

Alarma

 
Visualiza Valores con el titulo "Sala de Monitoreo" 
## Entregas:

- Video: El estudiante realizará un video explicativo de la solución de la práctica como se indica en el Instructivo de Video Defensa para el Laboratorio de Sistemas Digitales II que
 se encuentra en el aula virtual, el mismo, deberá ser enlazado al aula
 en el espacio de las Actividades Evaluativas denominado Entrega de Video Práctica 04, hasta la fecha indicada en el
 cronograma.
