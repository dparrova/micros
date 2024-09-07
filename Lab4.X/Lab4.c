#define _XTAL_FREQ 1000000

#include <xc.h>
#include "lcd.h"
#include <math.h>
#include <stdio.h>




//#include "teclado.h"

#pragma config WDT = OFF
#pragma config FOSC = INTOSC_EC
#pragma config LVP = OFF
#pragma config PBADEN = OFF


unsigned char Tecla=0;

void interrupt ISR(void);
void mensaje2 (void);

void main(void) {
    TRISB= 0b11110000;
    TRISD=0;
    LATB= 0b00000000;
    LATD=0;
    RBPU=0;
    
    RBIF=0;
    RBIE=1;
    GIE=1;
    
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
       
         
    LCD_Set_Cursor(2, 1);
    LCD_Write_String(Tecla);
    }
    
    return;
}

void mensaje2 (void){
         LCD_Set_Cursor(1, 1);
         LCD_Write_String("Piezas a contar:");
         LCD_Set_Cursor(2, 1);
         Cursor();
}        

void interrupt ISR(void){
    if(RBIF==1){
        if(PORTB!=0b11110000){
            Tecla=0;
            LATB=0b11111110;
            if(RB4==0) Tecla=1;
            else if(RB5==0) Tecla=2;
            else if(RB6==0) Tecla=3;
            else if(RB7==0) Tecla=4;
            else{
                LATB=0b11111101;
                if(RB4==0) Tecla=5;
                else if(RB5==0) Tecla=6;
                else if(RB6==0) Tecla=7;
                else if(RB7==0) Tecla=8;
                else{
                    LATB=0b11111011;
                    if(RB4==0) Tecla=9;
                    else if(RB5==0) Tecla=10;
                    else if(RB6==0) Tecla=11;
                    else if(RB7==0) Tecla=12;
                    else{
                        LATB=0b11110111;
                        if(RB4==0) Tecla=13;
                        else if(RB5==0) Tecla=14;
                        else if(RB6==0) Tecla=15;
                        else if(RB7==0) Tecla=16;
                    }
                }
            }
            LATB=0b11110000;
        }
        __delay_ms(100);
        RBIF=0;
    }
}