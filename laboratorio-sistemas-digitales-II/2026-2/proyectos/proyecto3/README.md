# Proyecto corto: Control de Ascensor de Cuatro Pisos con Prioridad de Llamadas

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Octubre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*


## Objetivos

- Diseñar e implementar un sistema embebido de dos PIC18F4550 (Maestro-Esclavo) para el control de un ascensor de cuatro pisos, con enlace UART bidireccional entre ambos microcontroladores.

- Gestionar las llamadas de piso con interrupción por cambio de estado (INT_RB) y la parada de emergencia con la interrupción externa INT0.

- Controlar la velocidad del motor de la cabina con PWM del módulo CCP y temporizar las puertas y el tiempo de trayecto con un Timer.

- Documentar el desarrollo en un informe técnico con la Bitácora de Prompts IA y defender el sistema ante una modificación en vivo.

## Descripción del Sistema

El sistema controla una cabina que sirve cuatro pisos. Cuatro pulsadores registran las llamadas, cuatro sensores indican la presencia de la cabina en cada piso y un pulsador de emergencia detiene el sistema. El movimiento de la cabina se simula mediante el accionamiento manual de los sensores de piso en Proteus. Un piso tiene prioridad de servicio sobre el orden normal de atención.

- PIC Esclavo (botonera y sensores): atiende por interrupción las llamadas y la emergencia, lee los sensores de piso, enciende los LED de llamada registrada y comunica los eventos al Maestro.

- PIC Maestro (control de la cabina): mantiene la cola de llamadas, decide el destino, controla el motor con PWM y el sentido de giro, gestiona puertas, fallas y emergencia, y presenta la información en el LCD 20x4 y en la Virtual Terminal.

## Parámetros de Operación

Parámetro | Valor 
Piso prioritario | Piso 3 
Tiempo de puertas abiertas | 3 s 
Velocidad de crucero (PWM) | 70 % de ciclo de trabajo 
Velocidad de aproximación (PWM) | 40 %, al pasar por el piso inmediatamente anterior al destino 
Frecuencia de la señal PWM | Mayor o igual a 1 kHz 
Tiempo máximo de trayecto entre sensores de piso consecutivos | 6 s 
Cola de llamadas | Una llamada pendiente por piso 
## Protocolo Inter-Micro

Mensajes ASCII terminados en <LF>. Esclavo → Maestro: Ln (llamada al piso n, n = 1 a 4), Sn (cambio de estado del sensor del piso n; se envía al activarse), E (activación de emergencia). Maestro → Esclavo: An (llamada n atendida; apaga el LED correspondiente).

## Requerimientos Funcionales

- El Esclavo debe atender con la interrupción INT_RB (RB4–RB7) las llamadas de los pisos 1 a 4, registrar cada una, encender su LED y transmitir el mensaje Ln; una llamada ya registrada no debe duplicarse.

- El Esclavo debe atender la parada de emergencia con la interrupción INT0 (flanco descendente), transmitir E y vigilar los sensores de piso, transmitiendo Sn en cada activación.

- El Maestro debe recibir los mensajes por interrupción de recepción serie (#INT_RDA), mantener la cola de llamadas y determinar el piso actual a partir de los sensores.

- La cabina debe mantener su sentido de marcha atendiendo, en el orden de los pisos de paso, las llamadas pendientes en ese sentido, e invertirlo cuando no existan llamadas adelante.

- Una llamada al piso prioritario debe convertirse en el destino inmediato una vez completada la parada o el trayecto en curso, anulando el orden por sentido.

- El motor debe controlarse con PWM del CCP1 y los bits de dirección del L293D: velocidad de crucero durante el trayecto y velocidad de aproximación desde el piso inmediatamente anterior al destino. Al llegar, el motor debe detenerse, las puertas permanecer abiertas el tiempo establecido y el Maestro enviar An.

- Si no se activa el sensor del piso siguiente dentro del tiempo máximo de trayecto, el Maestro debe detener el motor, activar el zumbador y mostrar «FALLA DE TRAYECTO».

- Ante la emergencia, el Maestro debe detener el motor de inmediato (PWM al 0 % y bits de dirección inactivos), activar el zumbador de forma continua, mostrar «EMERGENCIA» y vaciar la cola. Una segunda activación de INT0 debe liberar la emergencia, dejando la cabina detenida a la espera de nuevas llamadas; el mismo procedimiento libera la falla de trayecto.

- El LCD debe distribuir la información en cuatro líneas: piso actual y sentido (SUBE / BAJA / PARADO); destino; llamadas pendientes de los pisos 1 a 4; estado general o alarma vigente.

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

- En el Esclavo, INT_RB y INT0 deben configurarse con prioridades diferenciadas, con INT0 de mayor prioridad.

- El Esclavo debe habilitar las resistencias de pull-up del puerto B; en reposo las entradas están en nivel ALTO y el accionamiento corresponde a nivel BAJO.

- En esta arquitectura no se emplea el bus I2C.

- El movimiento de la cabina se simula accionando manualmente los sensores de piso en Proteus, en la secuencia correspondiente al trayecto.

## Distribución Física de Conexiones

PIC Esclavo

Pin | Función | Dispositivo / Observación 
RA0–RA3 | Entradas digitales | Sensores de piso 1 a 4 (nivel BAJO = cabina en el piso), con pull-up de 10 kΩ 
RB0 (INT0) | Interrupción externa | Pulsador de emergencia (flanco descendente) 
RB4–RB7 (INT_RB) | Interrupción por cambio de estado | Pulsadores de llamada de los pisos 1 a 4 
RD0–RD3 | Salidas digitales | LED de llamada registrada de los pisos 1 a 4 
RC6 (TX) / RC7 (RX) | UART inter-micro | Cruzados con RC7 / RC6 del Maestro 
OSC1 / OSC2 | Reloj | Cristal de 20 MHz con capacitores de 22 pF 
PIC Maestro

Pin | Función | Dispositivo / Observación 
RD0–RD7 | LCD 20x4 | Asignación de la librería lcd.c 
RC2 (CCP1) | Salida PWM | Habilitación (EN1) del driver L293D del motor 
RA0 | Salida digital | Entrada IN1 del L293D (subir) 
RA1 | Salida digital | Entrada IN2 del L293D (bajar) 
RA2 | Salida digital | Zumbador 
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
