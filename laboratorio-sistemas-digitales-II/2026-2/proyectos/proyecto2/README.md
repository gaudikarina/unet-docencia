# Proyecto corto: Incubadora Automática de Huevos con Volteo Programado

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Octubre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*


## Objetivos

- Diseñar e implementar un sistema embebido de dos PIC18F4550 (Maestro-Esclavo) para el control de una incubadora de huevos, con enlace UART entre ambos microcontroladores.

- Adquirir temperatura y humedad con el módulo ADC de 10 bits y generar la señal de un servomotor de volteo con el módulo CCP en modo comparación.

- Implementar el control de temperatura y humedad con histéresis y la programación del ciclo de incubación por etapas, utilizando un reloj de tiempo real DS1307 por I2C.

- Documentar el desarrollo en un informe técnico con la Bitácora de Prompts IA y defender el sistema ante una modificación en vivo.

## Descripción del Sistema

El sistema controla una incubadora con calefactor, humidificador y bandeja de huevos accionada por un servomotor de volteo. El ciclo de incubación se divide en dos etapas con condiciones ambientales distintas, cuya duración se mide con el reloj de tiempo real. Los intervalos se expresan en minutos del RTC como escala de demostración del ciclo.

- PIC Esclavo (adquisición): lee temperatura y humedad y transmite una trama cada 500 ms al Maestro.

- PIC Maestro (control e interfaz): mantiene el ciclo de incubación con el RTC, controla calefactor, humidificador y servo, gestiona alarmas y presenta la información en el LCD 20x4 y en la Virtual Terminal.

## Parámetros de Operación

Parámetro | Valor 
Etapa 1: Incubación | Minutos 0 a 12 del ciclo 
Etapa 1: temperatura (calefactor) | Encender por debajo de 37,0 °C; apagar por encima de 38,0 °C 
Etapa 1: humedad (humidificador) | Encender por debajo de 55 %HR; apagar por encima de 65 %HR 
Etapa 1: volteo | Cada 3 minutos, alternando 45° y 135° 
Etapa 2: Eclosión | Minutos 12 a 20 del ciclo 
Etapa 2: temperatura (calefactor) | Encender por debajo de 36,5 °C; apagar por encima de 37,5 °C 
Etapa 2: humedad (humidificador) | Encender por debajo de 65 %HR; apagar por encima de 75 %HR 
Etapa 2: volteo | Suspendido, servo fijo en 90° 
Alarma de temperatura | Fuera de 36,0 °C a 39,0 °C 
Alarma de humedad | Fuera de 40 %HR a 85 %HR 
Prioridad de mensaje | Temperatura > Humedad 
Fin del ciclo | Minuto 20: actuadores apagados y mensaje de fin de ciclo 
## Protocolo Inter-Micro

Trama Esclavo → Maestro cada 500 ms, en ASCII: $T,H<LF>. T: temperatura en décimas de °C (entero). H: humedad relativa en décimas de %HR (entero). Las tramas con formato incorrecto deben descartarse.

## Requerimientos Funcionales

- El Esclavo debe adquirir la temperatura (LM35, 10 mV/°C) y la humedad relativa (potenciómetro que representa 0–5 V = 0–100 %HR) con el ADC de 10 bits, en variables flotantes, y transmitir la trama cada 500 ms con base de tiempo del Timer0.

- El Maestro debe recibir las tramas por interrupción de recepción serie (#INT_RDA) y validarlas.

- El pulsador INICIO (interrupción INT2) debe iniciar el ciclo: el Maestro debe escribir 00:00:00 en el DS1307 y medir el tiempo transcurrido del ciclo a partir de sus registros de minutos y segundos.

- El Maestro debe controlar el calefactor y el humidificador con las bandas de histéresis de la etapa vigente, y cambiar de etapa en el minuto establecido.

- La señal del servo (período de 20 ms, pulso de 1,0 ms = 0°, 1,5 ms = 90°, 2,0 ms = 180°) debe generarse con el módulo CCP1 en modo comparación y el Timer1. En la etapa 1 debe alternarse entre 45° y 135° con el intervalo establecido; en la etapa 2 debe mantenerse en 90°.

- El Maestro debe activar el zumbador y mostrar la alarma de mayor prioridad cuando la temperatura o la humedad salgan de sus límites de alarma.

- Al llegar al minuto final, el Maestro debe apagar calefactor, humidificador y zumbador, detener el servo en 90° y mostrar «FIN DE CICLO».

- El LCD debe distribuir la información en cuatro líneas: temperatura y humedad; etapa vigente y tiempo transcurrido del ciclo; estado de calefactor, humidificador y posición del servo; estado general o alarma vigente. La consola debe emitir un resumen por segundo.

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

- El DS1307 debe conectarse al bus I2C del Maestro (SDA/SCL del módulo MSSP) con pull-ups de 4,7 kΩ, cristal de 32,768 kHz y batería de respaldo de 3 V. Por compartir pines con el MSSP, el Maestro no utiliza INT0 ni INT1.

- El Timer1 del Maestro queda reservado a la generación de la señal del servo; el resto de las bases de tiempo deben emplear otros temporizadores o el RTC.

- Calefactor y humidificador deben accionarse mediante transistor 2N2222 con diodo de protección, o módulo de relé.

## Distribución Física de Conexiones

PIC Esclavo

Pin | Función | Dispositivo / Observación 
RA0 (AN0) | Entrada analógica | LM35 (temperatura) 
RA1 (AN1) | Entrada analógica | Potenciómetro (humedad) 
RC6 (TX) / RC7 (RX) | UART inter-micro | Cruzados con RC7 / RC6 del Maestro 
OSC1 / OSC2 | Reloj | Cristal de 20 MHz con capacitores de 22 pF 
PIC Maestro

Pin | Función | Dispositivo / Observación 
RD0–RD7 | LCD 20x4 | Asignación de la librería lcd.c 
RB0 (SDA) / RB1 (SCL) | Bus I2C | DS1307 con pull-ups de 4,7 kΩ 
RB2 (INT2) | Entrada de interrupción | Pulsador INICIO (flanco descendente) 
RB3 | Salida serie por software | Consola: Virtual Terminal 
RC2 (CCP1) | Salida del servo (comparación + Timer1) | Servomotor de volteo 
RA0 | Salida digital | Calefactor (transistor o relé) 
RA1 | Salida digital | Humidificador (transistor o relé) 
RA2 | Salida digital | Zumbador 
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
