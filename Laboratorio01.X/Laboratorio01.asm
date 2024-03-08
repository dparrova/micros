;Primera Sección ;Traer librerias
include p18f4550.inc
    
;Segunda Sección
    ;tiene que ver con la confguración
    
;Tercera Sección; variables
aux1 equ 0h
aux2 equ 1h    
aux3 equ 2h
aux4 equ 3h
 
Inicio
Ejercicio_1
    movlw .7  
    movwf aux1 
    movf aux1,w
    addlw .3
    movwf aux1
    
Ejercicio_2
    movlw .8 
    movwf aux1
    movlw .10
    movwf aux2
    movf aux1,w
    addwf aux2

Ejercicio_3
    movlw .5
    movwf aux1 
    movf aux1,w
    sublw .9
    movwf aux1

Ejercicio_4
    movlw .6
    movwf aux1
    movlw .4
    movwf aux2 
    movf aux1,w 
    subwf aux2 ; da como resultado 254 porque es un dato de 8 bites ¡aclarar!
    
    Ejercicio_5
    movlw .5
    movwf aux1
    movf aux1,w
    mullw .4 ;el resultado se almacena en dos variables PRODH y PRODL
    movf PRODL,w ;traemos el PRODL al entorno

Ejercicio_6
    movlw .12
    movwf aux1
    movlw .15
    movwf aux2
    movf aux1,w
    mulwf aux2

Ejercicio_7
    movlw .12
    movwf aux1
    comf aux1 ; complemento a1 

Ejercicio_8
    movlw .12
    movwf aux1
    negf aux1 ; complemento a2

Ejercicio_9
    movlw .35
    movwf aux1
    movf aux1,w ;radundamos casos?
    iorlw .7
    movwf aux1

Ejercicio_10
    movlw .20
    movwf aux1
    movlw .56
    movwf aux2
    movf aux1,w
    iorwf aux2
 
Ejercicio_11
    movlw .62
    movwf aux1
    movf aux1,w
    andlw .15
    movwf aux1
 
 Ejercicio_12
    movlw .45
    movwf aux2
    movlw .100
    movwf aux1
    movf aux1,w
    andwf aux2
 
 Ejercicio_13
    movlw .120
    movwf aux1
    movf aux1,w
    xorlw .1
    movwf aux2
 
 Ejercicio_14
    movlw .17
    movwf aux1
    movlw .90
    movwf aux2
    xorwf aux1,w
    movwf aux3

 Ejercicio_15
    movlw .25
    movwf aux1
    movlw .40 
    movwf aux2
    movlw .103
    movwf aux3
    movf aux3,w
    xorlw 0xD0
    movwf aux3
    movf aux1,w
    iorwf aux2,w
    movwf aux1
    andwf aux3,w
    movwf aux4

 Ejercicio_16
    movlw .18
    movwf aux1
    movlw .60 
    movwf aux2
    movlw .16
    movwf aux3
    movlw b'00011010'
    subwf aux3,w
    movwf aux3
    movf aux1,w
    addwf aux2,w
    movwf aux1
    movf aux3,w
    mullw .3
    movf PRODL,w
    movwf aux3
    movf aux3,w
    subwf aux1,w
    movwf aux4
    
    movlw .0
    movf aux1
    movf aux2
    movf aux3
    movf aux4
    
goto Inicio
end



