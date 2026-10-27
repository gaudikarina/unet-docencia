# PROYECTOS Diseño de aplicaciones con PIC 18F4550

*Enunciado del Laboratorio de Sistemas Digitales II, Julio 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Incentivar el pensamiento lógico estructurado en el diseño de aplicaciones con PIC 18F4550.

2. Consolidar los conocimientos adquiridos en el manejo de periféricos del PIC 18F4550.

3. Resolver un problema práctico utilizando la combinación de al menos tres periféricos del PIC
18F4550.

1.     BINGO
Se desea diseñar un BINGO digital para un casino, para ello se debe emular la pantalla general
el cartón completo donde se va marcando cada bola sorteada, también debe visualizarse la bola sorteada
y debe emularse el proceso real, donde la bola sorteada es sacada del total. Para la selección al azar de
la bola sorteada, se debe utilizar una interrupción externa. La visualización debe hacerse en una pantalla
local y adicionalmente enviarse por protocolo USB a una sala de control. Cuando un jugador tiene un
cartón lleno debe oprimir un pulsador (interrupción externa), en ese momento, se debe observar en la
pantalla la palabra ”JUEGO DETENIDO POSIBLE GANADOR”, si el cartón ganador es correcto, en
las pantallas se visualizará la palabra “GANADOR”, deberá sonar una fanfarria y se reinicia el juego,
estos sonidos deben generarse utilizando las interrupciones por TIMER del microcontrolador; si el cartón
no es el jugador, en las pantallas se visualizará la palabra “FALSA ALARMA” y el juego debe continuar.
Para el uso de cartones deberá precargarlos en una memoria EEPRON con protocolo I2 C.

2.     CONTROL PID DE TEMPERATURA
Se desea mantener la temperatura de un motor de automóvil, para ello se cuenta con un sensor de
temperatura con protocolo I2 C, la temperatura debe regularse entre los 80◦ C y 90◦ C, para ello el automóvil
cuenta con dos electroventiladores, uno de baja velocidad y otro de alta velocidad, utilice motores DC para
emular los electroventiladores y los módulos PWM para la regulación de la temperatura. El automóvil
cuenta con una pantalla gráfica LCD en su tablero donde se indicará los valores de temperatura y velocidad
de los motores, de igual manera se envía a través de protocolo USB a una PC, estos datos.

3.     CONTROL PID DE PRESIÓN
Se desea diseñar un sistema de control de aire PID para los neumáticos de un automóvil inteligente,
para ello se ubican en cada neumático un sensor de presión con protocolo I2 C, la presión de aire de cada
neumático debe mantenerse entre 32 y 35 PSI, para regular la presión se cuenta con un mini compresor de
aire para cada neumático, emule su funcionamiento con un motor DC y regule su velocidad con una señal
PWM. El automóvil cuenta con una pantalla gráfica LCD en su tablero donde se indicará los valores de
presión y velocidad de los motores, de igual manera se envía a través de protocolo USB a una PC, estos
datos.

4.     RELOJ INTELIGENTE
Se desea diseñar un reloj inteligente, con las opciones de Cronómetro, Alarma, Temporizador
y Reloj. Para ello utilice un reloj de tiempo real con protocolo I2 C, se debe mostrar el menú en una
pantalla LCD gráfica local y en una PC envíado por puerto USB. Para entrar a cada opción se debe
utilizar interrupciones externas, en el caso de la alarma se debe generar un sonido armonioso utilizando
los TIMER del microcontrolador. Para el inicio y detención del cronómetro se debe utilizar interrupción
externa, al igual que el temporizador, deben programarse sonidos diferentes para c/u.

5.     PIZARRA ELECTRÓNICA DE AVISOS
Se desea diseñar una pizarra electrónica de avisos monocromática, de dimensiones 64x40 pixeles,
para ello utilice matrices de leds. La pantalla será utilizada en el HALL de la universidad y se ubicará
en el centro del HALL y anunciará donde queda ubicado Control de Estudios, Formación Permanente,
con flechas y de forma animada, adicionalmente dirá la hora, el día y la fecha actual, para ello utilice un
reloj de tiempo real. Si un aula termino su clase lo anunciara, para ello utilice las interrupciones externas,
tome 4 aulas para el ejemplo. La información debe ser manejada a través de una memoria EEPROM con
protocolo I2 C, adicionalmente, en rectorado se observará la misma información que será enviada a través
del protocolo USB del PIC.

6.     SISTEMA DE SEGURIDAD EN CASA
Se desea instalar un sistema de seguridad en una casa residencial, para ello cuenta con sensores de
movimiento PIR con protocolo I2 C, debe colocar al menos 4 en zonas estratégicas de la residencia, cuando
se detecta un movimiento se encienden las luces del área y se envia una señal de alerta a la pantalla de la
sala de control de la residencia, donde esta ubicado una PC y recibe la información por protocolo USB.
En cada puerta de acceso a la residencia y ventanas, se encuentran ubicados sensores mágneticos, que al
cambiar su estado si el sistema está activado, activarán una alarma sonora (utilizar los TIMER) y una
visual. La alarma tiene un sistema de teclado y pantalla en la entrada donde se accede a un menú, en el
cual se ingresa el código de activación y desactivación de la misma, este menú debe visualizarse también
en la sala de control.

7.     SEMÁFORO INTELIGENTE
En la intersección de la Av. Carabobo con Av. España se desea instalar un semáforo inteligente,
cuando un peatón desea cruzar cualquiera de sus cruces, solicita el paso a través de un interruptor ubicado

en cada esquina, esto hace que se inicie un temporizador que le indica al peatón cuando será habilitado
su paso, en el momento que se habilita, se debe parar el tráfico de acuerdo al cruce que realizará el
peatón. Si no es solicitado ningún paso peatonal, el semáforo debe funcionar sincronicamente de forma
regular, establezca los tiempos de cada luz de acuerdo a su criterio. Cada semáforo ubicado en esta
intersección contiene una pantalla de señalización del temporizador de cambio de luz. Adicionalmente, el
funcionamiento del mismo debe ser enviado a una sala de control utilizando el protocolo USB. En cada
pantalla local y en la de la sala de control debe visualizarse las palabras: PARE, PASO, con símbolos y
flechas de dirección según sea el caso, para ello, utilice una memoria EEPROM con protocolo I2 C.

8.     CONTROL DE LLEGADA Y SALIDA DE EMPLEA-
DOS
En la universidad se desea implementar un control de salida y llegada de empleados, tomando en
cuenta que, existen tres tipos de empleados obrero, administrativo y profesor. Se debe llevar un control de
llegada y salida, guardando un récord en una memoria EEPROM con protocolo I2 C, el cual debe indicar
tipo de empleado, dia, mes año, hora llegada, hora salida, para ello utilice un reloj de tiempo real con
protocolo I2 C. En cada puesto de trabajo se encuentra una pantalla que indica la hora de inicio, que se
muestra una vez el trabajador llega a la jornada laboral, el tipo de empleado y la hora de salida, que se
muestra una vez el trabajador termina. Utilice interrupciones externas para indicar la llegada y salida del
empleado. Adicionalmente, esta información debe ser enviada, por protocolo USB, a una sala de control
que se encuentra en RRHH donde se monitorea todos los empleados, para el proyecto emule al menos un
empleado de cada tipo. Se debe tener una opción de reporte donde permita leer la información guardada
en la memoria eeprom y visualizada en la sala de control.

9.     DISPOSITIVO DE CONTROL DE MOTORES
Una empresa especializada en venta de motores eléctricos desea ofrecer un dispositivo capaz de
realizar el control de giro, velocidad y posición de tres tipos de motores: dc, paso a paso y servomotor.
El dispositivo deberá contener un teclado o pulsadores, un menú local que se muestra en pantalla, que
permitirá escoger el tipo de motor y de control que se desea realizar, en la pantalla se debe visualizar
el set point, la posición y/o velocidad actual y el giro. Para el control de posición en el motor dc utilice
encoder de cuadratura. Adicionalmente deberá enviar a una sala de control, el mismo menú y las mismas
variables de monitoreo, a través del protocolo USB.

10.      ESTACIÓN METEOROLÓGICA
Se desea implementar una estación meteorologica en el jardín botánico de la universidad, la cual debe medir,
humedad, temperatura, luz y presión, utilice para ellos sensores con protocolo I2 C. Estas variables deben
ser medidas en intervalos de 20 segundos por un período de 5 minutos en una memoria externa EEPROM
con protocolo I2 C. Se debe visualizar los datos tomados en tiempo real en un LCD gráfico local y deben
ser enviados a una sala de control a través del protocolo USB. Se debe presentar un menú de opciones
que permita, visualizar la data en tiempo real, o visualizar la data grabada en un periodo de tiempo
preestablecido. En la pantalla debe visualizarse las variables físicas de acuerdo a lo especificado en la
tabla 1.

Cuadro 1: Estación Meteorológica

Variable Física                         Rango                        Unidad
Temperatura                          de -25 a +75                      ◦C
Luz             Noche, Anocheciendo, LLuvioso , Nublado, Soleado
Presión                          de 850 a 1100                    mbar
Humedad                             de 0 a 100                      %RH

## Entregas:
1. El grupo deberá entregar un informe técnico de acuerdo al instructivo publicado en el aula virtual,
el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada Informe
Proyecto hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Video Tutorial:Creación de
Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula
virtual, el mismo deberá ser montado en youtube, de forma oculta y enlazado al aula virtual en el
espacio denominado Entregas, en la tarea denominada Video Proyecto hasta la fecha indicada en
el cronograma.

> Este enunciado se usó igual en 2021-2 y 2021-3.
