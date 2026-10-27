# PRÁCTICA INTENSIVA 2

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Septiembre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Monitoreo Ambiental de un Invernadero Agrícola mediante Conversión Análogo-Digital y Comunicación Serial

## Objetivos

- Gestionar la configuración del conversor análogo-digital (ADC) de 10 bits del microcontrolador PIC 18F4550 en múltiples canales.

- Implementar la conversión analógica a digital aplicada a tres variables físicas de un proceso de monitoreo ambiental, con su despliegue en pantalla LCD.

- Gestionar la configuración del módulo USART del PIC 18F4550 para comunicación serial bidireccional.

- Implementar la transmisión y recepción de datos vía USART hacia una terminal remota de monitoreo.

- Diseñar una lógica de decisión que combine múltiples variables de proceso, aplicando criterios de prioridad entre alarmas simultáneas e histéresis para evitar oscilaciones en la activación de cada alerta.

## Pre-Laboratorio

- Investigar el funcionamiento del conversor análogo-digital de 10 bits del PIC 18F4550: canales disponibles, tiempo de adquisición y tensión de referencia.

- Listar las directivas del compilador y las funciones en C (CCS) empleadas para configurar y leer el ADC en múltiples canales: setup_adc(), setup_adc_ports(), set_adc_channel(), read_adc().

- Explicar el funcionamiento del módulo USART del PIC 18F4550 en modo asíncrono (8N1) y las funciones de CCS asociadas: #use rs232(), putc(), getc(), kbhit(), printf().

- Investigar la configuración de la herramienta Virtual Terminal de Proteus para simular comunicación serial con una estación remota de monitoreo.

- Revisar el principio de funcionamiento, la curva de respuesta y la relación de calibración de un sensor de temperatura de salida analógica lineal tipo LM35, de un sensor de humedad relativa tipo HIH-5030 y de una fotorresistencia (LDR).

- Investigar el concepto de histéresis aplicada a lógica de control (banda muerta alrededor de un umbral) y su utilidad para evitar el parpadeo de una alarma cuando la lectura oscila cerca del punto de disparo.

- Diseñar mediante una herramienta de inteligencia artificial generativa la lógica de decisión con prioridad e histéresis requerida en la sección Tarea IA, registrando el prompt utilizado en la Bitácora de Prompts.

## Laboratorio

 Se requiere implementar un sistema de monitoreo ambiental para un invernadero agrícola, capaz de supervisar de forma simultánea tres variables del proceso: temperatura, humedad relativa e intensidad lumínica. Cada variable se adquiere mediante un sensor analógico dedicado. Todas las conversiones análogas-digitales deben realizarse con resolución de 10 bits y escalarse mediante variables de tipo flotante con precisión de dos decimales.

 Los tres valores, ya escalados a su unidad física correspondiente y con dos decimales de precisión, deben mostrarse de forma simultánea en un LCD de 16x2 caracteres conectado localmente al microcontrolador, y transmitirse periódicamente por USART hacia la estación remota de monitoreo mediante la Virtual Terminal de Proteus.

 Cada variable cuenta con un umbral de alerta y una banda de histéresis propios:

Variable 
Sensor 
Rango 
Condición de Alerta 
Histéresis 
Temperatura 
LM35 
0–60 °C 
Superior a 35 °C 
± 1 °C 
Humedad relativa 
HIH-5030 
0–100 %RH 
Inferior a 40 %RH 
± 3 %RH 
Intensidad lumínica 
LDR 
0–100 % 
Inferior a 20 % 
± 5 % 
 Cuando dos o más condiciones de alerta se presenten de forma simultánea, el sistema debe resolver el conflicto de acuerdo con el siguiente orden de prioridad: en primer lugar la temperatura, por representar el riesgo más inmediato de estrés térmico para el cultivo; en segundo lugar la humedad relativa, asociada al riesgo de deshidratación; y en tercer lugar la intensidad lumínica, vinculada a una reducción de la fotosíntesis. El indicador visual y el mensaje transmitido por USART deben corresponder siempre a la variable de mayor prioridad entre las alertas activas en cada instante. El zumbador de alerta general debe activarse mientras exista al menos una condición de alerta activa entre las tres variables, independientemente de cuál tenga mayor prioridad, y debe desactivarse únicamente cuando ninguna de las tres se encuentre activa.

 La banda de histéresis se aplica en el sentido correspondiente al tipo de condición de alerta de cada variable: para las condiciones definidas como superiores a un umbral, la alarma se activa al superarlo y se desactiva solo al descender por debajo del umbral menos la banda de histéresis; para las condiciones definidas como inferiores a un umbral, la alarma se activa al descender por debajo de este y se desactiva solo al superar el umbral más la banda de histéresis.

 Adicionalmente, el sistema debe reconocer un comando remoto enviado desde la estación de monitoreo: al recibir el carácter 'V' por USART, debe activarse o desactivarse manualmente el sistema de ventilación forzada, de forma independiente a la lectura de temperatura vigente. La recepción del comando debe implementarse de forma no bloqueante mediante la función kbhit().

## Distribución Física de Conexiones

- Sensor de temperatura (LM35): canal AN0 (RA0).

- Sensor de humedad relativa (HIH-5030): canal AN1 (RA1).

- Fotorresistencia (LDR): canal AN2 (RA2).

- LCD 16x2 estándar (HD44780), modo 4 bits: PORTD — RD0-RD3 (datos D4-D7), RD4 (RS), RD5 (Enable). El pin RW se conecta permanentemente a tierra.

- Indicadores de alerta (LED): RB0 (temperatura), RB1 (humedad relativa), RB2 (intensidad lumínica).

- Zumbador de alerta general: RB3.

- Actuador de ventilación forzada (motor DC, accionado mediante transistor de conmutación o módulo de relé): RB4.

- Módulo USART: RC6 (TX) y RC7 (RX), conectados a un componente Virtual Terminal de Proteus, configurado a 9600 baudios, 8 bits de datos, sin paridad y 1 bit de parada (8N1).

 En el PIC 18F4550 de 40 pines, el pin RC3 no se encuentra disponible como entrada/salida de propósito general, al estar ocupado internamente por la señal VUSB; por esta razón no debe emplearse en el presente montaje.

## Lineamientos Obligatorios del Video Defensa (3-4 Minutos)

 El video se grabará de forma continua, capturando la pantalla completa y mostrando el rostro del estudiante en una esquina. Deberá dividirse estrictamente en:

- Minuto 1 (Demostración Base): mostrar el circuito en Proteus, variar manualmente los tres sensores para evidenciar las lecturas escaladas en el LCD y su llegada a la Virtual Terminal. Provocar la activación de al menos dos alarmas simultáneas y demostrar que el sistema resuelve el conflicto respetando el orden de prioridad establecido. Demostrar también el efecto del comando remoto descrito en el Laboratorio.

- Minuto 2 y 3 (Modificación del Código en Vivo): leer textualmente el Reto de Modificación planteado en este instructivo. En CCS C, localizar la lógica de prioridad, el umbral o la histéresis involucrados, e implementar el cambio solicitado. Compilar en vivo demostrando cero errores.

- Minuto 4 (Verificación Anti-Plagio): ejecutar la nueva simulación en Proteus demostrando que el sistema responde correctamente al cambio implementado.

## 🎓 TAREA IA

 Solicitar a una herramienta de inteligencia artificial generativa apoyo para diseñar la lógica de decisión que combine las tres lecturas del sistema (temperatura, humedad relativa e intensidad lumínica) en un único estado de alerta, resolviendo el caso en que dos o tres condiciones se activen de forma simultánea conforme al orden de prioridad establecido, e incorporando la banda de histéresis de cada variable para evitar el parpadeo de la alarma. Registrar el prompt exacto utilizado en la Bitácora de Prompts y verificar manualmente, con al menos un caso de conflicto simultáneo entre dos variables, que la lógica resultante prioriza de forma correcta.

🔧 RETO DE MODIFICACIÓN EN VIVO:

 El encargado del invernadero solicita tres ajustes al sistema: primero, invertir el orden de prioridad, de modo que la humedad relativa pase a tener mayor prioridad que la temperatura; segundo, reducir el umbral de temperatura de 35 °C a 30 °C; y tercero, modificar el mensaje de alerta de intensidad lumínica transmitido por USART, de "ALERTA: LUZ BAJA" a "ADVERTENCIA: BAJA FOTOSINTESIS".

> Nota: se asignó en cinco variantes: invernadero agrícola (E1, la que se presenta), distribución de agua potable (E2), línea de producción industrial (E3), reactor de una planta química (E4) y riego agrícola inteligente (E5).
