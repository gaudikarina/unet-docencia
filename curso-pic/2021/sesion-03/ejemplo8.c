#include <16F877.h>
#use delay (clock=4000000)
#include <lcd.c>
#include <kbd.c>

int i,j;
char T,k,clave[4],DATOS[4];

void cambiar(){
nuevo:
	j=0;
	//kbd_init();
	lcd_putc("\f");
	lcd_gotoxy(3,1);
	printf(lcd_putc,"CLAVE ANTERIOR");
	i=0;
	lcd_gotoxy(6,2);
	while(i<=3){
	k=kbd_getc();
	if(k!=0){
	printf(lcd_putc,"*");
	DATOS[i]=k;
	i++;
	}
	}
	delay_ms(150);
	if((DATOS[1]==clave[1])&&(DATOS[2]==DATOS[2])&&(DATOS[3]==clave[3])&&(DATOS[0]==clave[0])){
		j=0;
		lcd_putc("\f");
		lcd_gotoxy(3,1);
		printf(lcd_putc,"CLAVE NUEVA");
		i=0;
		while(i<=3){
		k=kbd_getc();
		if(k!=0){
		lcd_gotoxy(6+i,2);
		printf(lcd_putc,"*");
		clave[i]=k;
		i++;
		
		}
		}
		delay_ms(150);
		lcd_putc("\f");
		printf(lcd_putc,"CAMBIO EXITOSO");
		delay_ms(500);
	}
	else{
		while(1){
			lcd_putc("\f");
			lcd_gotoxy(4,1);
			printf(lcd_putc,"BLOQUEADO");
			delay_ms(500);
			}	
		}
}


		
void acceso(){
viejo:
	j=0;
	lcd_putc("\f");
	lcd_gotoxy(6,1);
	printf(lcd_putc,"CLAVE");
	i=0;
	while(i<=3){
	k=kbd_getc();
	if(k!=0){
	lcd_gotoxy(6+i,2);
	printf(lcd_putc,"*");
	DATOS[i]=k;
	i++;

	}
	}
	delay_ms(150);
	if((DATOS[1]==clave[1])&&(DATOS[2]==DATOS[2])&&(DATOS[3]==clave[3])&&(DATOS[0]==clave[0])){
		lcd_putc("\f");
		printf(lcd_putc,"BIENVENIDO");
		delay_ms(500);
	}
	else{
	while(1){
			lcd_putc("\f");
			lcd_gotoxy(4,1);
			printf(lcd_putc,"BLOQUEADO");
			delay_ms(500);
			}	
		}
	
}


void main(){
	i=0;
	PORT_B_PULLUPS(TRUE);
	while(i<=3){
	clave[i]='0';
	DATOS[i]=i;
	i++;
	}
	j=0;
	lcd_init();
	kbd_init();
	while(1){
		lcd_gotoxy(1,1);
		printf(lcd_putc,"1: CAMBIAR CLAVE");
		lcd_gotoxy(1,2);
		printf(lcd_putc,"2: ACCESO");
		T=kbd_getc();
		switch(T)
		{
		case '1':
			cambiar();
			break;
		case '2':
			acceso();
			break;
		}
	}
}	
