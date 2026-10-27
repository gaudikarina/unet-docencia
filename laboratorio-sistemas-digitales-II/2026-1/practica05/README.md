# PRÁCTICA 5

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Julio 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Manejo del Módulo de Comparación, Captura y PWM del Microcontrolador PIC18F4550 Asistido por IA

## Objetivos

- Gestionar la configuración del módulo CCP del PIC18F4550 para la generación de señales de frecuencia variable.

- Implementar el uso del módulo CCP en modo PWM y Comparación de forma simultánea para el control de temporización y frecuencia.

- Resolver problemas de temporización y control de periféricos de salida (Buzzer / Speaker / Driver L293D) e insumos de control analógico y digital.

- Utilizar herramientas de IA Generativa como co-piloto técnico para la estructuración de código C y matrices de melodías musicales.

## Pre-Laboratorio (Investigación e Ingeniería Asistida)

Cada estudiante debe investigar y documentar individualmente en su informe:

- Explicar los tres modos de trabajo del módulo CCP en el PIC18F4550 (Captura, Comparación y PWM).

- Explicar el procedimiento de configuración para cada modo de trabajo del módulo CCP.

- Indicar las directivas y funciones en C asociadas al módulo CCP en CCS C Compiler.

- Cálculos obligatorios: Realice una tabla con los valores de PR2 y Duty Cycle (50%) para cada una de las notas asignadas a su grupo según la frecuencia de reloj de su montaje.

- Fase Co-Piloto IA (Bitácora Obligatoria): Utilizar una IA Generativa para generar los arreglos de notas y duraciones de la canción asignada.

- Google Gemini: Exportar el chat completo a PDF y adjuntarlo en la entrega.

- ChatGPT / Claude: Adjuntar el enlace público de la conversación (Shared Link).

## Información Preliminar y Ecuaciones de Diseño

Modo Comparación (Control de Tempo / Ritmo):

 El registro de 16 bits del módulo CCP en modo comparación se contrasta continuamente con el Timer1. Al coincidir, se puede generar un reinicio automático del Timer1 (CCP_COMPARE_RESET_TIMER) e interrupción por hardware.

 \( Valor_{CCP} = \frac{t}{4 \cdot T_{OSC} \cdot P_{REDIV\_TMR1}} \)

Modo PWM (Generación de Tono / Frecuencia):

 Se fija el periodo deseado para la nota musical y se despeja el valor del registro PR2.

 \(T_{PWM} = (PR2 + 1) \cdot 4 \cdot T_{OSC} \cdot P_{REDIV\_TMR2} \quad \text{(Ec. 01)}\)

 Para un ciclo de trabajo de sonido limpio (50%), se calcula el valor a cargar mediante la función set_pwm_duty():

 \(DC_{PWM} = CCPRXL \cdot T_{OSC} \cdot P_{REDIV\_TMR2} \quad \text{(Ec. 02)}\)

Tabla de Frecuencias de Notas Musicales (Referencia Estándar)

Nota 
Frec. (Hz) 
Nota 
Frec. (Hz) 
Nota 
Frec. (Hz) 
F3 | 175 
E4 | 330 
B4 | 494 
G3 | 196 
F4 | 349 
C5 | 523 
Bb3 | 233 
F#4 | 370 
D5 | 587 
B3 | 247 
G4 | 392 
E5 | 659 
C4 | 262 
G#4 | 415 
F5 | 698 
C#4 | 277 
A4 | 440 
F#5 | 740 
D4 | 294 
Bb4 | 466 
G5 | 784 
Eb4 | 311 
B5 | 988 
A5 | 880 
*Duraciones estándar de referencia: Negra (N) = 500 ms | Corchea (C) = 250 ms.

## Plataforma de Hardware y Asignación de Pines

Mapeo de Hardware Proteus (Seguimiento de Diagrama):

- CCP1 (Pin RC2): Salida de audio conectada mediante resistencia de $330\,\Omega$ al Altavoz/Buzzer (LS1). Generación de frecuencia por PWM.

- CCP2 / Timer1: Configurado en modo Comparación e Interrupción para el control estricto del tempo de las notas.

- Driver L293D (U2) y Motor DC: Habilitador EN1 conectado a RC1. Entradas de dirección IN1..IN4 conectadas al Puerto B (RB1..RB4).

- Pantalla LCD 16x2 (LM016L): Controlada por el Puerto D (RD0=E, RD1=RS, RD2=RW, RD4..RD7=D4..D7). Muestra nombre de la nota, frecuencia y estado del sistema.

- Entrada Analógica RA0 (AN0): Potenciómetro de Control Maestro de Tempo / Velocidad (escala el tiempo base de reproducción en tiempo real).

- Entrada Digital RB0 (INT0): Pulsador de Control de Estado (Play / Pausa de la canción).

## Lineamientos de la Evaluación (Video Defensa 3-4 Minutos)

- Demostración Base (Minuto 1): Muestra la ejecución en Proteus del programa base reproduciendo la canción asignada. Muestra la telemetría en el LCD, la acción del botón de Pausa (RB0) y la perilla de Tempo (RA0). Muestra tu chat de IA.

- Modificación en Vivo (Minuto 2 y 3): Lee el Reto de Modificación asignado a tu grupo. Modifica el código en CCS C Compiler y compila en vivo sin errores.

- Verificación (Minuto 4): Ejecuta la simulación modificada demostrando el correcto funcionamiento del reto integrado con el driver L293D / Motor / Periféricos.

## 🤖 TAREA IA Y RETO EN VIVO — Star Wars Theme

Secuencia de Notas: G3(N), C4(N), G4(N), F4(C), E4(C), D4(C), C5(N), G4(N), F4(C), E4(C), D4(C), C5(N), G4(N), F4(C), E4(C), F4(C), D4(N).

Tarea IA: Solicitar a la IA la generación de las matrices de frecuencias PR2, Duty Cycle y duraciones para esta secuencia.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Conecta la señal del motor DC en RC1. Modifica el programa para que mientras suena la marcha imperial, la velocidad del motor aumente un 10% de Duty Cycle en cada nota de tipo NEGRA (N), mostrando en la línea 2 del LCD el porcentaje de potencia actual del motor.

## 🤖 TAREA IA Y RETO EN VIVO — Super Mario Bros

Secuencia de Notas: E5(C), E5(C), Silencio(C), E5(C), Silencio(C), C5(C), E5(N), G5(N), Silencio(N), G4(N).

Tarea IA: Solicitar a la IA las matrices completas de la melodía incluyendo la gestión de notas de silencio ($DC = 0$).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Programa la interrupción externa INT0 (RB0). Si se presiona durante la reproducción, la canción debe pausarse inmediatamente y el motor diferencial conectado al driver L293D debe ejecutar una maniobra de "Avanzar" (según la Tabla de Verdad del driver) a velocidad constante, mostrando en el LCD: "MODO: TRACCION".

## 🤖 TAREA IA Y RETO EN VIVO — The Legend of Zelda

Secuencia de Notas: Bb3(N), F3(C), Bb3(C), Bb3(C), C4(C), D4(C), Eb4(C), F4(N).

Tarea IA: Pide a la IA la rutina para modificar dinámicamente el registro de comparación CCP_2 o valor del Timer a partir de la lectura analógica del canal ADC0.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Utiliza el potenciómetro en RA0 (AN0) para alterar en tiempo real la velocidad de tempo de la canción entre 100 ms y 600 ms por corchea, mostrando en la línea 2 del LCD el valor actual de BPM o Tempo calculado sin distorsionar el tono de las notas.

## 🤖 TAREA IA Y RETO EN VIVO — Harry Potter Theme

Secuencia de Notas: B4(N), E5(N), G5(C), F#5(C), E5(N), B5(N), A5(N), F#5(N).

Tarea IA: Solicitar a la IA la estructuración de arreglos constantes en memoria ROM para ahorrar RAM en PIC18F4550.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Implementa una lectura de entrada en RB4. Si RB4 = 1, la melodía suena por el speaker. Si RB4 = 0, se apaga el sonido y la señal PWM en RC1 mueve el motor con una velocidad proporcional a la frecuencia de la nota actual (notas más agudas = mayor velocidad del motor).

## 🤖 TAREA IA Y RETO EN VIVO — Mission Impossible

Secuencia de Notas: G4(N), G4(N), Bb4(C), C5(C), G4(N), G4(N), F4(C), F#4(C).

Tarea IA: Pide a la IA estructurar la melodía de Misión Imposible integrando un indicador de estado por interrupción.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Utiliza el driver L293D con las salidas de dirección en RB0 y RB1. Haz que las ruedas del robot realicen una maniobra de "Giro Derecha" durante las notas Negras (N) y "Giro Izquierda" durante las Corcheas (C) siguiendo la Tabla de Verdad del driver.

## 🤖 TAREA IA Y RETO EN VIVO — Pac-Man Theme

Secuencia de Notas: B4(C), B5(C), F#5(C), Eb5(C), B5(C), F#5(C), Eb5(N), C5(C), C6(C).

Tarea IA: Pide a la IA las matrices de datos de Pac-Man y la lógica de control para los estados de la tabla de verdad L293D.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Conecta los pines de dirección del L293D. Haz que el robot ejecute "Avanzar" durante la primera mitad de la canción y "Retroceder" en la segunda mitad, actualizando el estado en la pantalla LCD ("MOV: AVANZAR" / "MOV: RETROCESO").

## 🤖 TAREA IA Y RETO EN VIVO — Tetris Korobeiniki

Secuencia de Notas: E5(N), B4(C), C5(C), D5(N), C5(C), B4(C), A4(N), A4(C), C5(C), E5(N).

Tarea IA: Pide a la IA la función de mapeo analógico para transformar la lectura de 10 bits de RA0 en un rango de temporización.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Integra el potenciómetro en RA0. Mientras suena Tetris por CCP1, la velocidad del motor conectado a RC1 debe regularse continuamente con la lectura del potenciómetro, mostrando en el LCD tanto la nota musical como el porcentaje de velocidad del motor.

## 🤖 TAREA IA Y RETO EN VIVO — Pink Panther Theme

Secuencia de Notas: C#4(C), D4(N), D#4(C), E4(N), C#4(C), D4(C), D#4(C), E4(C), G4(C).

Tarea IA: Solicita a la IA la estructura del código para pausar progresivamente una señal PWM reduciendo el ciclo de trabajo.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Implementa un "Freno Seco" o "Parada Estricta" en los motores mediante las combinaciones del driver L293D al presionar el pulsador RB0. Muestra en la pantalla LCD la alerta "FRENO DE EMERGENCIA" y apaga la salida de audio.

## 🤖 TAREA IA Y RETO EN VIVO — Indiana Jones Theme

Secuencia de Notas: E4(C), F4(C), G4(N), C5(N), D4(C), E4(C), F4(N), G4(C), A4(C), B4(N).

Tarea IA: Pide a la IA la lógica de una máquina de estados para alternar entre velocidad normal y doble velocidad.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica el código para que al presionar el botón RB0 se alterne entre Modo 1 (Reproducción normal) y Modo 2 (Reproducción al doble de velocidad disminuyendo a la mitad la cuenta de tiempo), indicándolo en la línea 2 del LCD.

## 🤖 TAREA IA Y RETO EN VIVO — Pirates of the Caribbean

Secuencia de Notas: A4(C), C5(C), D5(N), D5(N), D5(C), E5(C), F5(N), F5(N), F5(C), G5(C).

Tarea IA: Solicitar a la IA la función de caracteres personalizados (lcd_custom_char) para crear barras en el LCD.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Diseña una barra de progreso visual en la línea 2 del LCD. Por cada nota ejecutada de la canción, imprime un bloque ('■') llenando progresivamente los 16 caracteres de la pantalla hasta completar la melodía.

## 🤖 TAREA IA Y RETO EN VIVO — Coffin Dance / Astronomia

Secuencia de Notas: F4(C), F4(C), F4(C), F4(C), A4(C), C5(C), B4(C), A4(C), G4(N), G4(C).

Tarea IA: Pide a la IA el algoritmo para sincronizar cambios de velocidad en un motor con eventos de interrupción.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Conecta la señal de habilitación del motor en RC1. Al ritmo de las corcheas (C), la velocidad del motor debe alternar suavemente entre el 30% y el 80% de ciclo de trabajo en perfecta sincronía con las interrupciones del Timer.

## 🤖 TAREA IA Y RETO EN VIVO — Game of Thrones

Secuencia de Notas: G4(N), C4(N), Eb4(C), F4(C), G4(N), C4(N), Eb4(C), F4(C), D4(N), G3(N).

Tarea IA: Solicitar a la IA la rutina de finalización de ciclo de reproducción e inicialización de periféricos secundarios.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Crea la rutina "Arranque Final": cuando la melodía termine de sonar completa por primera vez, el sistema apaga la salida de audio en RC2, activa la tracción de los motores al 100% mediante el L293D e imprime en la pantalla LCD: "SISTEMA ACTIVO".

> Nota: el reto y la asignación de casos cambian por grupo; aquí se presenta la variante base.
