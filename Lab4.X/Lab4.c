#include <xc.h>
#include "lcd.h"
#include <math.h>
#include <stdio.h>


#define _XTAL_FREQ 4000000

#pragma config WDT = OFF
#pragma config FOSC = HS
#pragma config LVP = OFF
#pragma config PBADEN = OFF

void main(void) {
    __delay_ms(500);
    
    I2C_Master_Init();
    I2C_Master_Start();
    
    LCD_Init(0x27);
    LCD_Clear();
    LCD_Set_Cursor(1, 1);
    LCD_Write_String("Hola mundo");
    noBacklight(); 
    
     while (1) { 
       LCD_Set_Cursor(1, 1);
       LCD_Write_String("Hola mundo");

    }
    
    return;
}