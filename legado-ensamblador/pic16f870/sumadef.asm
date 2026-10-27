;**********************SUMA DECIMAL DE DOS NUMEROS BCD INTRODUCIDOS POR PUERTO Y SE MUESTRA EL RESULTADO POR PUERTO**************
status	equ	0x03
portb	equ	0x06
portc	equ	0x07
portd	equ	0x08
trisb	equ	0x86
trisc	equ	0x87
trisd	equ	0x88
m9		equ	0x21
m90		equ	0x22
lsb		equ	0x23
msb		equ	0x24
n1		equ	0x25
n2		equ	0x26
suma	equ	0x27

	org	0
	bsf		status,5
	movlw	0xff
	movwf	trisb
	movwf	trisc	;puertos B y C como entradas
	clrf	trisd	;puerto D como salida
	bcf		status,5
	movlw	0x0a
	movwf	m9
	movlw	0xa0
	movwf	m90
inicio
	movf	portb,0
	movwf	n1		;lee primer numero 
	movf	portc,0
	movwf	n2		;lee segundo numero
	addwf	n1,0	;suma hexadecimal de n1+n2
	movwf	suma
	btfss	status,1;hubo acarreo auxiliar?
	goto	ajus_nueve;si no hubo verficar si es mayor de nueve 
	goto	ajus_lsb;si hubo acarreo auxiliar vaya a ajuste lsb
ajus_lsb
	movf	suma,0
	addlw	0x06
	movwf	suma
	btfss	status,0	;suma 6 al resultado de la suma hexadecimal y pregunta si hubo acarreo general
	goto	ajus_noventa; si no hubo verifica si el nibble msb es mayor a 9
	goto	ajus_msb	; si hubo acarreo general ajusta el nibble msb
ajus_nueve
	movf	suma,0
	andlw	0x0f
	movwf	lsb
	movf	m9,0
	subwf	lsb,0
	btfss	status,0	;verifica si es mayor a 9 el nibble lsb
	goto	ajus_noventa; si no es mayor pasa a verificar si el nibble msb es mayor a 9
	movf	suma,0
	addlw	0x06
	movwf	suma		;realiza el ajuste al nibble lsb si es mayor a 9
ajus_noventa
	movf	suma,0
	andlw	0xf0
	movwf	msb
	movf	m90,0
	subwf	msb,0
	btfss	status,0	;verifica si es mayor a 9 el nibble msb
	goto	ajus_msb	;si no es mayor verifica si hubo acarreo general
	movf	suma,0
	addlw	0x60
	movwf	suma		;realiza ajuste al nibble msb si es mayor a 9
ajus_msb
	movf	n1,0
	addwf	n2,0
	btfss	status,0	;verifica si hubo acarreo general
	goto	mostrar		;si no hubo va a mostrar el resultado de la suma
	movf	suma,0
	addlw	0x60
	movwf	suma		;realiza el ajuste al nibble msb si hubo acarreo
mostrar
	movf	suma,0
	movwf	portd		;muestra resultado en decimal por puerto.
	goto	inicio
	end
	

	