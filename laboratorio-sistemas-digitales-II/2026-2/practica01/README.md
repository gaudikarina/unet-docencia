# PRÁCTICA INTENSIVA 1

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Septiembre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Sistema de Alarma y Control de Acceso: Manejo de Puertos E/S e Interrupciones Externas en el PIC18F4550

## Objetivos

- Configurar registros de dirección y manipulación de puertos digitales del PIC18F4550 aplicados al control de acceso mediante teclado matricial.

- Implementar algoritmos de barrido (polling) y técnicas de anti-rebote por software para decodificar un código de acceso numérico, sin utilizar librerías predefinidas.

- Configurar y manipular los registros de control de interrupciones externas del PIC18F4550 (INTCON, INTCON2, INTCON3, IPEN) para gestionar múltiples zonas de un sistema de alarma con distintos niveles de prioridad.

- Implementar rutinas de servicio de interrupción (ISR) que respondan de forma diferenciada según la zona violada y el estado del sistema (armado/desarmado), integrando en una sola aplicación el manejo de puertos de E/S y de interrupciones externas.

## Pre-Laboratorio

 Cada estudiante debe preparar de manera individual un reporte técnico que incluya:

- Configuración de Puertos: Explicar la configuración de los puertos de E/S del PIC18F4550 de acuerdo a su posición de memoria y a las directivas del compilador CCS, con ejemplos.

- Algoritmo de Polling del Teclado: Diseñar el diagrama de flujo para leer un teclado matricial 4x3 sin usar librerías automáticas de CCS C, asegurando que las filas actúen como salidas secuenciales y las columnas como entradas con resistencias Pull-Up, e incluyendo la lógica anti-rebote.

- Registros de Interrupción y Prioridades: Elaborar una tabla resumen que explique INTCON, INTCON2, INTCON3 e IPEN, indicando por qué RB0/INT0 tiene la prioridad más alta por defecto en el microcontrolador, y cómo se habilitan las interrupciones por cambio de estado (RBI/Interrupt-on-Change) en RB4-RB7.

- LCD 16x2 Estándar: Investigar el funcionamiento, librería (<lcd.c>) y modo de conexión del LCD alfanumérico 16x2 con controlador HD44780 (no se utilizará LCD gráfico en esta práctica).

- Fase de Co-Piloto IA (Bitácora de Prompts Obligatoria): Antes de consultar cualquier IA Generativa, cada estudiante debe construir su propio intento de solución para la funcionalidad específica de su caso asignado (ver tabla de asignación en la sección Laboratorio). Solo después de ese intento propio se debe interactuar con la IA para pedir la modificación o mejora puntual indicada en su caso. Es obligatorio entregar la Bitácora de Co-Piloto evidenciando el hilo completo desde el Mensaje 1.

⚠️ Formato de Evidencia según la IA elegida:

- Si utilizas Google Gemini: convierte el chat completo en un archivo PDF mediante la opción de exportación/impresión de la interfaz web de Gemini.

- Si utilizas otras IA (ChatGPT, Claude, etc.): genera y copia el Enlace Público de Compartir Chat oficial de la plataforma, y pégalo en el campo de texto en línea de Moodle.

*Nota: en ambos formatos se verificará que se muestre el código crudo original y completo generado por la IA antes de tus correcciones manuales.

## Laboratorio

Construya un Sistema de Alarma y Control de Acceso con las siguientes características:

- Estado inicial: sistema desarmado (LED rojo encendido en RA1).

- El usuario ingresa su código de acceso por teclado (manejo puro de puertos E/S, sin interrupciones). Si es correcto, el sistema pasa a armado (LED verde en RA2) y se habilitan las interrupciones externas mediante INTCON.

- Con el sistema armado, cualquier sensor de zona que se active dispara su interrupción correspondiente según su nivel de prioridad (IPEN), enciende la sirena (RA0) y muestra en el LCD el nombre de la zona violada.

- Para desarmar, se debe reingresar el código correcto por teclado.

- Adicionalmente, cada caso incorpora la funcionalidad propia de IA descrita en la tabla de asignación.

## Tabla de Asignación de Casos (5 estudiantes)

Caso 
Institución 
Nombres de las 7 Zonas (RB0 / RB1 / RB2 / RB4 / RB5 / RB6 / RB7) 
A 
Vivienda Unifamiliar 
Puerta Principal / Puerta de Cocina / Puerta de Garaje / Ventana Sala / Ventana Cocina / Ventana Habitación / Patio Trasero 
B 
Sucursal Bancaria 
Botón de Pánico Oculto / Puerta de la Bóveda / Puerta Principal de la Sucursal / Puerta de Emergencia / Ventana de Gerencia / Sala de Cómputo / Estacionamiento Interno 
C 
Edificio de Oficinas 
Puerta Principal / Lobby / Sala de Servidores / Puerta de Emergencia/Escalera / Oficina de Gerencia / Sala de Juntas / Depósito/Almacén / Estacionamiento 
D 
Centro de Salud 
Entrada de Emergencias / Depósito de Medicamentos Controlados / Puerta Principal / Farmacia / Quirófano / Laboratorio Clínico / Estacionamiento de Ambulancias 
E 
Institución Educativa 
Puerta Principal / Laboratorio de Electrónica / Sala de Coordinación / Biblioteca / Laboratorio de Computación / Auditorio / Estacionamiento 
Nota (Caso B): la Zona 1 no es una puerta sino el pulsador de pánico oculto, ubicado deliberadamente en RB0/INT0 por ser la interrupción de mayor prioridad por defecto del microcontrolador.

## Distribución Física de Conexiones (Hardware Común)

Teclado Matricial 4x3 (Código de Acceso) (🚨 NO USAR LA LIBRERÍA PREDEFINIDA):

 Filas (Salidas): RC0, RC1, RC2, RC4. Columnas (Entradas con Pull-Up): RC5, RC6, RC7.

Nota: el PIC18F4550 no dispone del pin RC3 en su encapsulado de 40 pines (ocupado internamente por VUSB), por lo que PORTC solo ofrece 7 líneas de E/S disponibles — de ahí el uso de un teclado 4x3 en lugar de 4x4.

Sensores de Zona (interruptores/pulsadores simulando sensores):

 Zona 1: RB0 (INT0, prioridad máxima). Zona 2: RB1 (INT1). Zona 3: RB2 (INT2). Zonas 4 a 7: RB4-RB7 (interrupción por cambio de estado / RBI).

Salidas del Sistema:

 Sirena/Zumbador: RA0. LED Rojo (Desarmado): RA1. LED Verde (Armado): RA2.

Módulo de Telemetría: LCD alfanumérico 16x2 con controlador HD44780, conectado de forma estándar al Puerto D (librería nativa <lcd.c>). No se utiliza LCD gráfico en esta práctica.

## Lineamientos Obligatorios del Video Defensa (3-4 Minutos)

 El video se grabará de forma continua, capturando tu pantalla completa y mostrando tu rostro en una esquina. Deberá dividirse estrictamente en:

- Minuto 1 (Demostración Base): Muestra tu circuito en Proteus armando y desarmando el sistema con el código por teclado, y demuestra que cada una de las 7 zonas de tu caso dispara correctamente la alarma y se identifica en el LCD, incluyendo la funcionalidad de IA propia de tu caso.

- Minuto 2 y 3 (Destrucción del Código en Vivo): Lee textualmente el Reto de Modificación asignado a tu caso (ver tabla en el recuadro TAREA IA). Ve a CCS C, localiza la lógica pertinente (puertos, registros de interrupción, variables de estado) e implementa el cambio. Compila en vivo demostrando cero errores.

- Minuto 4 (Verificación Anti-Plagio): Corre la nueva simulación en Proteus demostrando que el sistema responde al nuevo comportamiento solicitado en el reto.

## 🎓 TAREA IA Y RETO EN VIVO POR CASO

 Cada estudiante trabaja únicamente el caso que le fue asignado. Recuerda: primero tu intento propio, luego la consulta a la IA (ver Pre-Laboratorio, punto 5).

Caso A — Vivienda: Temporizador de Entrada

Tarea IA: cuando el sistema está armado y se abre la Zona 1 (Puerta Principal), la sirena no debe sonar de inmediato: debe iniciar una cuenta regresiva de 3 segundos durante la cual el residente puede ingresar el código correcto para desarmar sin disparar la alarma. Si se agota el tiempo sin código correcto, se activa la sirena.

🔧 Reto en vivo: cambiar el valor de la demora a otro valor escójalo Ud. mismo, y mostrar la cuenta regresiva en tiempo real en el LCD.
