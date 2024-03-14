;librerias
    include p18f4550.inc
    ;Configuracion
   CONFIG FOSC = EC_EC
   CONFIG WDT = OFF ; oscilador externo, y WatchDog apagado
  ;variables
  
  ;instrucciones
Inicio
  CODE
  bsf TRISD,0 ;configura como entrada
  bsf TRISD,1 ;configura como una entrada
  bsf TRISD,2 ;
  Ciclo
  bcf LATD,0 
  bsf LATD,0

goto Ciclo   
end