#include <xc.h>
#define _XTAL_FREQ 1000000
#pragma config WDT = OFF
#pragma config FOSC = INTOSC_EC
#pragma config LVP = OFF
#pragma config PBADEN = OFF


int colorIndice = 0;
int color[] = {2 , 6 , 4 , 5 , 1 , 0}; //magenta, azul, cyan, verde, amarillo y blanco
int rojo = 3;
int parar = 1; //logica negativa

void __interrupt() ISR(void);

void main(void) {
    TRISE = 0;
    TRISD = 0;
    TRISA = 0;
    TRISB = 1;
    LATD = 0b00000000; // DISPLAY  SEGMENTS
    LATE = 0b00000111; //LED RGB

    T0CON = 0b00000001; //inicio USO DE TMR0
    TMR0 = 3036;
    TMR0IF = 0;
    TMR0IE = 1;
    TMR0ON = 1; // fin TMR0

    INTEDG0 = 1; //Inicio configuración pulsador
    INT0IF = 0;
    INT0IE = 1; // fin pulsador
    
    INT1IF = 0; // Inicio configuración interruptor
    INT1IE = 1; // fin interruptor

    GIE = 1;
     while (1) {
            
            if (LATD == 0b00001010) {
            LATD = 0;
            LATE=color[colorIndice%6];
            colorIndice++;
        }   
            if(parar){
            __delay_ms(1000);
            LATD++;
            }
    }
    return;
}

void __interrupt() ISR(void) {
    if (TMR0IF == 1) {
        TMR0 = 3036; //PRESET
        TMR0IF = 0;
        LATA1 = !LATA1; //toggle!
    }
    if (INT0IF == 1) {
       INT0IF = 0;
       if(parar){
       LATD = 0;
       LATE = 0b00000111;
       colorIndice = 0;}
    }
    if (INT1IF == 1) {
       INT1IF = 0;
       LATE = rojo;
       parar = 0;
    }
}
