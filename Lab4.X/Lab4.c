
//Lab4
#pragma config WDT = OFF
#pragma config FOSC = HS
#pragma config LVP = OFF
#pragma config PBADEN = OFF


#include <xc.h>
#include <stdio.h>
#include "lcd.h"

#define _XTAL_FREQ 48000000
int v = 1023;
float t = 24.32;
char buffer[20];

const char figura_1[8] = {0x0A, 0x0A, 0x0A, 0x00, 0x11, 0x11, 0x0E, 0x00};
const char figura_2[8] = {0x04, 0x11, 0x0E, 0x04, 0x04, 0x0A, 0x11, 0x00};

void main()
{
    ADCON1bits.PCFG = 0x0F;             // Coloca todos los pines como digitales
    Lcd_Init();                         // Inicializa la pantalla LCD
    
    Lcd_CGRAM_Init();                   // Accede a la CRGAM
    Lcd_CGRAM_CreateChar(0, figura_1);  // Almacena el caracter 1 en la posicion 0 de la CGRAM
    Lcd_CGRAM_CreateChar(1, figura_2);  // Almacena el caracter 2 en la posicion 1 de la CGRAM
    Lcd_CGRAM_Close();                  // Sale de la CGRAM
    Lcd_Clear();                        // Limpia la pantalla
    
    while(1)
    {
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Guia Lab 4");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("PIC18F4550");
        Lcd_Set_Cursor(2,12);
        Lcd_Blink();
        __delay_ms(200);
        Lcd_NoBlink();
        Lcd_Clear();
        __delay_ms(40);
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Micros UNAL");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(0);
        Lcd_Write_Char(1);
        __delay_ms(1500);
        Lcd_Clear();
        __delay_ms(400);
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Hola mundo");
        __delay_ms(500);
        for(char i=0; i<15; i++){
            Lcd_Shift_Right();
            __delay_ms(300);
        }
        __delay_ms(300);
        for(char i=0; i<15; i++){
            Lcd_Shift_Left();
            __delay_ms(300);
        }
        Lcd_Clear();
        __delay_ms(400);
        
        Lcd_Set_Cursor(1,1);
        sprintf(buffer, "Int: %u", v);
        Lcd_Write_String(buffer);
        Lcd_Set_Cursor(2,1);
        sprintf(buffer, "Float: %0.2f", t);
        Lcd_Write_String(buffer);
        __delay_ms(1500);
        Lcd_Clear();
        __delay_ms(100);
    }
}
