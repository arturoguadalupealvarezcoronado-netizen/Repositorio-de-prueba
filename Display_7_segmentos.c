// CONFIG BITS
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>
#define _XTAL_FREQ 4000000

// Tabla para display de 7 segmentos (ánodo común)
unsigned char numeros[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

void main(void) {
    TRISB = 0x00;   // Display como salida
    TRISA0 = 1;     // RA0 como entrada
    PORTB = 0;      // Display apagado

    int contador = 0;
    PORTB = numeros[contador];

    while(1){
        // Detectar pulsación (botón en RA0)
        if (RA0 == 1) {
            __delay_ms(20);       // Antirrebote
            if (RA0 == 1) {       // Confirmar que sigue presionado
                
                // Aumentar contador
                contador++;
                if (contador > 9)
                    contador = 0;

                // Mostrar número
                PORTB = numeros[contador];

                // Esperar a que suelte el botón (evita múltiples incrementos)
                while(RA0 == 1);
                __delay_ms(20);   // Antirrebote al soltar
            }
        }
    }
}