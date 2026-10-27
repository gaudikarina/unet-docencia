PRÁCTICA 5

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Noviembre 2025). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

MANEJO DEL MÓDULO DE COMPARACIÓN CAPTURA Y PWM DEL MICROCONTROLADOR PIC 18F4550

Imprimir Página

Objetivos

- Gestionar la configuración del módulo CCP del PIC 18F4550 para generación de señales de frecuencia variable.

- Implementar el uso del módulo CCP en modo PWM y Comparación de forma simultánea.

- Resolver problemas de temporización y control de periféricos de salida (Buzzer/Speaker).

## Pre-Laboratorio:

Cada estudiante debe investigar y documentar brevemente lo siguiente:

- Explicar los tres modos de trabajo del modulo CCP en el PIC 18F4550.

- Explicar el procedimiento de conguracion para cada modo de trabajo del modulo CCP del PIC 18F4550.

- Indique las directivas y funciones en C asociadas al modulo CCP del PIC 18F4550.

- Cálculos obligatorios: Realice una tabla con los valores de PR2 y Duty Cycle para cada una de las notas asignadas a su grupo (ver Tabla de Melodías).

Información Preliminar

- CALCULO DEL VALOR DEL CCP MODO COMPARACIÓN:

\( Valor_{CCP}=\dfrac{t}{4\cdot T_{OSC}\cdot P_{RE}D_{IV}T_{MR1}} \)

- MODO DE COMPARACIÓN:

- El registro de 16 bits es comparado constantemente con TMR1.

- Cuando ambos valores son iguales, CCPx puede tomar alguno de los siguientes valores:

- Valor alto.

- Valor bajo.

- No cambia.

- Se genera una interrupción

- IMPORTANTE: El pin del CCPX tiene configurarse como salida.

- Existe un modo especial que genera un disparo hardware que resetea los 16 bits de TMR1. Esto pemite:

- Configurar TMR1 como un contador módulo n.

- Se dispara la conversión A/D.

- MODO PWM:

- Cálculos para la generación de la señal PWM: Se fija el valor del período de la señal PWM a generar, y se despeja de la ecuación 01 el valor de PR2.

\( T_{PWM}=(P_{R2}+1) \cdot 4 \cdot T_{OSC}\cdot P_{RE}D_{IV}T_{MR2} \) Ec. 01

- Si el valor de PR2 es mayor de 255, se debe recalcular, modificando el pre divisor del TMR2 y/o el T_OSC para ajustarlo al valor del T_PWM deseado.

- Con el valor DC (indica el valor del tiempo del duty cycle), se calcula el valor del CCPRXL que debe colocarse en la función set_pwm1_duty(), para ello, se utiliza la ecuación 02.

\( DC_{PWM}=CCPRXL \cdot T_{OSC} \cdot P_{RE}D_{IV}T_{MR2} \) Ec. 02.

 Laboratorio:

Generación de Melodías mediante Hardware

Diseñe un sistema que utilice el módulo CCP1 en modo PWM para generar las frecuencias de las notas, y el módulo CCP2 en modo Comparación (o interrupción por Timer) para controlar la duración de cada nota (ritmo).

Especificaciones:

- Modo PWM: Generar la nota con un Duty Cycle del 50% para obtener un sonido limpio.

- Modo Comparación: Controlar el tiempo de activación de la nota (ej. 500ms para notas negras, 250ms para corcheas).

- Hardware: PIC 18F4550, Speaker/Buzzer y osciloscopio para validación.

## Tabla de Frecuencias de Notas Musicales

Utilice estos valores para el cálculo del registro PR2 y la configuración del CCP (Modo PWM).

Nota Musical 
Frecuencia (Hz) 
Nota Musical 
Frecuencia (Hz) 
Nota Musical 
Frecuencia (Hz) 
F3 (Fa) 
175 
E4 (Mi) 
330 
B4 (Si) 
494 
G3 (Sol) 
196 
F4 (Fa) 
349 
C5 (Do) 
523 
Bb3 (Sib) 
233 
F#4 (Fa#) 
370 
D5 (Re) 
587 
B3 (Si) 
247 
G4 (Sol) 
392 
E5 (Mi) 
659 
C4 (Do) 
262 
G#4 (Sol#) 
415 
F5 (Fa) 
698 
C#4 (Do#) 
277 
A4 (La) 
440 
F#5 (Fa#) 
740 
D4 (Re) 
294 
Bb4 (Sib) 
466 
G5 (Sol) 
784 
Eb4 (Mib) 
311 
B5 (Si) 
988 
A5 (La) 
880 
## Asignación de Melodías por Grupo

Cada grupo deberá implementar la secuencia de notas correspondiente. Las frecuencias base se encuentran en la Tabla de Frecuencias Estándar.

Grupo 
Melodía Asignada 
Secuencia de Notas (Referencia) 
01 
Star Wars (Theme) 
G3(N), C4(N), G4(N), F4(C), E4(C), D4(C), C5(N), G4(N), F4(C), E4(C), D4(C), C5(N), G4(N), F4(C), E4(C), F4(C), D4(N). 
02 
Super Mario Bros 
E5(C), E5(C), Silencio(C), E5(C), Silencio(C), C5(C), E5(N), G5(N), Silencio(N), G4(N). 
03 
The Legend of Zelda 
Bb3(N), F3(C), Bb3(C), Bb3(C), C4(C), D4(C), Eb4(C), F4(N). 
04 
Harry Potter 
B4(N), E5(N), G5(C), F#5(C), E5(N), B5(N), A5(N), F#5(N). 
05 
Mission Impossible 
G4(N), G4(N), Bb4(C), C5(C), G4(N), G4

 
 Donde: (N) = Negra (500ms) y (C) = Corchea (250ms).

## Entregas:

- Video: El grupo realizará un video explicativo de la solución de la práctica como se indica en el Instructivo de Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula virtual, el mismo, deberá ser enlazado al aula en el espacio de las Actividades Evaluativas denominado Entrega de Video Práctica 05, hasta la fecha indicada en el cronograma.
