
//Lab4
#pragma config WDT = OFF
#pragma config FOSC = INTOSC_EC
#pragma config LVP = OFF
#pragma config PBADEN = OFF

#define _XTAL_FREQ 8000000
#define TRIGGER RC0
#define ECHO RC1

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

unsigned char Tecla = 0;

int flagParar = 1;
int menu = 2;
int v = 1023;
int decena = 0;
int unidad = 0;
int digito = 1;
float t = 24.32;
char buffer[30] = "Iniciando";

int mostrar = 0;
int cantidad = 0;
int contador = 0;
int cantidadResta = 0;
int cantidadRestaUnidad = 0;
int cantidadRestaDecena = 0;
int contadorUnidad = 0;
int contadorDecena = 0;
float porcentaje = 0;
float porcentajeManual = 1;
int motorEstado = 1;

unsigned char recibir;

unsigned int resultado_ADC; //VARIABLE DE ADC

int color[] = {2, 6, 4, 5, 1, 0}; //magenta, azul, cyan, verde, amarillo y blanco
int rojo = 3;

const char figura_1[8] = {0x0A, 0x0A, 0x0A, 0x00, 0x11, 0x11, 0x0E, 0x00}; //cara
const char figura_2[8] = {0x04, 0x11, 0x0E, 0x04, 0x04, 0x0A, 0x11, 0x00}; //hombre
const char figura_3[8] = {0x03, 0x03, 0x02, 0x07, 0x06, 0x0E, 0x0A, 0x13}; //dinosaurio
const char figura_4[8] = {0x04, 0x0E, 0x0A, 0x0A, 0x1F, 0x1B, 0x1F, 0x00}; //senal peligro
const char figura_5[8] = {0x0F, 0x09, 0x1C, 0x08, 0x02, 0x07, 0x12, 0x1E}; // senal reiniciar


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
void blacklighttoggle(void);
void vaciar(void);

unsigned char MedirDistancia(void); //ultrasonido
unsigned char etimeout = 0, ctimeout = 0;


unsigned int Conversion(unsigned char); //ADC 

void Duty_motor(float);

void interrupt ISR(void);

void main() {
    unsigned char d;
    unsigned int distanciaContar;
    OSCCON = 0b01110000; //oscilador interno se ajusta a 8 MHz, ajustar tambien para el LCD
    __delay_ms(1); //se espera que se estabilice el oscilador interno

    ADCON0 = 0b00000001;
    ADCON2 = 0b10001000;

    int pina0;
    TRISE = 0;
    TRISD = 0;
    TRISA = 0b00000001;
    TRISC = 0b00000010;

    LATD = 0b00000000; // DISPLAY  SEGMENTS
    LATE = 0b00000111; //LED RGB

    LATA5 = 1; //pinde de backlitgh
    TXSTA = 0b00100100;
    RCSTA = 0b10010000;
    BAUDCON = 0b00001000;
    SPBRG = 207; // 25 para 1Mhz 207 para 8Mhz
    unsigned char i;
    TRISB = 0b11110000;
    LATB = 0b00000000;
    RBPU = 0;
    __delay_ms(100);

    TMR0 = 3036;
    T0CON = 0b00000100; //Ultrasonido; sobreflujo 1segundo 
    TMR0IF = 0;
    TMR0IE = 1;
    TMR0ON = 1;
    RBIF = 0;
    RBIE = 1;
    GIE = 1;
    ADCON1bits.PCFG = 0x0E; // Coloca todos los pines como digitales

    PR2 = 249; // PERIDO DE 1KHZ
    CCPR1L = 125; // DUTY CICLE
    T2CON = 1; // PRESCALER DE 4
    CCP1CON = 12; // MODO PWM


    T1CON = 0b10010000; //Ajuste de timer1: prescaler 2 para ultrasonido

    TMR2 = 0; //INICA EN CERO 
    TMR2ON = 1;


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



        d = MedirDistancia();
        sprintf(buffer, "Distancia = %u cm \nPWM = %u %c \n", (int) d, (int) porcentaje, 37);

        if (menu == 2 && d < 9) ContarReal();
        __delay_ms(3000);
    };

}

void blacklighttoggle(void) {
    LATA5 = !LATA5;
}

void escenario1(void) {
    menu = 1;
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
    menu = 2;
    mostrar = 1;
    Lcd_Clear();
    Lcd_NoBlink();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Faltante:");
    Lcd_Write_Char(cantidadRestaDecena);
    Lcd_Write_Char(cantidadRestaUnidad);
    Lcd_Set_Cursor(1, 14);
    Lcd_Write_String("C=");
    Lcd_Write_Char(4);
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("Objetivo:");
    Lcd_Write_Char(0b00110000 + decena);
    Lcd_Write_Char(0b00110000 + unidad);
    Lcd_Set_Cursor(2, 14);
    Lcd_Write_String("#=X");
    Lcd_Write_Char(3);

};

void escenario3(void) {
    menu = 3;
    Lcd_Clear();
    Lcd_NoBlink();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Cuenta finalizada");
    Lcd_Set_Cursor(2, 13);
    Lcd_Write_String("A:OK");

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
    LATE = rojo;
    CCPR1L = 0;
    motorEstado = 0;

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
    } else if (digito == 2) {
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
        if (digito == 1) decena = 0;
        else if (digito == 2) unidad = 0;
    }
}

void ContarReal(void) {
    cantidad = (decena * 10) + unidad;
    contador++;
    cantidadResta = cantidad - contador + 1;
    cantidadRestaUnidad = 0b00110000 + cantidadResta % 10;
    cantidadRestaDecena = 0b00110000 + cantidadResta / 10;
    contadorUnidad = (contador - 1) % 10;
    contadorDecena = (contador - 1) / 10;

    LATD = contadorUnidad;
    LATE = color[contadorDecena];
    escenario2();
    __delay_ms(1000);
    if (!cantidadResta) {
        vaciar();
        escenario3();
    }

}

void vaciar(void) {
    unidad = 0;
    unidad = 0;
    cantidadRestaUnidad = 0b00110000 + unidad;
    cantidadRestaDecena = 0b00110000 + unidad;
    LATD = 0;
    LATE = color[0];
    contador = 0;
    digito = 1;
}

void Reiniciar(void) {

    cantidadRestaUnidad = 0b00110000 + unidad;
    cantidadRestaDecena = 0b00110000 + decena;
    LATD = 0;
    LATE = color[0];
    contador = 0;
    digito = 1;
    escenario2();
}

void Terminar(void) {
    vaciar();
    escenario1();
}

void Trasmitir(void) {
    int i;
    for (i = 0; buffer[i] != '\0'; i++) {
        while (TRMT == 0);
        TXREG = buffer[i];
    }
    TXREG = '\n';
}

unsigned int Conversion(unsigned char canal) {
    ADCON0 = (ADCON0 & 0b00000011) | (canal << 2);
    GO = 1; //bsf ADCON0,1
    while (GO == 1);
    return ADRES;
}

void okmenu(void) {
    if (menu == 1) ContarReal(); //comienza a contar
    else if (menu == 2); //no retorna a ningun lado
    else if (menu == 3) escenario1(); //retorna al principal de conteo desde la patalla de finalizar  
}

void interrupt ISR(void) {
    if (RBIF == 1 && flagParar) {

        if (PORTB != 0b11110000) {
            Tecla = 0;
            LATB = 0b11111110;

            if (RB4 == 0) PiezaAContar('1'); // 1
            else if (RB5 == 0) PiezaAContar('2'); // 2
            else if (RB6 == 0) PiezaAContar('3'); // 3
            else if (RB7 == 0 && menu != 2) okmenu(); // OK
            else {
                LATB = 0b11111101;
                if (RB4 == 0) PiezaAContar('4'); //4
                else if (RB5 == 0) PiezaAContar('5'); //5
                else if (RB6 == 0) PiezaAContar('6'); //6
                else if (RB7 == 0 && menu == 1) borrarDigito(); // BORRAR DIGITO
                else {
                    LATB = 0b11111011;
                    if (RB4 == 0) PiezaAContar('7'); //7
                    else if (RB5 == 0) PiezaAContar('8');
                    else if (RB6 == 0) PiezaAContar('9');
                    else if (RB7 == 0 && menu == 2) Reiniciar();
                    else {
                        LATB = 0b11110111;
                        if (RB4 == 0) blacklighttoggle();
                        else if (RB5 == 0) PiezaAContar('0');
                        else if (RB6 == 0 && menu == 2) Terminar();
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
        if (etimeout == 1) //Se cuenta cada segundo si esta habilitada la condición
            ctimeout++; // de antibloqueo
        else
            ctimeout = 0; //Si no esta habilitada se reinicia la variable
        if (ctimeout >= 1) //Si la condición de antibloqueo excede dos cuentas
            etimeout = 0; //se coloca la habilitación del antibloqueo en 0

        resultado_ADC = Conversion(0);
        Duty_motor(resultado_ADC);
    }

    if (RCIF == 1) {
        while (RCIF == 0);
        recibir = RCREG;
        if (recibir == 'p' || recibir == 'P') escenario4();
        else if (flagParar) {
            if (recibir == 'e' || recibir == 'E') motorEstado = 1;
            else if ((recibir == 'a' || recibir == 'A')) motorEstado = 0;
            else if ((recibir == 'r' || recibir == 'R') && menu == 2) Reiniciar();
            else if ((recibir == 'z' || recibir == 'Z')) {
                porcentajeManual = 0;
                porcentaje = 0;
                CCPR1L = 0;
            }
            else if ((recibir == 'x' || recibir == 'X')) {
                porcentajeManual = 0;
                porcentaje = 20;
                CCPR1L = 50;
            }
            else if ((recibir == 'c' || recibir == 'C')) {
                porcentajeManual = 0;
                porcentaje = 40;
                CCPR1L = 100;
            }
            else if ((recibir == 'v' || recibir == 'V')) {
                porcentajeManual = 0;
                porcentaje = 60;
                CCPR1L = 150;
            }
            else if ((recibir == 'b' || recibir == 'B')) {
                porcentajeManual = 0;
                porcentaje = 80;
                CCPR1L = 200;
            }
            else if ((recibir == 'n' || recibir == 'N')) {
                porcentajeManual = 0;
                porcentaje = 100;
                CCPR1L = 250;
            }
            else if ((recibir == 'm' || recibir == 'M')) {
                porcentajeManual = 1;
            };
        };
    }
}

void Duty_motor(float ADC) {
    if (motorEstado) {
        float escalarADC = (ADC / 1024)*249; //escarlar hasta 250
        // int escalarADC = ADC;
        if (escalarADC >= 249) escalarADC = 249;
        else if (escalarADC < 0) escalarADC = 0;
        if(porcentajeManual){
        porcentaje = escalarADC * 0.4;
        CCPR1L = (int) escalarADC;
        }
    }
    else CCPR1L = 0;
}

unsigned char MedirDistancia(void) {
    unsigned char aux = 0;
    CCP2CON = 0b00000100; //Ajustar CCP en modo captura con flanco de bajada
    CCP2IF = 0; //Iniciar bandera CCPx en 0
    CCPR2 = 0;
    TRIGGER = 1; //Dar inicio al sensor
    __delay_us(10);
    TRIGGER = 0;
    TMR1 = 0; //Iniciamos el timer1 en 0
    etimeout = 1; //Se habilita la condición de antibloqueo
    while (ECHO == 0 && etimeout == 1); //Se espera que el sensor empiece la
    //medición o que pase el antibloqueo (aprox 2s)
    if (etimeout == 0) { //Si el sensor no responde se retorna un 0
        return 0;
    }
    TMR1ON = 1; //Se da inicio al timer1 o medición de tiempo
    while (CCP2IF == 0 && TMR1IF == 0); //Espera a que la señal de ultrasonido regrese
    TMR1ON = 0; //Se da parada al timer 1 o medición de tiempo
    if (TMR1IF == 1) //Se comprueba que la medición del pulso del sensor no
        aux = 255; //exceda el rango del timer1, si es asi se limita a 255
    else {
        if (CCPR2 >= 14732) //Si el sensor excede 254cm se limita a este valor
            CCPR2 = 14732;
        aux = CCPR2 / 58 + 1; //Se calcula el valor de distancia a partir del tiempo
    }
    return aux; //Se retorna la medición de distancia obtenida
}
