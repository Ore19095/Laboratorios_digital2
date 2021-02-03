/*
 * File:   main.c
 * Author: Angel Orellana
 *
 * Created on 28 de enero de 2021, 04:40 PM
 */

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
#include <xc.h>
#include <stdint.h>
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define CHANEL_0 RA1
#define CHANEL_1 RA2
#include "ADC.h"
#include "7Segmentos.h"




#define _XTAL_FREQ 4000000
// definiciones para lalibreria 7segmentos
#define SEVEN_SEGMENT_SIZE 2


#define FORMAT_DISPLAY hex


#define VALUE_TMR2 50
volatile uint16_t micros = 0; //contador de milisegundos
volatile uint16_t timeB1 = 0, timeB2=0; //variables para el control del tiempo
volatile uint8_t portbAnterior = 255; //para el control del puerto anterior
volatile uint8_t portbActual = 255;

void main(void) {
    ANSEL = 1;
    ANSELH = 0;
    TRISA = 1;//RA 1 - RA7 COMO SALIDAS DIGITALES
    TRISB = 255; // PUERTO B COMO ENTRADA
    TRISC = 0;//SALIDA
    TRISD = 0; //SALIDA 
    IOCB = 255; // INTERRUPT ON CHANGE ACTIVADA EN TODO EL PUERTO B
    PORTD = 0;
    OPTION_REGbits.nRBPU = 0; //pull up interna activada
    
    INTCONbits.GIE = 1; // se activan las interrupciones
    INTCONbits.PEIE = 1; //perifericas activadas
    INTCONbits.RBIE = 1;// interrupt on change activada
    PIE1bits.TMR2IE = 1; // interrupcion del timer 2 activada
    
    PIR2 = VALUE_TMR2; // nuemero de veces que tiene que contar para que 
    //ocurra la interrupcion cada 1 ms
    
    T2CON = 0b00000100; // prescaler de 1:1 post de 1:1 y encendido
    
    
    initADC(); // inicializar el adc
    init7S(&PORTC);
    
    uint8_t* adc0;
    while(1){
        adc0 = readADC(0);
        displayValue(*adc0);
    }
    
    return;
}

void __interrupt() isr(void){
    if (INTCONbits.RBIF){
        portbAnterior = portbActual;
        portbActual = PORTB;
        
        if ((portbAnterior & 1) == 0 &&  (portbActual & 1) == 1){
            // se entra si el valor anterior era 0
            if (micros - timeB1 >= 50){
                // si la resta entre ambos es mas grande que 1 esto significa
                //que desde la ultima vez que se entro ham pasado mas de 1 ms
                timeB1 = micros;
                PORTD++;
            }
        }
        // misma logica que antes
        if((portbAnterior & 2) == 0  &&  (portbActual & 2) == 2){
            if(micros - timeB2 >= 50){
                timeB2 = micros;
                PORTD--;
            }
        }
        
        INTCONbits.RBIF = 0;
    }
    
     if (PIR1bits.TMR2IF){
        PIR1bits.TMR2IF = 0; 
        micros+= 50; // emtra aqui cada 50 uS
    }
    
    isrADC();
    isrTimer0();
    return;
}
