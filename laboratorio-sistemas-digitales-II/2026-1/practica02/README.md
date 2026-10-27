# PRÁCTICA 2

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Junio 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Arquitectura de Software Orientada a Eventos: Gestión de Interrupciones Externas y Sensores de Colisión Asistida por Inteligencia Artificial

## Objetivos

- Configurar y manipular los registros de control de interrupciones del PIC18F4550 (INTCON, INTCON2, INTCON3) utilizando las directivas nativas de CCS C Compiler.

- Implementar rutinas de servicio de interrupción (ISR) eficientes basadas en hardware para procesar eventos asíncronos en tiempo real, simulando sensores de colisión mecánicos (Bumpers).

- Aplicar el concepto de priorización de interrupciones para resolver jerarquías de criticidad en la navegación autónoma de un microrobot diferencial.

- Utilizar herramientas de Inteligencia Artificial Generativa (LLMs) como co-pilotos para la optimización de código libre de retardos prohibitivos dentro de las ISR, documentando la ingeniería mediante una Bitácora de Prompts.

## Pre-Laboratorio (Ingeniería Asistida por IA)

Cada estudiante debe preparar de manera individual el reporte técnico que incluya:

- Análisis de Registros PIC18F4550: Diseñar una tabla resumen que detalle las funciones exactas de los bits INTEDG0, INTEDG1, INT1IP, e IPEN, explicando cómo se habilitan y direccionan las prioridades altas y bajas en el microcontrolador.

- Estudio de Concurrencia (Flags vs Delays): Explicar de forma escrita por qué el uso de la función delay_ms() dentro de una función decorada con #int_ext digital destruye el determinismo del sistema. Proponer un flujo donde la ISR únicamente modifique variables de estado globales.

- Fase de Co-Piloto IA (Bitácora de Prompts Obligatoria): Deberás interactuar con una IA Generativa (ChatGPT, Gemini, Claude, etc.) para solicitar la estructura de código base asignada a tu grupo. Para garantizar la transparencia del proceso de ingeniería, es obligatorio entregar un archivo PDF independiente (Bitácora de Co-Piloto) junto con el video defensa, evidenciando el hilo completo desde el Mensaje 1 (Primer Prompt) bajo las siguientes condiciones:

⚠️ Formato de Evidencia según la IA elegida:

- Si utilizas Google Gemini: Debes convertir el chat completo en un archivo PDF utilizando la opción de exportación/impresión de páginas que aparece en la parte superior derecha de la interfaz web de Gemini. Este PDF se adjuntará junto a la bitácora en Moodle.

- Si utilizas otras IA (ChatGPT, Claude, etc.): Deberás generar y copiar obligatoriamente el Enlace Público de Compartir Chat (Shared Chat Link) oficial de la plataforma. Este link se pegará en el campo de texto en línea de Moodle al realizar la entrega.

*Nota: En ambos formatos se verificará que se muestre el código crudo original y completo generado por la IA antes de tus correcciones manuales.

## Laboratorio: Plataforma del Microrobot Diferencial

 Se construirá el firmware para un prototipo móvil diferencial que responde a la detección inmediata de obstáculos por medio de interrupciones de hardware, simulando sensores de impacto perimetrales (Bumpers). La pantalla LCD 16x2 actuará en todo momento como el panel de telemetría, mostrando el estado actual de los motores y variables de control del sistema.

## Distribución Física de Conexiones (Hardware Común)

- Lazo Principal (Estado por Defecto): El microrobot se encuentra en constante marcha hacia adelante y el LCD muestra el mensaje fijo: "Navegando...".

- Sensores de Colisión Mecánicos (Bumpers con Pull-Up externos):

- Bumper Izquierdo: Conectado al pin de interrupción externa RB0 (INT0).

- Bumper Derecho: Conectado al pin de interrupción externa RB1 (INT1).

- Driver L293D & Motores (Control de Actuadores):

- Motor Izquierdo: Controlado por pines RB2 y RB3.

- Motor Derecho: Controlado por pines RB4 y RB5.

- Módulo de Telemetría: Pantalla LCD 16x2 conectada de forma estándar al Puerto D (Manejo gestionado mediante la librería nativa <lcd.c>).

## Lógica de Control Base (Comportamiento Inicial)

 Antes de realizar cualquier modificación, el firmware cooperativo co-diseñado con la IA debe cumplir estrictamente con el siguiente comportamiento reactivo básico ante colisiones (configurado por flanco de bajada H_TO_L):

- Condición Normal: Ambos motores avanzan (RB2=1, RB3=0, RB4=1, RB5=0). Pantalla LCD indica: "Navegando..." en la línea 1.

- Caso Bumper Izquierdo (Activación de INT0): Detiene inmediatamente la marcha. El LCD debe limpiar la pantalla y mostrar en la línea 1: "Obstaculo Izq" y en la línea 2: "Evasion: Der" mientras ejecuta un giro de escape.

- Caso Bumper Derecho (Activación de INT1): Detiene inmediatamente la marcha. El LCD debe limpiar la pantalla y mostrar en la línea 1: "Obstaculo Der" y en la línea 2: "Evasion: Izq" mientras ejecuta un giro de escape en sentido opuesto.

## Lineamientos Obligatorios del Video Defensa (3-4 Minutos)

 El video se grabará de forma continua, capturando tu pantalla completa y mostrando tu rostro en una esquina. Deberá dividirse estrictamente en:

- Minuto 1 (Demostración Base): Muestra tu circuito en Proteus obedeciendo los comandos reactivos y desplegando la telemetría en el LCD. Muestra cómo se ejecuta la lógica autónoma inicial que le solicitaste a la IA.

- Minuto 2 y 3 (Destrucción del Código en Vivo): Lee textualmente el Reto de Modificación asignado que aparece abajo en tu recuadro. Ve a CCS C, localiza la lógica pertinente (modificación de flags, manipulación de registros específicos, condiciones) e implementa el cambio. Compila en vivo demostrando cero errores.

- Minuto 4 (Verificación Anti-Plagio): Corre la nueva simulación en Proteus demostrando que el robot responde al nuevo comportamiento de seguridad o re-configuración asignada.

## 🤖 TAREA IA Y RETO EN VIVO 

Desarrollo con IA: Crea un prompt estructurado para que el co-piloto proporcione las rutinas necesarias para habilitar las resistencias Pull-Up internas del puerto B utilizando funciones de control nativas de CCS.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la interrupción por cambio de estado #int_rb. El reto consiste en evaluar en vivo el nibble alto del puerto. Si la lectura de los interruptores conectados en los pines RB5:RB4 da como resultado la combinación exacta "10" en binario, el sistema detiene los motores de manera controlada. Si cambia cualquier otro pin, la interrupción descarta el evento y mantiene la marcha.

> Nota: el reto de modificación en vivo y el montaje cambian por grupo; aquí se presenta la variante base.
