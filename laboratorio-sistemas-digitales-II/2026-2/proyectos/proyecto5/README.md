# Proyecto corto: Cargador de Baterías de Plomo-Ácido con Perfil de Carga en Tres Fases

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Octubre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*


## Objetivos

- Diseñar e implementar un sistema embebido de dos PIC18F4550 (Maestro-Esclavo) para el control de un cargador de batería de plomo-ácido de 12 V, con enlace UART entre ambos microcontroladores.

- Adquirir tensión, corriente y temperatura con el módulo ADC de 10 bits y regular la etapa de potencia con PWM del módulo CCP.

- Implementar el perfil de carga en tres fases (corriente constante, tensión constante y flotación) con protecciones por temperatura y por tiempo máximo.

- Documentar el desarrollo en un informe técnico con la Bitácora de Prompts IA y defender el sistema ante una modificación en vivo.

## Descripción del Sistema

El sistema controla la carga de una batería de plomo-ácido sellada de 12 V. La etapa de potencia se gobierna con una señal PWM, y las magnitudes de la batería se simulan con potenciómetros que el operador ajusta durante la prueba. La regulación se realiza mediante ajuste incremental del ciclo de trabajo según la fase vigente.

- PIC Esclavo (adquisición): mide tensión, corriente y temperatura de la batería y transmite una trama cada 500 ms.

- PIC Maestro (control e interfaz): ejecuta la máquina de estados de la carga, regula el ciclo de trabajo, gestiona protecciones y alarmas y presenta la información en el LCD 20x4 y en la Virtual Terminal.

## Parámetros de Operación

Parámetro | Valor 
Corriente de la fase de corriente constante (CC) | 1,00 A 
Tensión de absorción (fase CV) | 14,40 V 
Tensión de flotación | 13,60 V 
Fin de la fase CV | Corriente menor a 0,15 A de forma sostenida durante 5 s 
Temperatura de corte | 45,0 °C; reanudación por debajo de 40,0 °C 
Tiempo máximo de carga | 90 minutos operativos (escala: 1 s de simulación = 1 minuto operativo) 
Paso de ajuste del ciclo de trabajo | ±2 % por cada trama recibida; límites de 0 % a 90 % 
Banda de regulación | ±0,05 A en CC; ±0,05 V en CV y flotación 
Prioridad de eventos (mayor a menor) | Temperatura > Tiempo máximo > Fin normal 
Escalas de las entradas | Tensión: 0–5 V = 0–16 V; corriente: 0–5 V = 0–4 A; temperatura: LM35 
## Protocolo Inter-Micro

Trama Esclavo → Maestro cada 500 ms, en ASCII: $V,I,T<LF>. V: tensión en centésimas de volt (entero). I: corriente en miliamperios (entero). T: temperatura en décimas de °C (entero).

## Requerimientos Funcionales

- El Esclavo debe adquirir tensión (potenciómetro), corriente (potenciómetro) y temperatura (LM35) con el ADC de 10 bits, convertirlas a unidades físicas en variables flotantes y transmitir la trama cada 500 ms con base de tiempo del Timer0.

- El Maestro debe recibir las tramas por interrupción de recepción serie (#INT_RDA) y validarlas.

- El pulsador INICIO/PARO (interrupción INT2) debe iniciar la carga en la fase CC con un ciclo de trabajo inicial de 10 %, y detenerla (ciclo de trabajo 0 %) si se acciona durante la carga.

- Fase CC: el Maestro debe ajustar el ciclo de trabajo en pasos de 2 % por cada trama para mantener la corriente en el valor establecido dentro de la banda. Al alcanzar la tensión de absorción debe pasar a la fase CV.

- Fase CV: el Maestro debe ajustar el ciclo de trabajo para mantener la tensión de absorción dentro de la banda. Cuando la corriente permanezca por debajo del umbral de fin de fase durante el tiempo establecido, debe pasar a flotación.

- Flotación: el Maestro debe mantener la tensión de flotación dentro de la banda de forma indefinida, indicando «CARGA COMPLETA».

- Protección por temperatura: al superar la temperatura de corte, el ciclo de trabajo debe llevarse a 0 %, activarse el zumbador y mostrarse «TEMPERATURA»; al descender por debajo de la temperatura de reanudación, debe retomarse la fase anterior.

- Protección por tiempo: al exceder el tiempo máximo de carga, el ciclo de trabajo debe llevarse a 0 %, activarse el zumbador y mostrarse «TIEMPO MAXIMO». Cuando coincidan eventos, debe aplicarse la prioridad establecida.

- Los LED de fase deben indicar CC, CV y flotación. El LCD debe distribuir la información en cuatro líneas: tensión y corriente; temperatura y ciclo de trabajo; fase vigente y tiempo transcurrido; estado general o alarma vigente.

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

- La señal PWM debe generarse con el módulo CCP1 en modo PWM por hardware, con frecuencia mayor o igual a 1 kHz, hacia una etapa de potencia con transistor o MOSFET con carga representativa (LED, lámpara o motor).

- El Timer1 del Maestro debe emplearse como base de tiempo de 1 s para el temporizado de la carga.

- En esta arquitectura no se emplea el bus I2C.

- Las magnitudes de la batería se simulan con potenciómetros ajustados manualmente durante la prueba.

## Distribución Física de Conexiones

PIC Esclavo

Pin | Función | Dispositivo / Observación 
RA0 (AN0) | Entrada analógica | Potenciómetro de tensión de batería 
RA1 (AN1) | Entrada analógica | Potenciómetro de corriente 
RA2 (AN2) | Entrada analógica | LM35 (temperatura) 
RC6 (TX) / RC7 (RX) | UART inter-micro | Cruzados con RC7 / RC6 del Maestro 
OSC1 / OSC2 | Reloj | Cristal de 20 MHz con capacitores de 22 pF 
PIC Maestro

Pin | Función | Dispositivo / Observación 
RD0–RD7 | LCD 20x4 | Asignación de la librería lcd.c 
RC2 (CCP1) | Salida PWM | Etapa de potencia (transistor o MOSFET) 
RA0 | Salida digital | LED fase CC 
RA1 | Salida digital | LED fase CV 
RA2 | Salida digital | LED flotación 
RA3 | Salida digital | Zumbador 
RB2 (INT2) | Entrada de interrupción | Pulsador INICIO/PARO (flanco descendente) 
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
