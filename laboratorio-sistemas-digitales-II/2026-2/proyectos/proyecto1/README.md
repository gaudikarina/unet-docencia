# Proyecto corto: Monitor de Cadena de Frío para Transporte de Vacunas

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Octubre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*


## Objetivos

- Diseñar e implementar un sistema embebido de dos PIC18F4550 (Maestro-Esclavo) para el monitoreo de una caja de transporte refrigerado de vacunas, con enlace UART entre ambos microcontroladores.

- Adquirir dos temperaturas con el módulo ADC de 10 bits y contar las aperturas de puerta con el Timer0 en modo contador, generando la base de tiempo con el Timer1.

- Implementar la evaluación de excursiones térmicas y de permanencia de puerta abierta con prioridad entre alarmas, y el registro de eventos en una memoria EEPROM externa mediante I2C.

- Documentar el desarrollo en un informe técnico con la Bitácora de Prompts IA y defender el sistema ante una modificación en vivo.

## Descripción del Sistema

El sistema supervisa una caja térmica de transporte con dos compartimentos independientes: el compartimento A (vacunas) y el compartimento B (diluyentes). La caja dispone de un contacto que indica el estado de la puerta. El sistema debe detectar excursiones de temperatura fuera de la ventana de conservación de cada compartimento, aperturas prolongadas de la puerta, y dejar un registro persistente de cada evento de alarma.

- PIC Esclavo (adquisición): lee las dos temperaturas, cuenta las aperturas y vigila el estado de la puerta; transmite una trama por segundo al Maestro.

- PIC Maestro (decisión e interfaz): evalúa las condiciones de alarma, gestiona el zumbador, los indicadores y la EEPROM, y presenta la información en el LCD 20x4 y en la Virtual Terminal.

## Parámetros de Operación

Parámetro | Valor 
Ventana de conservación del compartimento A | 2,0 °C a 8,0 °C 
Ventana de conservación del compartimento B | 15,0 °C a 25,0 °C 
Tolerancia de excursión térmica acumulada | 10 minutos operativos (escala: 1 s de simulación = 1 minuto operativo) 
Tiempo máximo de puerta abierta continua | 45 s (tiempo real de simulación) 
Prioridad de alarmas (mayor a menor) | Puerta > Térmica A > Térmica B 
Capacidad del registro de eventos | 32 registros, memoria circular 
Pérdida de enlace inter-micro | Sin tramas válidas durante 3 s 
## Protocolo Inter-Micro

Trama Esclavo → Maestro cada 1 s, en ASCII: $TA,TB,P,N<LF>. TA y TB: temperaturas en décimas de °C (entero). P: estado de la puerta (0 = cerrada, 1 = abierta). N: aperturas acumuladas desde el arranque (0 a 65535). Las tramas con formato incorrecto deben descartarse.

## Requerimientos Funcionales

- El Esclavo debe adquirir las temperaturas de los compartimentos A y B (sensores LM35, 10 mV/°C) con el ADC de 10 bits y convertirlas a °C en variables flotantes.

- El Esclavo debe contar con el Timer0 (modo contador, flanco descendente en T0CKI) las aperturas de puerta, determinar el estado de la puerta por el nivel de la misma señal y generar con el Timer1 una base de tiempo de 1 s que dispare la transmisión de la trama.

- El Maestro debe recibir las tramas por interrupción de recepción serie (#INT_RDA) sin pérdida de caracteres, validar su formato y mostrar «ENLACE PERDIDO» en el LCD con el zumbador activo cuando se cumpla la condición de pérdida de enlace.

- El Maestro debe acumular el tiempo operativo durante el cual cualquiera de los dos compartimentos permanece fuera de su ventana, y activar la alarma térmica correspondiente cuando el acumulado supere la tolerancia.

- El Maestro debe activar la alarma de puerta cuando la puerta permanezca abierta de forma continua por más del tiempo máximo establecido.

- Cuando coincidan varias alarmas, la línea de estado del LCD y de la consola debe mostrar la de mayor prioridad; el zumbador debe permanecer activo mientras exista al menos una alarma.

- Al iniciar cada alarma, el Maestro debe grabar en la EEPROM 24C64 un registro de 8 bytes: código de evento (1 = puerta, 2 = térmica A, 3 = térmica B), TA (2 bytes), TB (2 bytes), N módulo 256 (1 byte) y minuto operativo (2 bytes). El puntero de escritura y el contador de registros deben conservarse en las direcciones 0x0000 y 0x0001, y los registros comienzan en 0x0010.

- El pulsador CONSULTA debe mostrar en el LCD y en la consola, en cada pulsación, el siguiente registro desde el más reciente al más antiguo. El pulsador RECONOCER (interrupción INT2) debe silenciar el zumbador y reiniciar el acumulado de excursión térmica.

- El LCD debe distribuir la información en cuatro líneas: temperaturas A y B; estado de la puerta y aperturas acumuladas; excursión acumulada en minutos; estado general o alarma vigente.

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

- La memoria EEPROM 24C64 debe conectarse al bus I2C del Maestro (SDA/SCL del módulo MSSP) con resistencias de pull-up de 4,7 kΩ y líneas de dirección A0–A2 a masa. Por compartir pines con el MSSP, el Maestro no utiliza INT0 ni INT1.

- La escala de 1 s = 1 minuto operativo aplica únicamente al acumulado de excursión térmica.

## Distribución Física de Conexiones

PIC Esclavo

Pin | Función | Dispositivo / Observación 
RA0 (AN0) | Entrada analógica | LM35 del compartimento A 
RA1 (AN1) | Entrada analógica | LM35 del compartimento B 
RA4 (T0CKI) | Entrada del Timer0 (contador) y lectura de nivel | Contacto de puerta con pull-up de 10 kΩ; nivel BAJO = puerta abierta 
RC6 (TX) / RC7 (RX) | UART inter-micro | Cruzados con RC7 / RC6 del Maestro 
OSC1 / OSC2 | Reloj | Cristal de 20 MHz con capacitores de 22 pF 
PIC Maestro

Pin | Función | Dispositivo / Observación 
RD0–RD7 | LCD 20x4 | Asignación de la librería lcd.c 
RB0 (SDA) / RB1 (SCL) | Bus I2C | EEPROM 24C64 con pull-ups de 4,7 kΩ 
RB2 (INT2) | Entrada de interrupción | Pulsador RECONOCER (flanco descendente) 
RB5 | Entrada digital | Pulsador CONSULTA 
RB3 | Salida serie por software | Consola: Virtual Terminal 
RA0 | Salida digital | Zumbador 
RA1 | Salida digital | LED rojo (alarma) 
RA2 | Salida digital | LED verde (normal) 
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
