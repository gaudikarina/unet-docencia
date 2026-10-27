# PRÁCTICA 4

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Julio 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Sistemas de Control Supervisado por Terminal: Comunicación Serie Asíncrona (USART) e Interfaz de Comandos ASCII Asistida por Inteligencia Artificial

## Objetivos

- Configurar el módulo USART por hardware del PIC18F4550 para transmisión y recepción asíncrona a 9600 baudios utilizando las directivas nativas de CCS C Compiler.

- Desarrollar un intérprete de comandos ASCII no bloqueante para decodificar instrucciones de navegación enviadas desde una PC o terminal de simulación.

- Implementar un protocolo básico de telemetría para transmitir cíclicamente el estado operacional del robot (estado de los motores y velocidad estimada).

- Integrar el Virtual Terminal de Proteus (o terminales externos portables como Hercules) como interfaz de supervisión de bajo consumo de recursos de hardware.

- Utilizar herramientas de Inteligencia Artificial Generativa (LLMs) como co-pilotos para estructurar un parser de cadenas de texto eficiente y libre de retardos prohibitivos.

## Pre-Laboratorio (Ingeniería Asistida por IA)

Cada estudiante debe preparar de manera individual el reporte técnico que incluya:

- Análisis del Módulo USART del PIC18F4550: Diseñar una tabla resumen detallando el rol de los registros TXSTA, RCSTA y la fórmula de cálculo para el registro generador de baudrate (SPBRG) operando a 9600 baudios con un cristal de 20MHz.

- Estudio de Recepción No Bloqueante: Explicar detalladamente por qué el uso de la función getc() o gets() sin una validación previa de la bandera del búfer (kbhit()) detiene la ejecución del lazo principal del robot, y cómo resolverlo para no perder el control de los motores.

- Fase de Co-Piloto IA (Bitácora de Prompts Obligatoria): Deberás interactuar con una IA Generativa para solicitar la estructura base del decodificador de caracteres ASCII asignado a tu grupo, adjuntando la respectiva Bitácora en PDF o enlace compartido.

## Laboratorio: Plataforma del Microrobot Diferencial

 Se modificará el firmware del prototipo móvil diferencial de modo que, además de responder al teclado local, pueda ser controlado de forma remota mediante un enlace serie simulado. La pantalla LCD 16x2 y el terminal de Proteus actuarán en sincronía para desplegar la telemetría del sistema en tiempo real.

## Distribución Física de Conexiones (Hardware Común)

- Módulo USART por Hardware (Enlace PC / Terminal):

- Pin RC6 (TX): Transmisión conectada al RXD del Virtual Terminal.

- Pin RC7 (RX): Recepción conectada al TXD del Virtual Terminal.

- Configuración de Enlace: 9600 Baudios, 8 bits de datos, 1 bit de parada, sin paridad.

- Driver L293D & Motores (Pines de la Práctica 1):

- Motor Izquierdo: Controlado por pines RB0 y RB1.

- Motor Derecho: Controlado por pines RB2 y RB3.

- Módulo de Telemetría: Pantalla LCD 16x2 conectada de forma estándar al Puerto D (Manejo con <lcd.c>).

## Lógica de Control Base (Comportamiento Inicial)

 El firmware inicial cooperativo debe escuchar de forma asíncrona la llegada de caracteres simples enviados desde el terminal virtual para modificar la navegación del robot:

- Teclas de Control Remoto: El microcontrolador reacciona inmediatamente al recibir de forma serie los caracteres en mayúsculas:

- 'A': Avanzar ambos motores (RB0=1, RB1=0, RB2=1, RB3=0).

- 'P': Parada estricta de ambos motores (RB0=0, RB1=0, RB2=0, RB3=0).

- Pantalla LCD: Línea 1 muestra el estado actual ("NAV: AVANZA" o "NAV: PARADO") y la Línea 2 muestra el último carácter ASCII recibido.

- Telemetría de Retorno: Cada vez que el robot cambie de estado, debe transmitir hacia la PC/Terminal una cadena informativa con el formato: "STATE: [Estado Actual]\r\n".

## Lineamientos Obligatorios del Video Defensa (3-4 Minutos)

- Minuto 1 (Demostración Base): Muestra tu circuito en Proteus con la pantalla del Virtual Terminal abierta. Digita de forma manual 'A' y 'P' comprobando la respuesta del robot y la actualización de telemetría serie devuelta.

- Minuto 2 y 3 (Destrucción del Código en Vivo): Lee textualmente el Reto de Modificación asignado. Ve a CCS C, localiza la lógica de comunicación o control implicada, codifica el cambio y compila en vivo sin errores.

- Minuto 4 (Verificación Anti-Plagio): Corre la simulación en vivo en Proteus demostrando la modificación del protocolo.

> Nota: el reto y la asignación de casos cambian por grupo; aquí se presenta la variante base.
