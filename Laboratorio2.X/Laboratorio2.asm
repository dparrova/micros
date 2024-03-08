aux1 equ 0h; equ organiza la memoria de datos
    
ORG 0h ;vector de reset  org organiza la direccion de la memoria de instrucciones
    goto Inicio

ORG 8h ;vecto o rutina de interrupción
    goto ISR
Inicio

    
ISR 
    
    
    
    
end