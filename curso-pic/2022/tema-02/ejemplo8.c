#include <16F877.h>
#use delay (clock=4000000)
#use standard_io(B,D)
#include <lcd.c>

int i;

void main(){
   while(1){
      delay_ms(500);
      lcd_init();
      i=0;
      for(i==0;i<=10;i++){
         lcd_gotoxy(4,1);
         printf(lcd_putc,"Curso_PIC_2");
         delay_ms(100);
         lcd_putc("\f");
         delay_ms(100);
         }
      i=244;
      for(i==244;i<=254;i++){
         lcd_gotoxy(i,1);
         printf(lcd_putc,"Curso_PIC_2");
         delay_ms(100);
         lcd_putc("\f");
         delay_ms(100);
         }   
      i=1;
      for(i==1;i<=16;i++){
         lcd_gotoxy(i,1);
         printf(lcd_putc,"Curso_PIC_2");
         delay_ms(100);
         lcd_putc("\f");
         delay_ms(100);
         }
      i=16;
      for(i==16;i>=1;i--){
         lcd_gotoxy(i,1);
         printf(lcd_putc,"Curso_PIC_2");
         delay_ms(100);
         lcd_putc("\f");
         delay_ms(100);
         }
      i=255;
      for(i==255;i>=244;i--){
         lcd_gotoxy(i,1);
         printf(lcd_putc,"Curso_PIC_2");
         delay_ms(100);
         lcd_putc("\f");
         delay_ms(100);
         }
         }
}
