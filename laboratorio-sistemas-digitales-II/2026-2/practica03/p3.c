#include <18F4550.h>
#fuses HS, NOMCLR, NOWDT, NOPROTECT, NOLVP, NODEBUG, CPUDIV1, VREGEN
#use delay(clock=20000000)

// Bus I2C por hardware (MSSP): SDA = RB0, SCL = RB1, 100 kHz
#use i2c(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW, FORCE_HW)

// Pantalla LCD 16x2 (Puerto D)
#define LCD_ENABLE_PIN PIN_D0
#define LCD_RS_PIN     PIN_D1
#define LCD_RW_PIN     PIN_D2
#define LCD_DATA4      PIN_D4
#define LCD_DATA5      PIN_D5
#define LCD_DATA6      PIN_D6
#define LCD_DATA7      PIN_D7
#include <lcd.c>

// ---- Entradas de usuario (activas en bajo, pull-up interno) ----------
#define SEL_MODO    PIN_B2   // abierto = AUTOMATICO, a GND = MANUAL
#define PUL_DUTY    PIN_B3   // MANUAL: +10 %
#define PUL_HIST    PIN_B4   // consulta del historial de eventos

// ---- Salidas de alarma -----------------------------------------------
#define LED_TEMP    PIN_A0   // alarma de sobretemperatura
#define LED_FALLA   PIN_A1   // alarma de falla de ventilador
#define ZUMBADOR    PIN_A2   // activo mientras exista al menos una alarma

// ---- Base de tiempo ---------------------------------------------------
#define T1_CUENTAS_100MS  62500UL
#define CICLOS_POR_SEG    10

// ---- PWM: 5 kHz, duty 0..1000 = 0,0 %..100,0 % -----------------------
#define PWM_PR2        249
#define DUTY_MAX       1000
#define DUTY_MIN_MAN   200
#define DUTY_PASO_MAN  100

// ---- Curva del modo AUTOMATICO ---------------------------------------
#define T_MIN          24.0
#define T_MAX          30.0
#define DUTY_AUTO_MIN  250

// ---- Alarmas ------------------------------------------------------------
#define RPM_NOMINAL       3000.0
#define FALLA_ACTIVA      0.60
#define FALLA_DESACTIVA   0.70
#define TEMP_ALARMA_ON    32.0
#define TEMP_ALARMA_OFF   31.0

// ---- SHT21 ------------------------------------------------------------
#define SHT21_ESCRITURA   0x80
#define SHT21_LECTURA     0x81
#define SHT21_CMD_TEMP_NH 0xF3

// ---- Captura del tacometro -------------------------------------------
#define RPM_CONST        18750000.0
#define CAP_TIMEOUT      65000
#define MARGEN_TICK      50
#define CICLO_CAPTURA    5

// ---- EEPROM 24LC256 (A0=A1=A2=GND) -----------------------------------
// Mapa de memoria:
//   0x0000-0x0001 : puntero de escritura (direccion del proximo registro)
//   0x0010-0x008F : cola circular de 16 registros de 8 bytes
// Registro: [0-1] tiempo (s) | [2] tipo | [3-4] temperatura x100 (con signo)
//           [5-6] velocidad real (RPM) | [7] reservado
// Cada registro esta alineado a 8 bytes, por lo que nunca cruza una pagina (64 bytes).
#define EE_ESC        0xA0
#define EE_LEC        0xA1
#define EE_BASE       0x0010
#define REG_TAM       8
#define N_REG         3
#define EV_FALLA      1
#define EV_TEMP       2

// ---- Consulta del historial ------------------------------------------
#define CONSULTA_TICKS  50        // 5 s sin pulsar -> vuelve a la pantalla normal

// ---- Variables compartidas con la ISR --------------------------------
volatile int1  flag_100ms   = 0;
volatile int16 t_prox       = T1_CUENTAS_100MS;
volatile int1  modo_captura = 0;
volatile int8  cap_n        = 0;
volatile int1  cap_listo    = 0;
volatile int16 cap_t0, cap_t1;

// ---- Variables globales del historial --------------------------------
int16 ee_ptr    = EE_BASE;
int16 tiempo_s  = 0;              // segundos desde el arranque

#int_ccp2
void isr_ccp2(void)
{
   if(modo_captura)
   {
      if(cap_n == 0)
      {
         cap_t0 = CCP_2;
         cap_n = 1;
      }
      else if(!cap_listo)
      {
         cap_t1 = CCP_2;
         cap_listo = 1;
      }
   }
   else
   {
      t_prox += T1_CUENTAS_100MS;
      CCP_2 = t_prox;
      flag_100ms = 1;
   }
}

int1 medir_rpm(float *rpm)
{
   int16 t_ini, transcurrido, hasta_tick, periodo;
   int1  ok;

   disable_interrupts(INT_CCP2);
   setup_ccp2(CCP_OFF);
   modo_captura = 1;
   cap_n = 0;
   cap_listo = 0;
   setup_ccp2(CCP_CAPTURE_RE);
   clear_interrupt(INT_CCP2);
   t_ini = get_timer1();
   enable_interrupts(INT_CCP2);

   while(!cap_listo && (int16)(get_timer1() - t_ini) < CAP_TIMEOUT);

   disable_interrupts(INT_CCP2);
   setup_ccp2(CCP_OFF);
   ok = cap_listo;
   modo_captura = 0;

   transcurrido = get_timer1() - t_ini;
   hasta_tick   = t_prox - t_ini;
   if(((int32)transcurrido + MARGEN_TICK) >= (int32)hasta_tick)
   {
      t_prox += T1_CUENTAS_100MS;
      flag_100ms = 1;
   }
   CCP_2 = t_prox;
   setup_ccp2(CCP_COMPARE_INT);
   clear_interrupt(INT_CCP2);
   enable_interrupts(INT_CCP2);

   if(ok)
   {
      periodo = cap_t1 - cap_t0;
      if(periodo == 0)
         *rpm = 0.0;
      else
         *rpm = RPM_CONST / (float)periodo;
   }
   else
      *rpm = 0.0;

   return ok;
}

int1 sht21_disparar(void)
{
   int8 nack;

   i2c_start();
   nack = i2c_write(SHT21_ESCRITURA);
   if(nack == 0)
      nack = i2c_write(SHT21_CMD_TEMP_NH);
   i2c_stop();

   return (nack == 0);
}

int1 sht21_leer(float *temp_c)
{
   int8  msb, lsb, crc;
   int16 crudo;
   float t;

   i2c_start();
   if(i2c_write(SHT21_LECTURA) != 0)
   {
      i2c_stop();
      return FALSE;
   }
   msb = i2c_read(1);
   lsb = i2c_read(1);
   crc = i2c_read(0);
   i2c_stop();

   if((lsb & 0x03) != 0)                 // bits de estado: 00 = medicion de temperatura
      return FALSE;
   crudo = make16(msb, lsb) & 0xFFFC;
   t = -46.85 + 175.72 * (float)crudo / 65536.0;
   if(t < -40.0 || t > 125.0)            // fuera del rango del sensor
      return FALSE;
   *temp_c = t;
   return TRUE;
}

// ======================================================================
// EEPROM 24LC256
// ======================================================================

// Sondeo por ACK: la memoria no responde mientras dura el ciclo de escritura (~5 ms)
int1 ee_esperar_listo(void)
{
   int8 n;

   for(n = 0; n < 100; n++)
   {
      i2c_start();
      if(i2c_write(EE_ESC) == 0)
      {
         i2c_stop();
         return TRUE;
      }
      i2c_stop();
      delay_us(200);
   }
   return FALSE;
}

// Lectura secuencial de n bytes desde la direccion dir (direccionamiento de 16 bits)
int1 ee_leer(int16 dir, int8 *buf, int8 n)
{
   int8 i, nack;

   // Se acumula el resultado de cada byte (0 = ACK): garantiza la espera del ACK
   // antes del RESTART y detecta cualquier respuesta ausente
   nack = 0;
   i2c_start();
   nack += i2c_write(EE_ESC);
   nack += i2c_write(make8(dir, 1));
   nack += i2c_write(make8(dir, 0));
   i2c_start();                        // RESTART
   nack += i2c_write(EE_LEC);
   if(nack != 0)
   {
      i2c_stop();
      return FALSE;
   }
   for(i = 0; i < n; i++)
      buf[i] = i2c_read(i < (n - 1));  // ACK en todos menos en el ultimo
   i2c_stop();
   return TRUE;
}

int1 ee_escribir_ptr(int16 p)
{
   int8 nack;

   nack = 0;
   i2c_start();
   nack += i2c_write(EE_ESC);
   nack += i2c_write(0x00);
   nack += i2c_write(0x00);
   nack += i2c_write(make8(p, 1));
   nack += i2c_write(make8(p, 0));
   i2c_stop();
   if(nack != 0)
      return FALSE;
   return ee_esperar_listo();
}

int1 ee_escribir_registro(int16 dir, int16 t, int8 tipo, int16 temp_x100, int16 rpm)
{
   int8 nack;

   nack = 0;
   i2c_start();
   nack += i2c_write(EE_ESC);
   nack += i2c_write(make8(dir, 1));
   nack += i2c_write(make8(dir, 0));
   nack += i2c_write(make8(t, 1));
   nack += i2c_write(make8(t, 0));
   nack += i2c_write(tipo);
   nack += i2c_write(make8(temp_x100, 1));
   nack += i2c_write(make8(temp_x100, 0));
   nack += i2c_write(make8(rpm, 1));
   nack += i2c_write(make8(rpm, 0));
   nack += i2c_write(0xFF);            // byte reservado
   i2c_stop();
   if(nack != 0)
      return FALSE;
   return ee_esperar_listo();
}

// Recupera el puntero de escritura; si no es valido (memoria virgen), lo inicializa
int1 ee_iniciar(void)
{
   int8 b[2];

   if(!ee_leer(0x0000, b, 2))
      return FALSE;

   ee_ptr = make16(b[0], b[1]);
   if(ee_ptr < EE_BASE || ee_ptr >= (EE_BASE + N_REG * REG_TAM) ||
      ((ee_ptr - EE_BASE) % REG_TAM) != 0)
   {
      ee_ptr = EE_BASE;
      return ee_escribir_ptr(ee_ptr);
   }
   return TRUE;
}

// Almacena un evento en la cola circular y avanza el puntero
int1 registrar_evento(int8 tipo, float temp, float rpm)
{
   int16 nuevo;
   signed int16 t100;
   int1  ok;

   t100 = (signed int16)(temp * 100.0);

   if(!ee_escribir_registro(ee_ptr, tiempo_s, tipo, (int16)t100, (int16)rpm))
      return FALSE;

   nuevo = ee_ptr + REG_TAM;
   if(nuevo >= (EE_BASE + N_REG * REG_TAM))
      nuevo = EE_BASE;

   ok = ee_escribir_ptr(nuevo);
   ee_ptr = nuevo;          // el registro ya esta escrito: el puntero avanza aunque falle el sondeo final
   return ok;
}

// Lee el evento k-esimo (k = 0: el mas reciente).
// Devuelve 1 = registro valido, 0 = sin registro, 2 = error de bus.
int8 ee_leer_evento(int8 k, int16 *t, int8 *tipo, signed int16 *temp_x100, int16 *rpm)
{
   int8 b[8];
   int8 idx, rec;
   int16 ptr;

   // El puntero de la EEPROM es la referencia (no el de RAM)
   if(!ee_leer(0x0000, b, 2))
      return 2;
   ptr = make16(b[0], b[1]);
   if(ptr < EE_BASE || ptr >= (EE_BASE + N_REG * REG_TAM))
      return 0;

   idx = (int8)((ptr - EE_BASE) / REG_TAM);      // proximo registro a escribir
   rec = (idx + N_REG - 1 - k) % N_REG;          // registro solicitado

   if(!ee_leer(EE_BASE + (int16)rec * REG_TAM, b, 8))
      return 2;

   if(b[2] != EV_FALLA && b[2] != EV_TEMP)
      return 0;                                  // posicion vacia

   *t         = make16(b[0], b[1]);
   *tipo      = b[2];
   *temp_x100 = (signed int16)make16(b[3], b[4]);
   *rpm       = make16(b[5], b[6]);
   return 1;
}

// Muestra en el LCD el evento *k; si no existe y *k > 0 vuelve al mas reciente
int8 mostrar_consulta(int8 *k)
{
   int16 t, rpm;
   int8  tipo, r;
   signed int16 t100;

   r = ee_leer_evento(*k, &t, &tipo, &t100, &rpm);
   if(r == 0 && *k > 0)
   {
      *k = 0;
      r = ee_leer_evento(0, &t, &tipo, &t100, &rpm);
   }

   if(r == 1)
   {
      lcd_gotoxy(1, 1);
      printf(lcd_putc, "E%02u ", *k + 1);
      if(tipo == EV_FALLA)
         lcd_putc("FALLA ");
      else
         lcd_putc("TEMP  ");
      printf(lcd_putc, "%5lus", t);

      lcd_gotoxy(1, 2);
      printf(lcd_putc, "T:%5.2f R:%4lu  ", (float)t100 / 100.0, rpm);
   }
   else if(r == 0)
   {
      lcd_gotoxy(1, 1);
      lcd_putc("SIN EVENTOS     ");
      lcd_gotoxy(1, 2);
      lcd_putc("                ");
   }
   return r;
}

// ======================================================================

int16 duty_automatico(float t)
{
   float d;

   if(t <= T_MIN)
      return DUTY_AUTO_MIN;
   if(t >= T_MAX)
      return DUTY_MAX;

   d = DUTY_AUTO_MIN + (t - T_MIN) * ((DUTY_MAX - DUTY_AUTO_MIN) / (T_MAX - T_MIN));
   return (int16)d;
}

void refrescar_lcd(float t, int16 duty, int1 modo_auto, int1 error_i2c,
                   float rpm, int1 alarma_falla, int1 alarma_temp)
{
   lcd_gotoxy(1, 1);
   printf(lcd_putc, "T:%5.2fC D:%3lu%% ", t, duty / 10);
   lcd_gotoxy(1, 2);
   if(error_i2c)
      lcd_putc("ERR I2C         ");
   else
   {
      printf(lcd_putc, "R:%7.2f ", rpm);
      if(modo_auto)
         lcd_putc("A ");
      else
         lcd_putc("M ");

      if(alarma_falla)
         lcd_putc("FALL");
      else if(alarma_temp)
         lcd_putc("TEMP");
      else
         lcd_putc("OK  ");
   }
}

void main()
{
   int8  ciclos = 0;
   int1  modo_auto, pul_ant = 1, pul_act;
   int1  pul4_ant = 1, pul4_act;
   int1  refrescar = 1;
   int1  error_i2c = 0;
   int1  alarma_falla = 0, alarma_temp = 0;
   int1  consulta = 0;
   int1  medicion_pendiente = 0;
   int1  temp_valida = 0;          // TRUE tras la primera lectura valida del SHT21
   int8  consulta_k = 0, cticks = 0, r;
   int16 duty = DUTY_AUTO_MIN;
   int16 duty_manual = DUTY_MIN_MAN;
   float temperatura = 25.0;
   float rpm_tach = 0.0;      // velocidad indicada por el tacometro emulado (100 Hz = 3000 RPM)
   float rpm_real = 0.0;      // velocidad real = rpm_tach x ciclo de trabajo vigente
   float rpm_esperada;

   setup_adc_ports(NO_ANALOGS);
   set_tris_a(0x00);
   set_tris_c(0xFB);
   set_tris_d(0x00);
   port_b_pullups(TRUE);
   output_a(0x00);

   lcd_init();
   lcd_putc("\f* DATA CENTER*");
   lcd_gotoxy(1, 2);
   lcd_putc("Iniciando...");
   delay_ms(1000);

   if(!ee_iniciar())
      error_i2c = 1;

   setup_timer_2(T2_DIV_BY_4, PWM_PR2, 1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(duty);

   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   set_timer1(0);
   CCP_2 = t_prox;
   setup_ccp2(CCP_COMPARE_INT);
   clear_interrupt(INT_CCP2);
   enable_interrupts(INT_CCP2);
   enable_interrupts(GLOBAL);

   // Primera conversion: se lee en el primer ciclo de 100 ms
   if(sht21_disparar())
      medicion_pendiente = 1;
   else
      error_i2c = 1;

   while(TRUE)
   {
      if(flag_100ms)
      {
         flag_100ms = 0;

         // ---- Tareas de cada ciclo de 100 ms ----
         modo_auto = input(SEL_MODO);
         pul_act   = input(PUL_DUTY);
         pul4_act  = input(PUL_HIST);

         if(pul_ant && !pul_act && !modo_auto)
         {
            duty_manual += DUTY_PASO_MAN;
            if(duty_manual > DUTY_MAX) duty_manual = DUTY_MIN_MAN;
            refrescar = 1;
         }
         pul_ant = pul_act;

         // Consulta del historial: cada pulsacion muestra el siguiente evento
         if(pul4_ant && !pul4_act)
         {
            if(!consulta)
            {
               consulta = 1;
               consulta_k = 0;
            }
            else
            {
               consulta_k++;
               if(consulta_k >= N_REG) consulta_k = 0;
            }
            r = mostrar_consulta(&consulta_k);
            if(r == 2) error_i2c = 1;
            cticks = 0;
         }
         pul4_ant = pul4_act;

         if(consulta)
         {
            cticks++;
            if(cticks >= CONSULTA_TICKS)
            {
               consulta = 0;
               refrescar = 1;
            }
         }

         if(modo_auto)
            duty = duty_automatico(temperatura);
         else
            duty = duty_manual;

         set_pwm1_duty(duty);

         // ---- Secuencia de un segundo ----
         ciclos++;
         if(ciclos >= CICLOS_POR_SEG)
         {
            ciclos = 0;
            tiempo_s++;
            if(sht21_disparar())
               medicion_pendiente = 1;
            else
               error_i2c = 1;
         }
         else if(ciclos == 1 && medicion_pendiente)
         {
            medicion_pendiente = 0;
            if(sht21_leer(&temperatura))
            {
               error_i2c = 0;
               temp_valida = 1;

               // Alarma de sobretemperatura con histeresis (condicion "superior a")
               if(!alarma_temp)
               {
                  if(temperatura > TEMP_ALARMA_ON)
                  {
                     alarma_temp = 1;
                     if(!registrar_evento(EV_TEMP, temperatura, rpm_real))
                        error_i2c = 1;
                  }
               }
               else
               {
                  if(temperatura < TEMP_ALARMA_OFF)
                     alarma_temp = 0;
               }
            }
            else
               error_i2c = 1;
            refrescar = 1;
         }
         else if(ciclos == CICLO_CAPTURA)
         {
            medir_rpm(&rpm_tach);
            rpm_real = rpm_tach * (float)duty / (float)DUTY_MAX;

            // Alarma de falla de ventilador con histeresis (condicion "inferior a")
            rpm_esperada = RPM_NOMINAL * (float)duty / (float)DUTY_MAX;
            if(!alarma_falla)
            {
               if(temp_valida && rpm_real < FALLA_ACTIVA * rpm_esperada)
               {
                  alarma_falla = 1;
                  if(!registrar_evento(EV_FALLA, temperatura, rpm_real))
                     error_i2c = 1;
               }
            }
            else
            {
               if(rpm_real >= FALLA_DESACTIVA * rpm_esperada)
                  alarma_falla = 0;
            }
            refrescar = 1;
         }

         // La velocidad mostrada sigue al ciclo de trabajo vigente
         rpm_real = rpm_tach * (float)duty / (float)DUTY_MAX;

         // Salidas de alarma
         output_bit(LED_TEMP,  alarma_temp);
         output_bit(LED_FALLA, alarma_falla);
         output_bit(ZUMBADOR,  alarma_temp || alarma_falla);

         if(refrescar)
         {
            refrescar = 0;
            if(!consulta)
               refrescar_lcd(temperatura, duty, modo_auto, error_i2c,
                             rpm_real, alarma_falla, alarma_temp);
         }
      }
   }
}
