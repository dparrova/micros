#include <xc.h>
#include "lcd.h"
#include <math.h>
#include <stdio.h>


#define _XTAL_FREQ 4000000

#include "teclado.h"

#pragma config WDT = OFF
#pragma config FOSC = HS
#pragma config LVP = OFF
#pragma config PBADEN = OFF

void mensaje2 (void);

void main(void) {
    
    // ver como poner el puerto C en salida
    
    __delay_ms(500);
    
    I2C_Master_Init();
    I2C_Master_Start();
    
    LCD_Init(0x4E);
    LCD_Clear();
    LCD_Set_Cursor(1, 4);
    LCD_Write_String("Bie");
    LCD_Set_Cursor(2, 1);
    LCD_Write_String("Grupo 2:");
    LCD_CHAR_PROPIO();
    LCD_Write_Char(0x00);
    Backlight(); 
    
    
    
    //__delay_ms(5000);
    LCD_Clear();
     mensaje2();
     while (1) {
     //    while(COLUMNA1 and COLUMNA2 AND COLUMNA3 and COLUMNA4){}
       
         
    }
    
    return;
}

void mensaje2 (void){
         LCD_Set_Cursor(1, 1);
         LCD_Write_String("Piezas a contar:");
         LCD_Set_Cursor(2, 1);
         Cursor();
}        