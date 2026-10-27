# Proyecto corto: Estación de Envasado con Control de Peso y Clasificación

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Octubre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*


## Objetivos

- Diseñar e implementar un sistema embebido de dos PIC18F4550 (Maestro-Esclavo) para una estación de envasado con control de peso, con enlace UART entre ambos microcontroladores.

- Adquirir el peso con el módulo ADC de 10 bits, contar envases con el Timer1 en modo contador y accionar una tolva con servomotor mediante el módulo CCP en modo comparación.

- Implementar la secuencia de llenado, pesaje y clasificación de cada envase con control de lote y detención por rechazos consecutivos.

- Documentar el desarrollo en un informe técnico con la Bitácora de Prompts IA y defender el sistema ante una modificación en vivo.

## Descripción del Sistema

El sistema llena envases de forma individual sobre una banda transportadora. Un sensor detecta la llegada de cada envase; la tolva se abre hasta alcanzar el peso objetivo, se cierra anticipadamente para compensar el material en caída, y el envase se clasifica como conforme o rechazado según su peso. El peso se simula con un potenciómetro que representa la celda de carga.

- PIC Esclavo (adquisición): mide el peso promediando 8 muestras del ADC por trama, cuenta los envases detectados y transmite una trama cada 200 ms.

- PIC Maestro (proceso e interfaz): ejecuta la secuencia de envasado, controla banda y tolva, clasifica los envases, gestiona el lote y presenta la información en el LCD 20x4 y en la Virtual Terminal.

## Parámetros de Operación

Parámetro | Valor 
Peso objetivo | 250 g 
Tolerancia de conformidad | ±3 % del peso objetivo 
Anticipo de cierre de tolva | 5 g (cierre al alcanzar el objetivo menos el anticipo) 
Tiempo de asentamiento antes del pesaje | 500 ms 
Tamaño del lote | 12 envases procesados (conformes más rechazados) 
Rechazos consecutivos para detención | 3 
Posiciones del servo de tolva | Cerrada 0°; abierta 90° 
Escala de la celda de carga | 0–5 V = 0–500 g 
## Protocolo Inter-Micro

Trama Esclavo → Maestro cada 200 ms, en ASCII: $W,N<LF>. W: peso en décimas de gramo (entero). N: envases contados desde el arranque (0 a 65535).

## Requerimientos Funcionales

- El Esclavo debe adquirir el peso con el ADC de 10 bits promediando 8 muestras, convertirlo a gramos en variables flotantes y generar con el Timer0 la base de 200 ms para la transmisión.

- El Esclavo debe contar con el Timer1 (modo contador, entrada T1CKI) los pulsos del sensor de envase.

- El Maestro debe recibir las tramas por interrupción de recepción serie (#INT_RDA) y validarlas.

- El pulsador INICIO LOTE (interrupción INT2) debe iniciar o reiniciar un lote, poniendo en marcha la banda.

- Secuencia por envase: la banda avanza hasta que el contador N se incrementa; la banda se detiene y la tolva se abre; al alcanzar el peso objetivo menos el anticipo, la tolva se cierra; tras el tiempo de asentamiento se toma la siguiente trama como peso final.

- El Maestro debe clasificar el envase como CONFORME si su peso está dentro de la tolerancia y como RECHAZO en caso contrario, encendiendo el LED de rechazo durante 1 s y actualizando los contadores de conformes y rechazados; luego debe reanudar la banda.

- Al acumular tres rechazos consecutivos, el Maestro debe detener la banda, activar el zumbador y mostrar «PARO POR RECHAZOS»; el sistema se rearma con INICIO LOTE.

- Al completar el tamaño de lote, el Maestro debe detener la banda y mostrar «LOTE COMPLETO» con el total de conformes y rechazados.

- El LCD debe distribuir la información en cuatro líneas: peso instantáneo; estado de la secuencia (ESPERA, LLENADO, ASENTAMIENTO, CLASIFICACIÓN); envases procesados, conformes y rechazados; mensaje de lote o alarma vigente.

Restricciones de diseño:

- Dos microcontroladores PIC18F4550. El archivo de cabecera incluido en cada programa debe corresponder exactamente al componente colocado en Proteus.

- #fuses HS,NOWDT,NOPROTECT,NOLVP y #use delay(crystal=20MHz), con cristal de 20 MHz y dos capacitores de 22 pF en OSC1/OSC2 de cada PIC.

- Enlace inter-micro: UART por hardware, 9600 baudios, 8N1, con RC6 (TX) y RC7 (RX) conectados en cruce entre ambos PIC y masa común.

- Consola: Virtual Terminal conectada al Maestro mediante un segundo canal serie por software (#use rs232 con stream, solo transmisión en RB3, 9600 baudios, 8N1), sin compartir el canal inter-micro.

- El pin RC3 no existe en el encapsulado DIP-40 del PIC18F4550 y no debe utilizarse. No se admite el bus SPI.

- Los puertos con función analógica deben configurarse explícitamente (setup_adc_ports) en ambos PIC: solo los canales requeridos como analógicos y el resto como E/S digital.

- LCD 20x4 en el Maestro con la librería lcd.c, que reserva todo el puerto D del Maestro.

- Las conversiones ADC deben ser de 10 bits; los valores físicos se calculan en variables de punto flotante y se presentan con una cifra decimal.

- El programa principal de ambos microcontroladores no debe contener esperas bloqueantes (delay_ms) superiores a 50 ms; la temporización se resuelve con Timers e interrupciones.

- La señal del servo (período de 20 ms, pulso de 1,0 ms = 0° y 1,5 ms = 90°) debe generarse con el CCP1 en modo comparación y el Timer1 del Maestro, que queda reservado a esa función; las demás bases de tiempo del Maestro deben emplear el Timer0 u otro temporizador.

- En esta arquitectura no se emplea el bus I2C.

- El sensor de envase se simula con un generador de pulsos o pulsador conectado a T1CKI del Esclavo.

## Distribución Física de Conexiones

PIC Esclavo

Pin | Función | Dispositivo / Observación 
RA0 (AN0) | Entrada analógica | Potenciómetro (celda de carga simulada) 
RC0 (T1CKI) | Entrada del Timer1 (contador) | Sensor de envase (generador de pulsos o pulsador) 
RC6 (TX) / RC7 (RX) | UART inter-micro | Cruzados con RC7 / RC6 del Maestro 
OSC1 / OSC2 | Reloj | Cristal de 20 MHz con capacitores de 22 pF 
PIC Maestro

Pin | Función | Dispositivo / Observación 
RD0–RD7 | LCD 20x4 | Asignación de la librería lcd.c 
RC2 (CCP1) | Salida del servo (comparación + Timer1) | Servomotor de la tolva 
RA0 | Salida digital | Banda transportadora (relé o transistor) 
RA1 | Salida digital | LED de rechazo 
RA2 | Salida digital | Zumbador 
RB2 (INT2) | Entrada de interrupción | Pulsador INICIO LOTE (flanco descendente) 
RB3 | Salida serie por software | Consola: Virtual Terminal 
RC6 (TX) / RC7 (RX) | UART inter-micro | Cruzados con RC7 / RC6 del Esclavo 
OSC1 / OSC2 | Reloj | Cristal de 20 MHz con capacitores de 22 pF 
## Hitos del Proyecto

- Semana 3 (lanzamiento): esquemático completo en Proteus con ambos microcontroladores y mapa de pines verificado.

- Semana 4 (desarrollo): firmware del Esclavo y del Maestro, integración del enlace UART y de la lógica de decisión.

- Semana 5 (entrega): Informe Escrito con Bitácora de Prompts IA (30 %) y Entrevista Relámpago Individual (25 %).

## Evaluación y Entregables del Proyecto

El Proyecto Corto se califica con dos componentes independientes: el Informe Escrito con Bitácora IA (30 %) y la Entrevista Relámpago Individual (25 %).

## Informe Escrito (30 %)

Entrega en PDF, letra Times New Roman 12 pt, tamaño carta, orientación vertical, márgenes superior 3 cm, inferior 2 cm, derecho 3 cm e izquierdo 2 cm. Títulos en negrita 14 pt centrados; subtítulos en negrita 12 pt justificados a la izquierda. Estructura obligatoria:

- Portada conforme al modelo institucional: Universidad Nacional Experimental del Táchira; Vicerrectorado Académico; Decanato de Docencia; Departamento de Ingeniería Electrónica; Núcleo de Electrónica y Sistemas Digitales; Laboratorio de Sistemas Digitales II; «Informe Proyecto Corto»; título del proyecto; autor (nombres y apellidos, CIV); San Cristóbal, mes y año.

- Introducción: mínimo cuatro párrafos que enmarquen al lector en el contenido del informe.

- Marco Teórico: periféricos del PIC18F4550 empleados, protocolo de comunicación utilizado y algoritmo de decisión del sistema.

- Diseño Metodológico: (a) configuración de los periféricos y los puertos de cada PIC; (b) diagrama esquemático del montaje en Proteus; (c) diagrama de flujo del programa principal y de cada función en ambos microcontroladores; (d) procedimiento de diseño de la aplicación, con el uso de la IA generativa para la base del firmware y las correcciones realizadas manualmente.

- Resultados: por cada requerimiento funcional, el código CCS C correspondiente, la referencia al montaje de Proteus y la evidencia de la simulación.

- Conclusiones.

- Referencias Bibliográficas en formato IEEE.

- Anexos: enlace de descarga de los archivos de compilación (CCS C) y de simulación (Proteus), y la Bitácora de Prompts IA.

## Bitácora de Prompts IA

El diseño del firmware se realiza en co-diseño con una IA generativa (ChatGPT, Gemini, Claude u otra). Es obligatorio entregar el hilo completo desde el Mensaje 1, con el código crudo original y completo generado por la IA antes de las correcciones manuales:

- Google Gemini: exportar el chat completo a un archivo PDF y adjuntarlo en Moodle junto con el informe.

- Otra IA: generar el enlace público oficial de chat compartido y pegarlo en el campo de texto en línea de Moodle al realizar la entrega.

## Entrevista Relámpago Individual (25 %)

La entrevista es individual. Se debe presentar el sistema funcionando en Proteus según las especificaciones de este instructivo y explicar la lógica del diseño. Durante la entrevista se formula un requerimiento no anunciado previamente que debe resolverse en el momento: localizar la lógica pertinente en CCS C (puertos, condiciones, variables), implementar el cambio, compilar sin errores y demostrar el nuevo comportamiento en la simulación de Proteus.
