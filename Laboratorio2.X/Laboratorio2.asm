;librerias
    include p18f4550.inc
;Configuracion
   CONFIG FOSC = EC_EC
   CONFIG WDT = OFF ; oscilador externo, y WatchDog apagado
   CONFIG LVP = OFF
;variables
  aux1 equ 0h
;instrucciones
Inicio 
 code
  bcf TRISD,0 ;configura como salida
  bcf TRISD,1 ;configura como una salida
  bcf TRISD,2 ;
  Ciclo
  bcf LATD,0 
  bsf LATD,0
  bcf LATD,1 
  bsf LATD,1
  bcf LATD,2 
  bsf LATD,2

goto Ciclo   
end