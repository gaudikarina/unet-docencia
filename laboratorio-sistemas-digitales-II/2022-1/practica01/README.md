# Práctica 1 (mayo de 2022): puertos, teclado y LCD gráfico
*Practice 1 (May 2022): I/O ports, keypad and graphic LCD*

Código en C (CCS) y simulación de Proteus (`PRACTICA1.pdsprj`) de la práctica de puertos de E/S e interrupciones externas con teclado 4×4 y LCD gráfico con controlador KS0108. El enunciado equivalente está en [`../../2021-3/practica01`](../../2021-3/practica01/README.md).

## Nota sobre los íconos
Algunos programas incluyen mapas de bits de marcas de terceros para las pantallas del LCD gráfico: `bofa1.h` (logo de un banco), `pantalla.h`, `chatw.h`, `smsm.h`, `contac.h`, `teleg.h` y `digitel.h` (íconos de aplicaciones de mensajería y de una empresa de telefonía). No se publican porque son marcas de terceros, por lo que esos programas no compilan sin ellos. Para compilar, sustituya cada archivo por una imagen propia convertida con la misma estructura de arreglo.

Las librerías `hdm64gs12gau.c`, `hdm64gs12gaudi.c` y `graphics.c` sí se incluyen; las dos primeras son adaptaciones mías del controlador HDM64GS12 (cambié los puertos de conexión).
