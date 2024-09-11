#include <xc.h>
#include "teclado.h"

//pasos, primero comprobar que las exista un cambio en las entradas 
//hacer el algoritmo de verificacion de boton
// se ponen las filas en 1110
// conmprobar en las columnas cual esl la tecla

/*
void resturnTeclado(){
    __delay_ms(10); //retardo para antirebote
    LATB = 0bxx1110xx;
    if(!COLUMNA1)
        return char '1';
    if(!COLUMNA2)
        return char '2';
    if(!COLUMNA3)
        return char '3';
    if(!COLUMNA4)
        return char 'A';
    LATB = 0bxx1101xx;
    if(!COLUMNA1)
        return char '2';
    if(!COLUMNA2)
        return char '3';
    if(!COLUMNA3)
        return char '4';
    if(!COLUMNA4)
        return char 'B';
    LATB = 0bxx1011xx;
    if(!COLUMNA1)
        return char '7';
    if(!COLUMNA2)
        return char '8';
    if(!COLUMNA3)
        return char '9';
    if(!COLUMNA4)
        return char 'C';
    LATB = 0bxx0111xx;
    if(!COLUMNA1)
        return char '*';
    if(!COLUMNA2)
        return char '0';
    if(!COLUMNA3)
        return char '#';
    if(!COLUMNA4)
        return char 'D';
}
*/