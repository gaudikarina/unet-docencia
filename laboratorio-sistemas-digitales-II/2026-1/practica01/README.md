# PRÁCTICA 1

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Mayo 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Arquitectura de Software E/S en Microrrobótica Móvil Asistida por Inteligencia Artificial

## Objetivos

- Configurar registros de dirección y manipulación de puertos digitales en el PIC18F4550 aplicados al control de actuadores de potencia (Motores DC).

- Implementar algoritmos de barrido (polling) y técnicas de anti-rebote por software para decodificar mandos de navegación desde un teclado matricial 4x3.

- Integrar herramientas de Inteligencia Artificial Generativa (LLMs) como co-pilotos de diseño para optimizar estructuras lógicas y perfiles de movimiento robótico.

- Validar la robustez del código mediante la resolución en tiempo real de fallas operacionales y cambios de requerimientos en el hardware simulado.

## Pre-Laboratorio (Ingeniería Asistida por IA)

Cada estudiante debe preparar de manera individual el reporte técnico que incluya:

- Estudio del Driver L293D: Diseñar una tabla de verdad que muestre los estados lógicos necesarios en los pines de entrada ($IN1, IN2, IN3, IN4$) para lograr que un puente en H ejecute los 5 movimientos básicos de un robot diferencial: Avanzar, Retroceder, Giro Izquierda, Giro Derecha y Parada Estricta.

- Algoritmo de Polling del Teclado: Explicar el diagrama de flujo para leer un teclado 4x3 sin usar librerías automáticas de CCS C, asegurando que las filas actúen como salidas secuenciales y las columnas como entradas con resistencias Pull-Up.

- Fase de Co-Piloto IA (Bitácora de Prompts Obligatoria): Deberás interactuar con una IA Generativa (ChatGPT, Gemini, Claude, etc.) para solicitar la estructura de código base asignada a tu grupo. Para garantizar la transparencia del proceso de ingeniería, es obligatorio entregar un archivo PDF independiente (Bitácora de Co-Piloto) junto con el video defensa, evidenciando el hilo completo desde el Mensaje 1 (Primer Prompt) bajo las siguientes condiciones:

⚠️ Formato de Evidencia según la IA elegida:

- Si utilizas Google Gemini: Debes convertir el chat completo en un archivo PDF utilizando la opción de exportación/impresión de páginas que aparece en la parte superior derecha de la interfaz web de Gemini. Este PDF se adjuntará junto a la bitácora en Moodle.

- Si utilizas otras IA (ChatGPT, Claude, etc.): Deberás generar y copiar obligatoriamente el Enlace Público de Compartir Chat (Shared Chat Link) oficial de la plataforma. Este link se pegará en el campo de texto en línea de Moodle al realizar la entrega.

*Nota: En ambos formatos se verificará que se muestre el código crudo original y completo generado por la IA antes de tus correcciones manuales.

## Laboratorio: Plataforma del Microrobot Diferencial

 Se construirá el firmware para un prototipo móvil diferencial que responde a mandos manuales mediante el teclado matricial y ejecuta rutinas automatizadas complejas co-diseñadas por IA. La pantalla LCD 16x2 actuará en todo momento como el panel de telemetría, mostrando el estado actual de los motores y variables de control del sistema.

## Distribución Física de Conexiones (Hardware Común)

- Teclado Matricial 4x3 (Control de Navegación Manual) (🚨 NO USAR LA LIBRERIA PREDEFINIDA):

- Filas (Salidas): RC0, RC1, RC2,RC4

- Columnas (Entradas con Pull-Up): RC5, RC6, RC7.

- Mapeo de Teclas por defecto: 2=Avanzar, 8=Retroceder, 4=Izquierda, 6=Derecha, 5=Parar. 

- Driver L293D & Motores (Control de Actuadores):

- Motor Izquierdo: Controlado por pines RB0 y RB1.

- Motor Derecho: Controlado por pines RB2 y RB3.

- Módulo de Telemetría: Pantalla LCD 16x2 conectada de forma estándar al Puerto D (Manejo gestionado mediante la librería nativa <lcd.c>).

## Lineamientos Obligatorios del Video Defensa (3-4 Minutos)

 El video se grabará de forma continua, capturando tu pantalla completa y mostrando tu rostro en una esquina. Deberá dividirse estrictamente en:

- Minuto 1 (Demostración Base): Muestra tu circuito en Proteus obedeciendo los comandos manuales del teclado y desplegando la telemetría en el LCD. Muestra cómo se ejecuta la lógica autónoma que le solicitaste a la IA en el pre-laboratorio.

- Minuto 2 y 3 (Destrucción del Código en Vivo): Lee textualmente el Reto de Modificación que aparece abajo en tu recuadro. Ve a CCS C, localiza la lógica lógica/física pertinente (puertos, temporizaciones, condicionales de control) e implementa el cambio. Compila en vivo demostrando cero errores.

- Minuto 4 (Verificación Anti-Plagio): Corre la nueva simulación en Proteus demostrando que el robot responde al nuevo comportamiento de seguridad o re-configuración.

## 🎓TAREA IA Y RETO EN VIVO

Variable del Tablero / Función Base: MODO PATRULLAJE EN ZIG-ZAG (Exploración de Entorno).

Desarrollo Co-Diseñado con IA: Se utiliza la IA para generar una función de navegación autónoma secuencial que se activa al presionar la tecla 1. El robot debe avanzar por 1.2 segundos, realizar un quiebro a la derecha por 0.4 segundos, avanzar otros 1.2 segundos y realizar un quiebro a la izquierda por 0.4 segundos para evadir líneas de obstáculos fijos.

🔧 RETO DE MODIFICACIÓN EN VIVO (Ejemplo para resolver en el Video Tutorial):

 Modifica el código fuente en vivo para integrar un Protocolo de Parada de Emergencia por Hardware. Configura el pin RA5 como entrada digital. Si en cualquier momento de la trayectoria automática el pin RA5 detecta un cero lógico (0V / Pulsador presionado), el robot debe romper inmediatamente la secuencia de la IA, apagar por completo ambos motores (RB0-RB3 en 0) y activar un parpadeo de alerta intermitente en un LED testigo conectado al pin de salida RE2 con retardos de 200ms, bloqueando el teclado hasta que el microcontrolador sea reiniciado.
