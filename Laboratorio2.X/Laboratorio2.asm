;librerias
    include p18f4550.inc
;Configuracion
   CONFIG FOSC = EC_EC
   CONFIG WDT = OFF ; oscilador externo, y WatchDog apagado
   CONFIG LVP = OFF ; 
;variables
  aux1 equ 0h
;instrucciones
Inicio 
 code
  bcf TRISD,0 ;configuracion como salidas
  bcf TRISD,1 ;
  bcf TRISD,2 ;
  Ciclo
  ;bcf LATD,0 
  ;bsf LATD,0
  ;bcf LATD,1 
  ;bsf LATD,1
  ;bcf LATD,2 
  ;bsf LATD,2
  ;codigo de colores en logica inversa por ser una RGB de anodo común.
  movlw b'00000011' ;Azul
  movwf LATD 
  movlw b'00000001' ;Cyan
  movwf LATD
  movlw b'00000101' ;Verde
  movwf LATD
  movlw b'0000100' ;Amarillo
  movwf LATD
  movlw b'00000000' ;Blanco
  movwf LATD
  movlw b'00000010' ;Magenta
  movwf LATD
  movlw b'00000110' ;Rojo
  movwf LATD
  movlw b'0000111' ;Negro
  movwf LATD
goto Ciclo   
end