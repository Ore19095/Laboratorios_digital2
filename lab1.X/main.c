/*
 * File:   main.c
 * Author: Angel Orellana
 *
 * Created on 21 de enero de 2021, 06:25 PM
 */


#include <xc.h>


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define btnSemaforo PORTBbits.RB0
#define btnJ1 PORTBbits.RB1
#define btnJ2 PORTBbits.RB2


#define _XTAL_FREQ 4000000


static char valores[] = {1,2,4,8,16,32,64,128};
void semaforo(void);

void main(void) {
    // SE CONFIGURAN LOS PUERTOS
    ANSEL  = 0;
    ANSELH =0;
    TRISA = 0;
    TRISB= 255;
    TRISC = 0;
    TRISD = 0; //PUERTOS A C Y D COMO SALIDAS  y puerto b como entrada]
    OPTION_REGbits.nRBPU = 0;
    char inicio =0;//variable que se utilizar
    char contadorJ1 =0  , contadorJ2= 0;
    char puertobAnterior;
    while (1){
        puertobAnterior = PORTB;
            if(  (puertobAnterior && 1 ) == 0 ){
            __delay_us(100); //delay de 100 us
            if (btnSemaforo == 1) {  //  solto el boton
                inicio =1; // se da inicio a la secuencia, para que empiece el juego
                semaforo();
            } 
            while(inicio){ // entra en esta parte si el valor de inicio es diferente de 0
                if ( (puertobAnterior && 2) == 0){
                    __delay_us(100);
                    if(btnJ1 == 1 ) contadorJ1++;
                }
            }
     }    
    
    }
    
    
    
    
    return; 
}

void semaforo(){
    PORTD = 1;
    __delay_ms(500);
    PORTD = 2;
    __delay_ms(500);
    PORTD =4;
}