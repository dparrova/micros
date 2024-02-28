;Primera Secci�n : importar librerias del pic que vamos a trabajar
include P18F4550.inc
;Segunda secci�n : configuraci�n, solo cuando se usa un ucontrolador no se usa para un codigo de solo simular

;Tercera Secci�n : definir variables -- en asamble no hay tipo, se define entera sin signo 

;nombre - palabra reservada - direccion de la memoria
aux1 equ 0h ;en la direcci�n 0 y h es hexadecimal
aux2 equ 1h
aux3 equ 0xa;cuando la direccion tiene todas letras se usa el sufijo x en este caso 0xa
aux4 equ 3h 
;Cuarta Secci�n :  
Inicio ;tiene dos funciones, etiquetar todo de ah� para abajo. 
;pseudo codigo aux1 <- 5, se usa un registro w (registro de trabajo) entonces se puede hacer aux1 <- w
punto1
movlw .7 ; el punto indica que es decimal
movwf aux1 
movf aux1,w
addlw .3
movwf aux1

punto2
movlw .8 
movwf aux1
movlw .10
movwf aux2
movf aux1,w
addwf aux2

punto3
movlw .5
movwf aux1 
movf aux1,w
sublw .9
movwf aux1

punto4
movlw .6
movwf aux1
movlw .4
movwf aux2 
movf aux1,w 
subwf aux2 ; da como resultado 254 porque es un dato de 8 bites aclarar!!

punto5
movlw .5
movwf aux1
movf aux1,w
mullw .4 ;el resultado se almacena en dos variables PRODH y PRODL
movf PRODL,w ;traemos el PRODL al entorno

punto6
movlw .12
movwf aux1
movlw .15
movwf aux2
movf aux1,w
mulwf aux2

punto7
movlw .12
movwf aux1
comf aux1 ; complemento a1 

punto8
movlw .12
movwf aux1
negf aux1 ; complemento a2

punto9
movlw .120
movwf aux1
movf aux1,w
iorlw .1

punto10
movlw .17
movwf aux1
movlw .90
movwf aux2
movf aux1,w
iorwf aux2
 
;Ejercicio 11
 movlw .62
 movwf aux1
 andlw .15
 ;mover lo que esta en w a un registro
 movwf aux1
 ;variables inicializadas en tres sistemas numericos
 
 ;Ejercicio 12
 movlw .45
 movwf aux2
 movlw .100
 movwf aux1
 andwf aux2
 
 ;Ejercicio 13
 movlw .120
 movwf aux1
 xorwf .1
 movwf aux2
 
 ;Ejercicio 14
 movlw .17
 movwf aux1
 movlw .90
 movwf aux2
 xorwf aux1,w
 movwf aux3

 ;Ejercicio 15
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
 
 ;Ejercicio 16
 movlw .18
 movwf aux1
 movlw .60 
 movwf aux2
 movlw .16
 movwf aux3
 movf aux3,w
 sublw b'11010'
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

goto Inicio ;simpre debe exister un apuntador para que se ejecute siempre
end




