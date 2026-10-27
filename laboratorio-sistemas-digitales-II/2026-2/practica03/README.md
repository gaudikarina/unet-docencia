# PRÁCTICA INTENSIVA 3

*Enunciado de la práctica (Laboratorio de Sistemas Digitales II, Septiembre 2026). Texto adaptado: se omiten el encabezado institucional y los datos de la asignatura.*

## Módulo CCP e Interfaz Intercircuito I2C: Control de Velocidad de un Extractor de Aire en un Invernadero

## Objetivos

- Configurar el módulo CCP del PIC18F4550 en sus tres modos de trabajo (Captura, Comparación y PWM) mediante las directivas del compilador CCS C.

- Implementar la medición del período de una señal externa en modo Captura, una base de tiempo en modo Comparación y el control de velocidad de un motor DC en modo PWM.

- Configurar el módulo MSSP del PIC18F4550 como maestro I2C y gestionar un bus compartido por múltiples esclavos, verificando el reconocimiento (ACK) de cada transacción.

- Adquirir datos de un dispositivo digital I2C y almacenar y recuperar registros de eventos en una memoria EEPROM externa 24LC256 con direccionamiento de 16 bits.

## Pre-Laboratorio

 Antes de la sesión de laboratorio, el estudiante debe realizar las siguientes investigaciones y asignaciones técnicas:

- Investigar el módulo CCP del PIC18F4550: registros CCPxCON y CCPRx, modos de Captura (flanco de subida/bajada y prescaler), Comparación (acciones al coincidir, interrupción por software y evento especial) y PWM (cálculo del período con PR2 y del ciclo de trabajo con 10 bits de resolución); relación con Timer1/Timer3 y Timer2; y funciones asociadas de CCS C (setup_ccp1(), setup_ccp2(), set_pwm1_duty(), CCP_2, setup_timer_1(), setup_timer_2()).

- Investigar el protocolo I2C (condiciones de START, RESTART y STOP, direccionamiento de 7 bits y bit R/W, ACK/NACK, resistencias de pull-up) y las hojas de datos del SHT21 (comando de medición de humedad, tiempo de conversión, bits de estado y ecuación de conversión de humedad relativa) y de la 24LC256 (direccionamiento de 16 bits, escritura por página, tiempo del ciclo de escritura y sondeo por ACK).

- Diseñar e implementar el circuito y el firmware base descritos en la sección Laboratorio, sin recurrir a herramientas de IA generativa.

- Resolver la rutina descrita en el bloque TAREA IA con apoyo de una herramienta de IA generativa: elaborar previamente un intento de solución propio, dialogar con la herramienta a partir de dicho intento, verificar críticamente el código obtenido mediante simulación en Proteus y conservar el registro completo de la interacción (bitácora de prompts) para su presentación.

## Laboratorio

 Se requiere diseñar e implementar el sistema de control de el extractor de aire para un invernadero de producción agrícola. El PIC18F4550 opera como maestro de un bus I2C al cual se conectan un sensor de humedad relativa y temperatura SHT21 y una memoria EEPROM 24LC256 destinada al registro de eventos. La velocidad del extractor (motor DC) se regula mediante PWM en función de la humedad relativa, su velocidad real se determina midiendo el período de la señal del tacómetro y la base de tiempo del sistema se establece con el modo Comparación. El estado del sistema se presenta en un LCD alfanumérico 16x2.

Asignación de los módulos CCP. El PIC18F4550 dispone de dos módulos CCP. El módulo CCP1 debe operar de forma permanente en modo PWM. El módulo CCP2 debe alternar por software entre el modo Comparación (base de tiempo del sistema) y el modo Captura (medición del período del tacómetro), de manera que los tres modos de trabajo intervengan en el funcionamiento del sistema.

Base de tiempo (Comparación). El modo Comparación de CCP2, referido a Timer1, debe generar un ciclo de supervisión de 100 ms. En cada ciclo se actualizan los contadores de tiempo y las lecturas de los pulsadores; una vez por segundo se realiza la adquisición de la humedad relativa por I2C, se actualiza el ciclo de trabajo del PWM (modo automático), se realiza la medición de velocidad y se refresca el LCD. La base de tiempo no debe acumular deriva por efecto del intercambio de modos de CCP2.

Adquisición de la humedad relativa. La humedad relativa debe adquirirse con el SHT21 mediante el comando de medición de humedad sin retención (0xF5), leyendo el resultado 100 ms después del disparo e ignorando los dos bits menos significativos del dato, que contienen el estado (10 en binario para medición de humedad). La humedad relativa se calcula como HR = −6 + 125 · S / 65536, donde S es el dato de 16 bits con los bits de estado en cero.

Medición de velocidad (Captura). Una vez por segundo, CCP2 debe reconfigurarse en modo Captura por flanco de subida para medir el período de la señal del tacómetro (4 pulsos por revolución) y calcular la velocidad en RPM, con dos decimales de precisión. Si no se detecta un pulso dentro de un tiempo límite, la velocidad debe registrarse como 0 RPM. Tras la medición, CCP2 debe volver al modo Comparación.

Emulación del tacómetro. Como el modelo de motor DC de Proteus no genera señal de tacómetro, se emplea un generador de señal digital (DCLOCK) cuya frecuencia representa la velocidad del extractor a plena carga: 100 Hz equivalen a 1500 RPM (velocidad nominal). La velocidad indicada por el tacómetro se calcula a partir del período medido (RPM = 60 / (4 × período)). La velocidad real del extractor debe calcularse multiplicando la velocidad indicada por el tacómetro por el ciclo de trabajo vigente del PWM; esta velocidad real es la que se presenta en el LCD y la que se utiliza en las alarmas. Ejemplo: con el generador a 100 Hz y un ciclo de trabajo de 50 %, la velocidad real es de 750 RPM. La frecuencia del generador se ajusta antes de iniciar la simulación, y una falla del extractor se emula con una frecuencia inferior al 60 % de la nominal (menos de 60 Hz) o desconectando la señal del tacómetro mediante un interruptor en serie.

Control de velocidad (PWM). La frecuencia del PWM debe estar comprendida entre 1,2 kHz y 5 kHz. En modo AUTOMÁTICO, el ciclo de trabajo se determina por interpolación lineal de la humedad relativa según la tabla siguiente. En modo MANUAL, el ciclo de trabajo se ajusta con un pulsador en pasos de 10 %, entre 20 % y 100 %, con retorno cíclico a 20 % tras alcanzar 100 %.

Humedad relativa (SHT21) | Ciclo de trabajo del PWM (modo AUTOMÁTICO) 
HR ≤ 60,00 % | 25 % 
60,00 % < HR < 80,00 % | Interpolación lineal entre 25 % y 100 % 
HR ≥ 80,00 % | 100 % 
Alarmas. El sistema debe supervisar dos condiciones de alarma, cada una con su banda de histéresis y su LED individual. Cuando coinciden ambas, la línea de estado del LCD debe indicar la de mayor prioridad. El zumbador permanece activo mientras exista al menos una alarma activa. La velocidad esperada corresponde a 1500 RPM multiplicadas por el ciclo de trabajo vigente, y se compara con la velocidad real.

Alarma | Condición de activación | Condición de desactivación | Prioridad 
Falla de extractor | Velocidad real inferior al 60 % de la velocidad esperada | Velocidad real igual o superior al 70 % de la velocidad esperada | 1 (mayor) 
Humedad excesiva | Humedad relativa superior a 85,00 % | Humedad relativa inferior a 83,00 % | 2 
Registro de eventos en EEPROM. Cada transición de inactiva a activa de una alarma debe almacenarse en la memoria 24LC256 como un registro de longitud fija que incluya el tiempo transcurrido desde el arranque (s), el tipo de evento, la humedad relativa y la velocidad real. Las dos primeras posiciones de la memoria deben reservarse para el puntero de escritura, de modo que el historial se conserve al reiniciar el sistema. El historial debe organizarse como una cola circular con una capacidad mínima de diez registros. Mediante el pulsador de consulta, cada pulsación debe mostrar en el LCD el siguiente evento almacenado, del más reciente al más antiguo.

Interfaz de usuario. La línea 1 del LCD debe mostrar la humedad relativa y el ciclo de trabajo vigente; la línea 2, la velocidad real en RPM, el modo de operación y la alarma de mayor prioridad activa. El selector de modo alterna entre AUTOMÁTICO y MANUAL.

 Debe instrumentarse el bus con el I2C Debugger de Proteus, de modo que las transacciones con cada esclavo puedan visualizarse durante la simulación, y la salida PWM con el osciloscopio virtual.

Restricciones de diseño:

- Humedad relativa y la velocidad deben calcularse en variables de punto flotante y presentarse con dos decimales de precisión.

- El bus I2C debe implementarse con el módulo MSSP (hardware). Cada transacción debe verificar el bit de reconocimiento (ACK). Ante la ausencia de respuesta de un esclavo, el sistema debe indicar "ERR I2C" en el LCD sin detener la ejecución del programa.

- Las escrituras en la EEPROM deben respetar el ciclo interno de escritura del dispositivo (sondeo por ACK o retardo mínimo de 5 ms) y utilizar direccionamiento de 16 bits.

- Toda lectura del sensor debe validarse (la trama de estado y el rango de 0 % a 100 %) antes de utilizarse; una lectura no válida no debe emplearse en el control, en las alarmas ni en los registros de la EEPROM.

- El ciclo de 100 ms y la medición del tacómetro deben gestionarse mediante las interrupciones de los módulos CCP; no se admiten retardos bloqueantes (delay_ms()) para temporizar el ciclo de supervisión.

- Los pines analógicos del puerto A deben configurarse como entradas/salidas digitales. La salida CCP2 debe ubicarse en RC1.

- Los módulos permitidos son CCP (con Timer1 y Timer2) e I2C (MSSP); no se admite el uso del módulo USART ni de interrupciones externas.

- El dispositivo seleccionado en el compilador debe coincidir con el componente empleado en Proteus (PIC18F4550), y el fuse de oscilador debe corresponder al hardware del esquema.

- El pin RC3 no debe emplearse, por no estar disponible como línea de E/S en el encapsulado DIP de 40 pines.

## Distribución Física de Conexiones (Hardware Común)

 Microcontrolador PIC18F4550 con cristal de 20 MHz y capacitores de carga (fuse HS). Asignación de pines:

Función | Pin(es) | Observaciones 
I2C — SDA | RB0 | Pull-up de 4,7 kΩ a VCC. Conectado a SHT21 (dirección de escritura 0x80) y 24LC256 (0xA0). 
I2C — SCL | RB1 | Pull-up de 4,7 kΩ a VCC. Conectado a SHT21 y 24LC256. 
Memoria 24LC256 | A0, A1, A2 y WP a GND | Dirección de escritura 0xA0. 
Sensor de humedad SHT21 | RB0 (SDA), RB1 (SCL) | Dirección de escritura 0x80. La humedad relativa se ajusta desde las propiedades del componente antes o durante la simulación. 
Salida PWM (CCP1) | RC2 | Motor DC del extractor accionado mediante transistor de conmutación (2N2222) o MOSFET, con diodo de protección. Osciloscopio virtual conectado a este pin. 
Entrada de tacómetro (CCP2) | RC1 | Señal de 4 pulsos por revolución emulada con un generador de señal digital (DCLOCK) de frecuencia fija entre 20 Hz y 100 Hz, ajustada antes de iniciar la simulación (100 Hz equivalen a la velocidad nominal de 1500 RPM). 
LCD 16x2 (HD44780) | RD4–RD7 (datos), RD1 (RS), RD2 (RW), RD0 (E) | Modo de 4 bits. 
Selector AUTOMÁTICO/MANUAL | RB2 | Interruptor a GND con pull-up interno del puerto B. 
Pulsador de ciclo de trabajo (+10 %) | RB3 | Pulsador a GND con pull-up interno. Activo en modo MANUAL. 
Pulsador de consulta de historial | RB4 | Pulsador a GND con pull-up interno. 
LED alarma de humedad excesiva | RA0 | Con resistencia limitadora. 
LED alarma de falla del extractor | RA1 | Con resistencia limitadora. 
Zumbador general | RA2 | Activo mientras exista al menos una alarma. 
## Lineamientos Obligatorios del Video Defensa (3-4 Minutos)

 El video se grabará de forma continua, capturando la pantalla completa y mostrando el rostro del estudiante en una esquina. Deberá dividirse estrictamente en:

- Minuto 1 (Demostración Base): Mostrar el circuito en Proteus ejecutando el comportamiento base, respondiendo a los estímulos de entrada y desplegando las lecturas/acciones requeridas.

- Minuto 2 y 3 (Modificación del Código en Vivo): Leer textualmente el Reto de Modificación indicado abajo. Modificar en el entorno CCS C la lógica técnica requerida y compilar en vivo sin errores.

- Minuto 4 (Verificación de Funcionamiento): Iniciar la simulación en Proteus para demostrar de forma inmediata la respuesta del sistema al nuevo requerimiento implementado.

## 🎓 TAREA IA

 Diseñar en CCS C para el PIC18F4550 la rutina de medición de velocidad del extractor con el módulo CCP2: reconfiguración de Comparación a Captura por flanco de subida referida a Timer1, cálculo del período entre dos capturas consecutivas y de la velocidad en RPM (4 pulsos por revolución), tratamiento del desbordamiento de Timer1 y del tiempo límite sin pulsos (0 RPM), y reprogramación de CCPR2 al retornar al modo Comparación para mantener el ciclo de 100 ms sin deriva. La rutina debe validarse en Proteus con el generador de señal digital ajustado a distintas frecuencias.

🔧 RETO DE MODIFICACIÓN EN VIVO:

 Modificar la curva de control del modo AUTOMÁTICO para que el ciclo de trabajo mínimo sea 40 % para HR ≤ 60,00 % y el máximo (100 %) se alcance a HR ≥ 75,00 %, con interpolación lineal entre ambos puntos. Compilar sin errores y validar en Proteus ajustando la humedad relativa del SHT21 a 60 %, 67,5 % y 75 %, verificando el ciclo de trabajo en el LCD y en el osciloscopio virtual.

> Nota: se asignó en cinco variantes: extractor de aire de un invernadero (E1, la que se presenta), extractor de gases de un estacionamiento subterráneo (E2), ventilador de enfriamiento de una banda transportadora (E3), ventilador del evaporador de una cámara frigorífica (E4) y extractor de una sala de baterías (E5).
