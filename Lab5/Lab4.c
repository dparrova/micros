
//Lab4
#pragma config WDT = OFF
#pragma config FOSC = INTOSC_EC
#pragma config LVP = OFF
#pragma config PBADEN = OFF
#define _XTAL_FREQ 1000000

#include <xc.h>
#include <stdio.h>
#include "lcd.h"

unsigned char Tecla = 0;

int flagParar = 1;
//int flagReiniciar = 0;
//int flagTerminar = 0;
int v = 1023;
int decena = 0;
int unidad = 0;
int digito = 1;
float t = 24.32;
char buffer[20] = "valor de ADC=";

 int mostrar = 0;
 int cantidad = 0;
 int contador = 0;
 int cantidadResta = 0;
 int cantidadRestaUnidad = 0;
 int cantidadRestaDecena = 0;
 int contadorUnidad = 0;
 int contadorDecena = 0;

int color[] = {2, 6, 4, 5, 1, 0}; //magenta, azul, cyan, verde, amarillo y blanco
int rojo = 3;

const char figura_1[8] = {0x0A, 0x0A, 0x0A, 0x00, 0x11, 0x11, 0x0E, 0x00};
const char figura_2[8] = {0x04, 0x11, 0x0E, 0x04, 0x04, 0x0A, 0x11, 0x00};
const char figura_3[8] = {0x03, 0x03, 0x02, 0x07, 0x06, 0x0E, 0x0A, 0x13}; //dinosaurio
const char figura_4[8] = {0x04, 0x0E, 0x0A, 0x0A, 0x1F, 0x1B, 0x1F, 0x00};
const char figura_5[8] = {0x0F, 0x09, 0x1C, 0x08, 0x02, 0x07, 0x12, 0x1E};


void escenario1(void);
void escenario2(void);
void escenario3(void);
void escenario4(void);
void escenario5(void);
void PiezaAContar(char a);
void borrarDigito(void);
void ContarReal(void);
void Reiniciar(void);
void Terminar(void);
void Trasmitir(void);

void interrupt ISR(void);

void main() {
    int pina0;
    TRISE = 0;
    TRISD = 0;
    TRISA = 0b00000001;
    
    LATD = 0b00000000; // DISPLAY  SEGMENTS
    LATE = 0b00000111; //LED RGB

    TXSTA = 0b00100100;
    RCSTA = 0b10000000;
    BAUDCON = 0b00001000;
    SPBRG = 25;
    
    unsigned char i;
    TRISB = 0b11110000;
    LATB = 0b00000000;
    RBPU = 0;
    __delay_ms(100);
    TMR0 = 3036;
    T0CON = 0b00000001;
    TMR0IF = 0;
    TMR0IE = 1;
    TMR0ON = 1;
    RBIF = 0;
    RBIE = 1;
    GIE = 1;
    ADCON1bits.PCFG = 0x0F;           // Coloca todos los pines como digitales
    Lcd_Init(); // Inicializa la pantalla LCD

    Lcd_CGRAM_Init(); // Accede a la CRGAM
    Lcd_CGRAM_CreateChar(0, figura_1); // Almacena el caracter 1 en la posicion 0 de la CGRAM
    Lcd_CGRAM_CreateChar(1, figura_2); // Almacena el caracter 2 en la posicion 1 de la CGRAM
    Lcd_CGRAM_CreateChar(2, figura_3); // Almacena el caracter 3 en la posicion 2 de la CGRAM
    Lcd_CGRAM_CreateChar(3, figura_4); // Almacena el caracter 4 en la posicion 3 de la CGRAM
    Lcd_CGRAM_CreateChar(4, figura_5); // Almacena el caracter 4 en la posicion 3 de la CGRAM
    Lcd_CGRAM_Close(); // Sale de la CGRAM
    Lcd_Clear(); // Limpia la pantalla


    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Laboratorio 04");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("PIC18F4550");
    Lcd_Set_Cursor(2, 12);
    Lcd_Blink();
    __delay_ms(200);
    Lcd_NoBlink();


    for (i = 1; i <= 5; i++) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Micros UNAL");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Char(0);
        Lcd_Set_Cursor(2, 7);
        Lcd_Write_Char(1);
        Lcd_Set_Cursor(2, 2 + i);
        Lcd_Write_Char(2);
        __delay_ms(1000);
    }
    Lcd_Clear();
    escenario1();
    
    while (1) {
    
    pina0 = PORTAbits.RA0; 
    if (mostrar && pina0==1) {
        ContarReal();
       
    }
    };

}

void escenario1(void) {
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Piezas a contar:");
    Lcd_Set_Cursor(2, 9);
    Lcd_Write_String("A:ok B:");
    Lcd_Write_Char(0b01111111);
    Lcd_Set_Cursor(2, 1);
    Lcd_Blink();
};

void escenario2(void) {
    
    Lcd_Clear();
    Lcd_NoBlink();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Faltante:");
    Lcd_Write_Char(cantidadRestaDecena);
    Lcd_Write_Char(cantidadRestaUnidad);
    Lcd_Set_Cursor(1, 14);
    Lcd_Write_String("C:");
    Lcd_Write_Char(4);
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("Objetivo:");
    Lcd_Write_Char(0b00110000 + decena);
    Lcd_Write_Char(0b00110000 + unidad);
    Lcd_Set_Cursor(2, 14);
    Lcd_Write_String("D:");
    Lcd_Write_Char(3);
    mostrar = 1;

};

void escenario3(void) {
    Lcd_Clear();
    Lcd_NoBlink();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Cuenta finalizada");
    Lcd_Set_Cursor(2, 13);
    Lcd_Write_String("A:OK");
    while(1);
};

void escenario4(void) { //PARADA DE EMERGENCIA
    Lcd_Clear();
    Lcd_NoBlink();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Parada de");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("Emergencia ");
    Lcd_Write_Char(3);
    flagParar = 0;
    LATE=rojo;

};

void escenario5(void) {
    Lcd_Clear();
    Lcd_NoBlink();
    Lcd_Set_Cursor(2, 1);


};

void PiezaAContar(char a) {

    if (digito == 1) {
        decena = a & 0x0f;
        if (decena >= 6) decena = 5;
        Lcd_Write_Char(0b00110000 + decena);
        digito++;
    }
    else if (digito == 2) {
        unidad = a & 0x0f;
        Lcd_Write_Char(0b00110000 + unidad);
        digito++;
    }


}

void borrarDigito(void) {
    if (digito != 1) {
        Lcd_Set_Cursor(2, digito - 1);
        Lcd_Write_Char(' ');
        Lcd_Set_Cursor(2, digito - 1);
        digito--;
        if(digito == 1) decena = 0;
        else if(digito == 2) unidad = 0;
    }
}

void ContarReal(void){
    cantidad = (decena * 10) + unidad;
    contador++;
    cantidadResta = cantidad - contador +1;
    cantidadRestaUnidad =0b00110000 + cantidadResta%10;
    cantidadRestaDecena =0b00110000 + cantidadResta/10;
    contadorUnidad = (contador-1)%10;
    contadorDecena = (contador-1)/10;
    
   // LATD=contadorUnidad;
    LATD = contadorUnidad;
    LATE = color[contadorDecena];
    escenario2();
    __delay_ms(1000);
    if(!cantidadResta) {
        escenario3();
        mostrar = 0;
    }
    
}

void Reiniciar(void){
       
        cantidadRestaUnidad =0b00110000 + unidad;
        cantidadRestaDecena =0b00110000 + decena;
        LATD = 0;
        LATE = color[0];
        contador =0;
        digito = 1;
        escenario3();
}

void Terminar(void){
        unidad = 0 ;
        unidad = 0;
        cantidadRestaUnidad =0b00110000 + unidad;
        cantidadRestaDecena =0b00110000 + unidad;
        LATD = 0;
        LATE = color[0];
        contador =0;
        digito = 1;
        escenario1();
     
}

void Trasmitir(void){
    int i;
    
    for(i=0;buffer[i]!='\0';i++)
    {    
    while(TRMT==0);
    TXREG = buffer[i];
    }
    TXREG = '\n';
    
}


void interrupt ISR(void) {
    if (RBIF == 1 && flagParar) {

        if (PORTB != 0b11110000) {
            Tecla = 0;
            LATB = 0b11111110;

            if (RB4 == 0) PiezaAContar('1'); // 1
            else if (RB5 == 0) PiezaAContar('2'); // 2
            else if (RB6 == 0) PiezaAContar('3'); // 3
            else if (RB7 == 0) ContarReal(); // OK
            else {
                LATB = 0b11111101;
                if (RB4 == 0) PiezaAContar('4'); //4
                else if (RB5 == 0) PiezaAContar('5'); //5
                else if (RB6 == 0) PiezaAContar('6'); //6
                else if (RB7 == 0) borrarDigito(); // BORRAR DIGITO
                else {
                    LATB = 0b11111011;
                    if (RB4 == 0) PiezaAContar('7'); //7
                    else if (RB5 == 0) PiezaAContar('8');
                    else if (RB6 == 0) PiezaAContar('9');
                    else if (RB7 == 0) Reiniciar();
                    else {
                        LATB = 0b11110111;
                        if (RB4 == 0) Tecla = 13;
                        else if (RB5 == 0) PiezaAContar('0');
                        else if (RB6 == 0) Terminar();
                        else if (RB7 == 0) escenario4();
                    }
                }
            }
            LATB = 0b11110000;
        }
        __delay_ms(200);

        RBIF = 0;

    }
    if (TMR0IF == 1) {
        TMR0IF = 0;
        TMR0 = 3036;
        LATA1 = !LATA1; //toggle!
        Trasmitir();
    }
}