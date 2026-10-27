# PRÁCTICA 3

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Julio 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Adquisición de Datos y Telemetría Multicanal: Configuración Avanzada del ADC del PIC18F4550 Asistida por Inteligencia Artificial

## Objetivos

- Configurar los registros de control del módulo analógico-digital del PIC18F4550 (ADCON0, ADCON1, ADCON2) para operaciones multi-canal.

- Seleccionar adecuadamente los tiempos de adquisición (TAD) y el reloj de conversión basándose en la frecuencia del oscilador del sistema (20MHz).

- Implementar ecuaciones de interpolación lineal y escalado matemático por software para transformar voltajes crudos en unidades físicas reales.

- Utilizar Inteligencia Artificial Generativa para optimizar las rutinas de conversión y formateo de cadenas flotantes, manteniendo la Bitácora de Prompts obligatoria.

## Pre-Laboratorio (Ingeniería Asistida por IA)

- Cálculo del Tiempo de Adquisición (TAD): Diseñar una memoria de cálculo manuscrita que justifique la selección de los bits ACQT y ADCS para un cristal de 20MHz, garantizando que se respete el parámetro mínimo de la hoja de datos del PIC18F4550.

- Investigación de la Hoja Técnica e Instrumentación Analógica: Cada grupo debe investigar de manera obligatoria el datasheet de su transductor asignado. Se debe documentar matemáticamente el diseño de la etapa de instrumentación y acondicionamiento requerida (ej. divisores de tensión, puentes de Wheatstone o etapas de ganancia con amplificadores operacionales) necesaria para adaptar la salida eléctrica nativa del sensor al rango estándar de entrada del ADC (0V - 5V).

- Ecuación de Escalado Lineal: Desarrollar la fórmula matemática genérica para convertir una resolución de 10 bits (0 - 1023) a un rango de voltaje de 0V - 5V, y posteriormente a la unidad física asignada a su grupo.

- Fase de Co-Piloto IA (Bitácora de Prompts Obligatoria): Deberás interactuar con un LLM para solicitar la plantilla de código multi-canal. Es obligatorio entregar el PDF de Gemini o el enlace público de ChatGPT/Claude en la entrega virtual. Se verificará que el primer prompt contenga los requerimientos base del hardware común.

⚠️ Formato de Evidencia según la IA elegida:

- Google Gemini: Exportar el chat completo a un archivo PDF utilizando el menú de impresión nativo de la plataforma.

- ChatGPT / Claude: Adjuntar el Enlace Público de Compartir Chat (Shared Chat Link) en el cuadro de texto en línea de Moodle.

## Distribución Física de Conexiones (Hardware Común)

⚠️ NOTA DE HARDWARE SIMULADO:

Es responsabilidad estricta del grupo cablear en Proteus la etapa de acondicionamiento físico investigada (puentes, divisores u operacionales nativos) antes del pin de entrada. No se permitirá la inyección directa de voltajes ficticios si el transductor requiere instrumentación previa.

- Entrada Analógica Principal (Canal Asignado + Instrumentación): Conectada al pin AN0 (RA0). Aquí se ubicará el circuito transductor específico de cada grupo.

- Potenciómetro de Setpoint (Canal Secundario): Conectado al pin AN1 (RA1). Se usará como control de umbral ajustable.

- Módulo de Telemetría: Pantalla LCD 16x2 conectada al Puerto D de forma estándar (PIN_D0 a PIN_D7).

- Actuador de Alerta Local: Un indicador LED conectado al pin digital RB0 y un Buzzer en el pin RB1.

## Lógica de Control Base (Comportamiento Inicial)

 El firmware inicial co-diseñado con la IA debe leer secuencialmente ambos canales analógicos de forma cíclica (conmuta de canal, espera el tiempo de muestreo, dispara la conversión read_adc() y procesa) cumpliendo con la siguiente lectura base en pantalla:

- Línea 1 del LCD: Debe mostrar el nombre de la variable física medida y su valor convertido (ej. "Temp: 45.2 C" o la unidad correspondiente a su grupo).

- Línea 2 del LCD: Debe mostrar el valor del Setpoint de control escalado exactamente de 0.0 a 100.0% ajustable mediante el potenciómetro de AN1 (ej. "Set: 65.0%").

- Condición Base de Alerta: Si el porcentaje de la variable medida en AN0 supera el porcentaje fijado en el Setpoint de AN1, el LED en RB0 se enciende de forma fija. Si es menor, permanece apagado.

## Lineamientos Obligatorios del Video Defensa (3-4 Minutos)

- Minuto 1 (Demostración Base): Muestra tu simulación en Proteus variando el sensor en AN0 y el potenciómetro en AN1, evidenciando la etapa de acondicionamiento físico cableada, el cambio en el LCD y la activación del LED según la lógica de control base.

- Minuto 2 y 3 (Destrucción del Código en Vivo): Lee textualmente el Reto de Modificación asignado a tu grupo. Ve a CCS C, localiza las funciones de conversión, lógica matemática o condicionales de comparación e implementa la modificación en tiempo real. Compila demostrando cero errores.

- Minuto 4 (Verificación Anti-Plagio): Corre la simulación modificada demostrando que el hardware responde al nuevo comportamiento dinámico de protección o alarma solicitado.

## 🤖 TAREA IA Y RETO EN VIVO 

Sensor Asignado (AN0): Voltaje de Entrada Directo. Escalado de telemetría base: 0.00 V a 5.00 V analógicos puros.

🔧 RETO DE MODIFICACIÓN EN VIVO (Ejemplo para Demostración Tutorial):

 Modifica el firmware en vivo para alterar la **Justificación de bits del Resultado del ADC** mediante la reconfiguración del registro ADCON2. Por defecto, las librerías leen el resultado justificado a la derecha (10 bits completos). El reto consiste en cambiar por código el bit de configuración correspondiente para justificar el resultado a la **izquierda (Left Justified)**, obligando a modificar la lectura matemática para extraer únicamente los 8 bits más significativos del registro ADRESH. Demuestra en Proteus que la resolución cambia limpiamente a un rango de 0 a 255 manteniendo el escalado de voltaje en el LCD.

> Nota: el reto y la asignación de casos cambian por grupo; aquí se presenta la variante base.
