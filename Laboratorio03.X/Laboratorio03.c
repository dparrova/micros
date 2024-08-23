#include <xc.h>
#define _XTAL_FREQ 1000000
#pragma config WDT = OFF
#pragma config FOSC = INTOSC_EC
#pragma config LVP = OFF
#pragma config PBADEN = OFF


void __interrupt() ISR(void);

void main(void) { 
    TRISE=0;
    TRISD=0;
    TRISA=0;
    TRISB=1;
    LATD = 0b00000000; // DISPLAY  SEGMENTS 
    LATE = 0b00000111; //LED RGB
    INTEDG0=1;
    INT0IF=0;
    INT0IE=1;
    GIE=1;
    
    T0CON=0b00000001;
    TMR0=3036;
    TMR0IF=0;
    TMR0IE=1;
    GIE=1;
    TMR0ON=1;
     
      while(1){
          LATD++;
      if(LATD==0b00001010)
          //
      {
              LATD=0;
              LATE--;
            
      }
      __delay_ms(1000);    
     //LATA1=!LATA1; //FUNCIONANDO!
     
    }
    return;
}

void __interrupt() ISR(void){
    if(TMR0IF==1){
        TMR0=3036 ;
        TMR0IF=0;
        LATA1=LATA1^1;
 //if(INT0IF==1){
   //  INT0IF=0;
     //LATD++; 
     
 }   
}
// comentario