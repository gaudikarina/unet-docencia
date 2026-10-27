;**************************************************************************
;Programa: proyectolab.asm		Fecha: 21 de Marzo de 2008
;
;Este programa intenta trabajar con los puertos B y C del microcontrolador
;para controlar el modulo de matriz de led's y a traves de los led que se 
;vea reflejado sobre la pantalla de mamera secuencial las siguientes letras
;U, N, E y T utilizando el PIC16F870 para tal proposito
;
;Revision: 1.0				Programa para PIC16F870
;Velocidad de reloj: 4 MHz		Reloj Instruccion: 1 MHz = 1uS
;Perro Guardian (WDT): Deshabilidado	Tipo de Reloj: XT
;Proteccion del codigo: OFF
;**************************************************************************

;**************************************************************************
;                           ORDENES DE CONTROL
;**************************************************************************

	RADIX	HEX			;Establece todo el programa en
					;numeracion hexadecimal

	LIST	p=16f870		;Tipo de microcontrolador utilizado
	#INCLUDE	"P16F870.INC"	;Definicion de registros internos
					;para uso del programa

;**************************************************************************
;                    DEFINICION DE REGISTROS DE TRABAJO
;**************************************************************************

STATUS	EQU	0x03			;Registro de estados
PC	EQU	0x02			;Registro Contador de Programa
PORTB	EQU	0x06			;Puerto B Banco 0
PORTC	EQU	0X07			;Puerto C Banco 0
REGB	EQU	0x20			;Registro de trabajo 8 bit
REGC	EQU	0x21			;Registro de trabajo 8 bit
REGD	EQU	0x22			;Registro de trabajo 8 bit
ROTAR	EQU	0x23			;Registro de trabajo 8 bit
ACUM	EQU	0x24			;Registro de trabajo 8 bit

;**************************************************************************
;                         DEFINICION DE VARIABLES
;**************************************************************************

#DEFINE	BANCO0	bcf	STATUS,5	;Siempre que escriba BANCO0 se
					;ejecuta bcf STATUS,5
#DEFINE	BANCO1	bsf	STATUS,5	;Siempre que escriba BANCO1 se
					;ejecuta bsf STATUS,5

;**************************************************************************
;                           INICIO DEL PROGRAMA
;**************************************************************************
	
	ORG	0x00			;Inicio en la posicion 00 banco 0
	goto	INICIO
	ORG	0x05			;Permite salvar el vector de inte-
					;rrupciones FSR

;**************************************************************************
;			    SUB RUTINAS DE RETARDO
;**************************************************************************

RETAR1	movlw	0x80
	movwf	REGC

SLTE	NOP

	decf	REGC,1
	btfss	STATUS,2
	goto	SLTE

	rlf	ROTAR,0

	return

RETAR2	movwf	ROTAR			;Retardo de Tiempo
	movlw	0x00

	movwf	PORTC
	movwf	PORTB
	
	movlw	0x80
	movwf	REGC

SLTF	NOP
	decf	REGC,1
	btfss	STATUS,2
	goto	SLTF
	movf	ROTAR,0

	return

;**************************************************************************
;                BASE DE DATOS PARA MOSTRAN EN MATRIZ
;**************************************************************************

TABLA1	addwf	PC,1
	retlw	0x00
	retlw	0x01
	retlw	0x02
	retlw	0x03
	retlw	0x04
	retlw	0x05
	retlw	0x06
	retlw	0x07
	retlw	0x08

TABLA2	addwf	PC,1
	retlw	0x10
	retlw	0x11
	retlw	0x12
	retlw	0x13
	retlw	0x14
	retlw	0x15
	retlw	0x16
	retlw	0x17
	retlw	0x18

TABLA3	addwf	PC,1
	retlw	0x20
	retlw	0x21
	retlw	0x22
	retlw	0x23
	retlw	0x24
	retlw	0x25
	retlw	0x26
	retlw	0x27
	retlw	0x28

TABLA4	addwf	PC,1
	retlw	0x30
	retlw	0x31
	retlw	0x32
	retlw	0x33
	retlw	0x34
	retlw	0x35
	retlw	0x36
	retlw	0x37
   	retlw	0x38

;**************************************************************************
;                           INICIO DEL PROGRAMA
;**************************************************************************

INICIO	BANCO1

	clrf	PORTB
	clrf	PORTC

	BANCO0

;**************************************************************

SLTD	movlw	0x80			;Para cargar la letra U
	movwf	REGB
	movlw	0x00			;MODIFICACION
	movwf	ACUM			;MODIFICACION
SLT3	movlw	0x08
	movwf	REGD
	movlw	0x01

SLT1	movwf	PORTC			;Inicio Sub Rutina 1
	movwf	ROTAR

	movf	ACUM,0			;MODIFICACION

	call	TABLA1
	movwf	PORTB

	incf	ACUM,1			;MODIFICACION

	call	RETAR1

	decf	REGD,1
	
	btfss	STATUS,2
	goto	SLT1
	decf	REGB,1

	btfsc	STATUS,2
	goto	SLT2
	goto	SLT3
	
SLT2	call	RETAR2

;**************************************************************

	movlw	0x80			;Para cargar la letra N
	movwf	REGB
	movlw	0x00			;MODIFICACION
	movwf	ACUM			;MODIFICACION
SLT6	movlw	0x08
	movwf	REGD
	movlw	0x01
	
SLT4	movwf	PORTC			;Inicio Sub Rutina 2
	movwf	ROTAR

	movf	ACUM,0			;MODIFICACION

	call	TABLA2
	movwf	PORTB

	incf	ACUM,1			;MODIFICACION

	call	RETAR1

	decf	REGD,1
	
	btfss	STATUS,2
	goto	SLT4
	decf	REGB,1

	btfsc	STATUS,2
	goto	SLT5
	goto	SLT6	

SLT5	call	RETAR2

;**************************************************************

	movlw	0x80			;Para cargar la letra E
	movwf	REGB
	movlw	0x00			;MODIFICACION
	movwf	ACUM			;MODIFICACION
SLT9	movlw	0x08
	movwf	REGD
	movlw	0x01
	
SLT7	movwf	PORTC			;Inicio Sub Rutina 3
	movwf	ROTAR

	movf	ACUM,0			;MODIFICACION

	call	TABLA3
	movwf	PORTB

	incf	ACUM,1			;MODIFICACION

	call	RETAR1

	decf	REGD,1
	
	btfss	STATUS,2
	goto	SLT7
	decf	REGB,1

	btfsc	STATUS,2
	goto	SLT8
	goto	SLT9
	
SLT8	call	RETAR2

;**************************************************************

	movlw	0x80			;Para cargar la letra T
	movwf	REGB
	movlw	0x00			;MODIFICACION
	movwf	ACUM			;MODIFICACION
SLTC	movlw	0x08
	movwf	REGD
	movlw	0x01
	
SLTA	movwf	PORTC			;Inicio Sub Rutina 4
	movwf	ROTAR

	movf	ACUM,0			;MODIFICACION

	call	TABLA4
	movwf	PORTB

	incf	ACUM,1			;MODIFICACION

	call	RETAR1

	decf	REGD,1
	
	btfss	STATUS,2
	goto	SLTA
	decf	REGB,1

	btfsc	STATUS,2
	goto	SLTB
	goto	SLTC
	
SLTB	call	RETAR2

	goto	SLTD

;**************************************************************************
;				FIN DEL PROGRAMA
;**************************************************************************
	
	END

