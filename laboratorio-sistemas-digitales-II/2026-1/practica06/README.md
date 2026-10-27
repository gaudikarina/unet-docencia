# PRÁCTICA 6

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Julio 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Interfaz Serial Intercircuito (\(I^2C\)): Monitoreo de Sensores Digitales y Control Directo de Actuadores Asistido por IA

## Objetivos

- Configurar e implementar el bus síncrono \(I^2C\) en modo Maestro utilizando el microcontrolador PIC18F4550.

- Investigar e interpretar la hoja de datos del dispositivo asignado para identificar sus direcciones y mapa de registros.

- Implementar el sistema base de monitoreo: lectura del sensor \(I^2C\) y despliegue continuo de datos en el LCD (Puerto D).

- Integrar rutinas de control en el Puerto C (PORTC) para el accionamiento de cargas a través del driver L293D.

- Desplegar la información en la pantalla LCD y monitorear las tramas mediante la herramienta \(I^2C\) Debugger en Proteus.

- Utilizar herramientas de IA Generativa como co-piloto técnico para el diseño de drivers e integración de actuadores.

## Pre-Laboratorio (Investigación e Ingeniería Asistida)

Cada estudiante debe investigar y documentar individualmente en su informe:

- Explicar el protocolo físico \(I^2C\): función de SDA y SCL, la condición de START/STOP, la respuesta ACK/NACK y las resistencias Pull-Up.

- Investigación del Dispositivo Asignado: Consultar el Datasheet del periférico asignado para determinar:

- Dirección física de 7 bits y configuración de pines de dirección (A0, A1, A2 si aplica).

- Byte de control para operación de Escritura (\(R/\bar{W} = 0\)) y de Lectura (\(R/\bar{W} = 1\)).

- Mapa de registros, comandos de configuración y formato de transmisión de datos.

- Explicar el uso de la directiva #use i2c(...) en CCS C Compiler y el manejo de funciones de bajo nivel (i2c_start(), i2c_write(), i2c_read(), i2c_stop()).

- Fase Co-Piloto IA (Bitácora Obligatoria): Utilizar una IA Generativa para diseñar la rutina de lectura del sensor y el control básico del motor en el Puerto C.

- Google Gemini: Exportar el chat completo a PDF y adjuntarlo en la entrega.

- ChatGPT / Claude: Adjuntar el enlace público de la conversación (Shared Link).

## Plataforma de Hardware Base Unificado (Proteus)

⚙️ Esquema Base Unificado para TODOS los grupos:

 Cada grupo construirá en Proteus el circuito con la siguiente distribución estandarizada de puertos:

- Puerto B (Bus \(I^2C\)): Líneas SDA (RB0) y SCL (RB1) dedicadas exclusivamente al bus de datos y reloj, con resistencias Pull-Up de \(4.7\text{ k}\Omega\).

- Sensor/Periférico \(I^2C\): Conectado a SDA y SCL en el Puerto B según la asignación de cada grupo.

- Herramienta de Diagnóstico: \(I^2C\) DEBUGGER en Proteus conectado directamente a las líneas SDA y SCL.

- Puerto C (Etapa de Potencia y Motores):

- Pines RC0 y RC1 conectados a las entradas IN1 e IN2 del Driver L293D para control de sentido de giro.

- Pin RC2 conectado al pin de habilitación EN1 del L293D.

- Pines RC4..RC5 conectados a LEDs de estado.

- Puerto D (Visualización): Pantalla LCD 16x2 conectada al Puerto D (RD0..RD7).

- Telemetría Serial: Consola Serial EUSART a 9600 bps en los pines RC6 (TX) y RC7 (RX).

## Lineamientos de la Evaluación (Video Defensa 3-4 Minutos)

- Demostración Base (Minuto 1): Muestra la simulación en Proteus ejecutando la conducta básica (lectura del sensor y visualización en LCD), junto a la acción de control primaria en el Puerto C y la ventana del \(I^2C\) Debugger. Muestra el chat de la IA.

- Modificación en Vivo (Minuto 2 y 3): Lee el Reto de Modificación asignado a tu grupo. Aplica el cambio en la lógica de control dentro de CCS C Compiler y compila en vivo.

- Verificación (Minuto 4): Ejecuta la simulación demostrando el cambio de comportamiento del motor (Puerto C), LCD (Puerto D) y tramas \(I^2C\)/UART.

## 🤖 GRUPO 1 — Sensor de Temperatura \(I^2C\) DS1621 y Control de Ventilación

Sistema Base: Leer continuamente la temperatura del DS1621 e imprimirla en el LCD en el Puerto D.

Tarea IA: Solicitar a la IA la función de lectura del registro de temperatura del DS1621 y una acción básica de control: encender el motor en el Puerto C (RC2=1) cuando la temperatura supere los \(30^\circ\text{C}\).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica de control e implementa una ventana de histéresis: el motor en Puerto C debe encender en sentido horario solo al superar los \(35^\circ\text{C}\) y apagarse únicamente cuando la temperatura baje de \(28^\circ\text{C}\).

## 🤖 GRUPO 2 — Sensor de Presión MPXA6115A con ADC \(I^2C\) PCF8591 y Compresor

Sistema Base: Leer el canal AIN0 del ADC PCF8591, convertir la lectura a kPa y mostrar el valor en la pantalla LCD (Puerto D).

Tarea IA: Pedir a la IA la rutina para solicitar la conversión del PCF8591 vía \(I^2C\) y encender el motor compresor en el Puerto C cuando la presión sea menor a \(60\text{ kPa}\).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica de control: si la presión cae por debajo de \(50\text{ kPa}\), gira el motor hacia la derecha; si la presión supera los \(80\text{ kPa}\), invierte el sentido de marcha a la izquierda para aliviar presión.

## 🤖 GRUPO 3 — Sensor de Humedad HIH5030 con ADC \(I^2C\) PCF8591 y Extractor

Sistema Base: Capturar el valor analógico del sensor HIH5030 mediante el PCF8591 y proyectar el porcentaje de humedad (\%\text{RH}) en el LCD (Puerto D).

Tarea IA: Solicitar a la IA la función de lectura del ADC PCF8591 e integrar un control simple para encender un extractor en Puerto C si la humedad supera el \(50\%\text{RH}\).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica: eleva el umbral de activación a \(65\%\text{RH}\), gira el extractor en sentido antihorario (RC0=0, RC1=1, RC2=1) y transmite una notificación serial mediante la UART.

## 🤖 GRUPO 4 — Sensor Digital de Temperatura TC74 / LM75 e Inversión de Marcha

Sistema Base: Leer los datos de temperatura del registro correspondiente del TC74 y desplegar el valor en grados Celsius en el LCD (Puerto D).

Tarea IA: Pedir a la IA la secuencia de comandos \(I^2C\) para la lectura del sensor y un control sencillo de encendido de motor si \(T > 28^\circ\text{C}\).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica para un control de marcha bidireccional: si \(T < 25^\circ\text{C}\), gira el motor a la derecha; si \(T \ge 25^\circ\text{C}\), invierte la dirección hacia la izquierda utilizando el Puerto C.

## 🤖 GRUPO 5 — Temporizador Industrial con RTC DS1307 y Actuación Directa

Sistema Base: Leer continuamente los registros BCD de segundos, minutos u horas del RTC DS1307 y mostrarlos en el LCD (Puerto D) en formato "HH:MM:SS".

Tarea IA: Solicitar a la IA la conversión BCD a decimal y una acción de control básica: activar el motor en Puerto C al llegar al segundo cero (segundos == 0).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica de control de tiempo: mantén el motor encendido únicamente durante los primeros 20 segundos de cada minuto y apágalo automáticamente durante los 40 segundos restantes.

## 🤖 GRUPO 6 — Registro y Recuperación de Estado de Motor en EEPROM 24LC256

Sistema Base: Leer un dato almacenado previamente en una posición de la EEPROM 24LC256 y mostrarlo en la pantalla LCD (Puerto D).

Tarea IA: Pedir a la IA rutinas de lectura/escritura en direcciones de 16 bits de la EEPROM e implementar la alternancia de encendido/apagado del motor mediante un comando por UART.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica de persistencia: guarda automáticamente en la EEPROM el estado del motor cada vez que cambie por UART, y haz que al reiniciar el PIC18F4550 se lea dicho estado para restaurarlo en el Puerto C.

## 🤖 GRUPO 7 — Control de Persiana Automatizada con Sensor LDR vía ADC \(I^2C\)

Sistema Base: Monitorizar el valor de iluminación captado por una LDR a través del canal AIN0 del ADC PCF8591 e imprimir el valor en el LCD (Puerto D).

Tarea IA: Solicitar a la IA la rutina de lectura del ADC y un control simple: encender el motor en el Puerto C para cerrar la persiana cuando la luz baje del \(40\%\).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica con temporización: ajusta el umbral al \(30\%\) de luz, enciende el motor solo durante 3 segundos (simulando carrera completa) y activa un LED indicador en el pin RC4.

## 🤖 GRUPO 8 — Sensor Digital Humedad/Temperatura SHT21 y Bomba de Riego

Sistema Base: Solicitar la lectura de humedad al SHT21 mediante comandos \(I^2C\) e imprimir la medición en el LCD (Puerto D).

Tarea IA: Pedir a la IA la función de consulta al SHT21 y un control básico: encender una bomba de agua en el Puerto C si la humedad cae por debajo del \(50\%\text{RH}\).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica: reduce el umbral crítico a \(40\%\text{RH}\), activa la bomba en el Puerto C y envía una alerta serial continua por la UART mientras el riego permanezca activo.

## 🤖 GRUPO 9 — Sensor Barométrico BMP180 y Sistema de Seguridad por Presión

Sistema Base: Enviar la secuencia de inicio de conversión al BMP180, leer la presión obtenida y desplegarla en la pantalla LCD (Puerto D).

Tarea IA: Solicitar a la IA los pasos de lectura del BMP180 e integrar un control simple para activar un extractor en el Puerto C si la presión supera los \(40\text{ kPa}\).

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica e implementa una parada de emergencia: si la presión supera los \(50\text{ kPa}\), deshabilita completamente las salidas del Puerto C (PORTC = 0x00) y muestra un mensaje de alarma en la pantalla LCD.

## 🤖 GRUPO 10 — Consigna con Potenciómetro vía ADC \(I^2C\) PCF8591 y Conmutación de Marcha

Sistema Base: Leer la posición de un potenciómetro conectado al canal AIN0 del PCF8591 e imprimir su valor en escala de 0 a 255 en el LCD (Puerto D).

Tarea IA: Pedir a la IA el código de lectura del PCF8591 y una lógica de conmutación simple: encender el motor en el Puerto C cuando la lectura supere el valor de 128.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica estructurando 3 zonas de control: Zona 1 (\(< 85\)): Gira el motor a la izquierda. Zona 2 (\(85 - 170\)): Detén el motor. Zona 3 (\(> 170\)): Gira el motor a la derecha. Refleja la zona activa en el LCD.

## 🤖 GRUPO 11 — Bus Dual (RTC DS1307 + EEPROM 24LC256) y Estampa de Tiempo de Arranque

Sistema Base: Acceder al bus \(I^2C\) compartido, leer la hora del DS1307 y mostrar los datos en el LCD (Puerto D).

Tarea IA: Solicitar a la IA una rutina para alternar comunicaciones en el mismo bus entre el RTC y la EEPROM, arrancando el motor en el Puerto C al presionar un botón.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica: cada vez que arranque el motor en el Puerto C, captura la hora exacta del DS1307, escríbela en la EEPROM 24LC256 como registro de auditoría y confirma la escritura por UART.

## 🤖 GRUPO 12 — Escáner de Direcciones en Bus \(I^2C\) y Control Manual

Sistema Base: Ejecutar un barrido de direcciones en el bus \(I^2C\) y reportar en el LCD (Puerto D) las direcciones donde se detecte respuesta ACK.

Tarea IA: Solicitar a la IA el algoritmo de escaneo de bus en CCS C y una función básica para encender/apagar un motor en el Puerto C.

⚠️ RETO DE MODIFICACIÓN EN VIVO (Para tu Video):

 Modifica la lógica: vincula el arranque del motor al escaneo; activa el motor en el Puerto C únicamente si se detecta presente en el bus al menos un dispositivo \(I^2C\), notificando el hallazgo por consola serial.

> Nota: el reto y la asignación de casos cambian por grupo; aquí se presenta la variante base.
