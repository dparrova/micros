;Primera Sección : importar librerias del pic que vamos a trabajar
include P18F4550.inc
;Segunda sección : configuración, solo cuando se usa un ucontrolador no se usa para un codigo de solo simular

;Tercera Sección : definir variables -- en asamble no hay tipo, se define entera sin signo 

;nombre - palabra reservada - direccion de la memoria
aux1 equ 0h ;en la dirección 0 y h es hexadecimal
aux2 equ 1h
aux3 equ 0xa;cuando la direccion tiene todas letras se usa el sufijo x en este caso 0xa
aux4 equ 3h 
;Cuarta Sección :  
Inicio ;tiene dos funciones, etiquetar todo de ahí para abajo. 
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

goto Inicio ;simpre debe exister un apuntador para que se ejecute siempre
end





