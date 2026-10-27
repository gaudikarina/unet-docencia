# Práctica 1: Manejo de puertos de entrada - salida e interrupciones en el microcontrolador PIC

*Enunciado del Laboratorio de Sistemas Digitales II, Septiembre 2021. Texto adaptado: se omiten el encabezado institucional y las figuras del original.*

## Objetivos
1. Familiarizar al estudiante con el entorno de desarrollo PROTEUS y CCS.

2. Gestionar la configuración de interrupciones externas.

3. Manejar los niveles de prioridad en interrupciones externas.

4. Manejar puertos de E/S del microcontrolador para resolver un problema especifico.

5. Resolver un problema especifico con manejo de interrupciones externas.

## Pre-Laboratorio
1. Explicar la configuración de puertos de acuerdo a las directivas del compilador con ejemplos.

2. Listar las funciones en C que se utilizan para manejo de puertos de E/S.

3. Investigar los tipos de interrupciones externas que maneja el PIC 18F4550.

4. Explicar la priorización de interrupciones en el PIC 18F4550.

5. Listar las directivas del compilador para interrupciones del pic 18F4550.

6. Listar las funciones en C que se utilizan para interrupciones externas del pic 18F4550.

7. Investigar el funcionamiento, librerías y funciones en CCS, y modo de conexión de los siguientes
elementos:

a) Teclado 4x4,
b) LCD gráfico con controlador KS0108.

8. Indicar las modificaciones que deben realizar a las librerías kbd.c y hdm64gs12g.c, para utilizarlas
en la resolución de la práctica.

9. Investigar como cargar una imagen .bmp en el LCD gráfico con controlador KS0108.

## Laboratorio
## Actividad Preliminar
1. Realizar la instalación de los software:Proteus y CCS; los cuales se encuentran publicados en el aula
virtual.

2. Siga los pasos indicados en el video tutorial titulado: Video de Instalación del Software de Laboratorio.

## Experiencia 01
Se desea realizar una aplicación de cajero automático, con las siguientes características:

1. Teclado de acceso alfanúmerico como se muestra en la figura 1, para la personalización siga los
pasos del siguiente video.

Figura 1: Teclado Cajero Automático

2. LCD gráfico con controlador KS0108.

3. Clave de 4 dígitos,

4. Pantalla de bienvenida con logo del banco cada grupo debe presentar uno diferente.

5. En la pantalla de inicio debe verse el nombre de la empresa solicitante y luego salir el menú
desplegable que se muestra en la figura 2.

Figura 2: Menú Cajero Automático

6. Una vez indicada la transacción debe solicitar el pin de acceso y para ello debe introducir la clave
de 4 dígitos y debe visualizarse en la pantalla el simbolo * por cada número introducido, debe
esperar introducir la tecla ENTER para avanzar, si se presiona CLEAR debe limpiar la pantalla y
esperar que se vuelva a introducir la clave, si se presiona cancel debe ir a la pantalla de bienvenida
y comenzar de nuevo.

7. Si el pin es correcto debe irse al submenú que se indica en la tabla 1 para cada menú.

8. Si el pin es incorrecto debe salir un mensaje de alerta de seguridad (cada grupo hacer uno diferente)
y bloquear el sistema.

## Experiencia 02
Se desea diseñar una alarma de automóvil con las siguientes características:
1. RB4-RB7, hay 4 sensores que controlan cada puerta del auto (prioridad 1).

2. RB2 un sensor que controla la puerta de la maleta (prioridad 2).

3. RB1 un sensor que controla la puerta del capot (prioridad 2).

4. Si la alarma está activada, cuando una de las puertas es abierta, su sensor envía un uno por la línea
respectiva, cambiando está de estado, con lo que provoca una interrupción y comienzan a sonar un
zumbador conectado en RA0 (debe sonar como una alarma de automóvil real).

5. Para detener la alarma el usuario debe mandar una señal infrarroja a un sensor, que cuando la
detecta activa la patita RB0 con lo que se produce una interrupción, los zumbadores se paran y la
alarma se desactiva.

6. El estado inicial del programa es alarma inactiva, para ello debe debe encenderse un led rojo.

7. Para activar la alarma se debe enviar una señal infrarroja, a través de la patilla RB0 y se indicará
con led encendido en verde.

8. Simular el sensor RB0 con pulsador y los de las puertas con interruptores.

Cuadro 1: Tabla de Sub-Menús Cajero Automático

Menú                           Sub-menú 1                 Sub-menú 2
Retiro de cuenta co-            Solicitar PIN               PIN correcto mensaje de retire su
rriente                                                     dinero CC. Si es PIN incorrecto
mensaje error y debe irse al menú
principal y comenzar de nuevo
Retiro de cuenta ahorro         Solicitar PIN               PIN correcto mensaje de retire su
dinero CA. Si es PIN incorrecto
mensaje error y debe irse al menú
principal y comenzar de nuevo
Transferencias                  Solicitar PIN               PIN correcto mensaje de reali-
ce transferencia. Si es PIN inco-
rrecto mensaje error y debe irse
al menú principal y comenzar de
nuevo

Saldo cuenta corriente          Solicitar PIN               PIN correcto mensaje de saldo
CC. Si es PIN incorrecto mensaje
error y debe irse al menú princi-
pal y comenzar de nuevo
Saldo cuenta ahorro             Solicitar PIN               PIN correcto mensaje de Saldo
CA. Si es PIN incorrecto mensaje
error y debe irse al menú princi-
pal y comenzar de nuevo

Cambio de Clave                 Solicitar PIN               PIN correcto solicitar nueva cla-
ve. Si es PIN incorrecto mensaje
error y debe irse al menú princi-
pal y comenzar de nuevo
Otras transacciones             Solicitar PIN               PIN correcto mensaje de Servi-
cios. Si es PIN incorrecto mensaje
error y debe irse al menú princi-
pal y comenzar de nuevo.

## Restricciones de diseño:
Para la experiencia 01 solo debe utilizar la configuración de E/S de los puertos, no se aceptarán
soluciones donde se utilice otro módulo del microcontrolador (Interrupciones, CCP, etc).
Para la experiencia 02 deben usar todas las interrupciones externas RB0, RB1, RB2 y RBI.

## Entregas:
## Laboratorio
1. El grupo deberá entregar un informe técnico de acuerdo al Instructivo publicado en el aula virtual,
el mismo deberá ser cargado en el espacio denominado Entregas, en la tarea denominada Informes
de Laboratorio 01 hasta la fecha indicada en el cronograma.

2. Video explicativo y de solución de la práctica como se indica en el Video Tutorial:Creación de
Video Defensa para el Laboratorio de Sistemas Digitales II que se encuentra en el aula
virtual, el mismo deberá ser montado en flipgrid y enlazado al aula en el espacio Entregas, en la
tarea denominada Videos de Laboratorio 01 hasta la fecha indicada en el cronograma.

## Nota sobre los íconos
`bofa.c` y `p120213.c` incluyen `bofa1.h`, un mapa de bits con el logo de una entidad bancaria para la pantalla de bienvenida del cajero. No se publica porque es una marca de terceros, por lo que estos programas no compilan sin ese archivo. Para compilar, sustituya el logo por una imagen propia convertida con la misma estructura de arreglo para el LCD gráfico KS0108.
