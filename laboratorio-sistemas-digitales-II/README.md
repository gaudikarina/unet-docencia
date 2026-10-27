# Laboratorio de Sistemas Digitales II
*Digital Systems Laboratory II — PIC18F4550*

**Herramientas / Tools:** PIC18F4550 · C con CCS · Proteus (`.pdsprj`) · LCD 16×2

## Estructura
Las carpetas `2021-2` y `2021-3` contienen las primeras prácticas del laboratorio (teclado y LCD gráfico, interrupciones, A/D, USART, I²C y CCP), cada una con su enunciado y su código.

| Carpeta | Tema | Contenido |
|---|---|---|
| `2025-1/practica01-puertos-matrices-teclado` | Puertos digitales | Conteo 00–99 en dos matrices de LED 5×7 y lectura de teclado matricial con anti-rebote (pruebas `displaytest`, `keytest`, `displaykeytest`, máquina de estados en `displaykeytest2`). |
| `2025-1/practica02-interrupciones` | Interrupciones | `INT_EXT`, `INT_EXT1/2` e `INT_RB`: contadores de producto con detección de conflicto y visualización en LCD. |
| `2025-1/practica03-adc-lcd` | Conversión A/D | Lectura de un sensor de luz con el ADC, cálculo de voltaje e intensidad (lux) y visualización en LCD. |
| `2025-1/practica04-comunicacion-serie` | Comunicación serie (SCI) | Sistema de monitoreo: `hab` mide y transmite la luz de una sala; `rem` recibe en un nodo remoto con `#int_RDA`; `simp` es un ejemplo mínimo de recepción. |
| `2025-3/practica05-ccp-pwm` | Módulo CCP y PWM | Melodía con PWM (CCP2) y base de tiempo por comparación (CCP1, 250 ms por corchea). |
| `2025-3/proyectos` | Proyectos finales | Descripción de los cinco proyectos (ver su README). |

La práctica 3 (conversión A/D con LCD) y la 4 (comunicación serie) del período 2025-3 siguen el mismo diseño de las del 2025-1.

## Períodos 2022-1, 2026-1 y 2026-2
Periféricos que usa cada práctica (según su código):

| Período | Práctica | Periféricos |
|---|---|---|
| 2022-1 (mayo) | 1 | LCD gráfico 128×64 (HDM64GS12), teclado matricial y comunicación serie |
| 2022-1 (mayo) | 2 | LCD gráfico, LCD 16×2 e interrupciones externas |
| 2022-1 (mayo) | 3 | LCD gráfico, LCD 16×2, conversión A/D y generación de tonos |
| 2022-1 (mayo) | 4 | Conversión A/D, comunicación serie y temporizadores |
| 2022-1 (mayo) | 5 | CCP/PWM y temporizadores |
| 2022-1 (mayo) | 6 | Red maestro/esclavo con I²C, sensores, A/D y LCD gráfico |
| 2026-1 | 1 | LCD 16×2, teclado matricial, serie e interrupciones |
| 2026-1 | 2 | LCD 16×2, serie e interrupciones |
| 2026-1 | 3 | LCD 16×2, conversión A/D, serie y sensores |
| 2026-1 | 4 | LCD 16×2 y comunicación serie |
| 2026-1 | 5 | A/D, CCP/PWM, temporizadores e interrupciones |
| 2026-2 | 1 | LCD 16×2, teclado matricial, serie e interrupciones |
| 2026-2 | 2 | Sensores con histéresis, umbrales y prioridad, relés y tonos |
| 2026-2 | 3 | I²C, CCP/PWM, temporizadores, EEPROM y sensores |

**Librerías del LCD gráfico (2022-1):** `hdm64gs12gau.c` y `hdm64gs12gaudi.c` son adaptaciones mías del controlador HDM64GS12 (cambié los puertos de conexión) y `graphics.c` es la librería de gráficos para CCS. Los iconos en mapa de bits (`.h`) de las prácticas no se incluyen.

## Enunciados
Cada práctica incluye su `README.md` con el enunciado (objetivos, pre-laboratorio, montaje y entregas), aunque no tenga solución asociada. Los enunciados se publican una sola vez, en el primer período en que se usaron:

- **2021-2:** prácticas 1 a 5 (puertos, interrupciones, A/D con USART, I²C y CCP) y proyectos cortos, con su código.
- **2021-3:** prácticas 1 a 3 (puertos e interrupciones; A/D y USART; I²C y CCP). Se repitieron sin cambios en 2022, 2023 y 2024, por lo que no se duplican. Los proyectos son los mismos de 2021-2.
- **2025-1, 2025-3, 2026-1 y 2026-2:** todos los enunciados son distintos de los anteriores. Los retos que cambian por grupo se indican como variantes.

Se omiten los encabezados institucionales, las figuras originales y los datos de los estudiantes.

## Cómo usar
Abrir el `.c` en CCS (o en MPLAB con el compilador CCS) para generar el `.hex`, y cargarlo en el microcontrolador del `.pdsprj` de Proteus. Los archivos compilados (`.hex`, `.cof`, `.lst`) no se publican porque se generan al compilar.
