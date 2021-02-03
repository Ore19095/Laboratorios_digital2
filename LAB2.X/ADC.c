/*
 * File:   newmain.c
 * Author: Angel Orellana
 *
 * Created on 1 de febrero de 2021, 05:37 PM
 */

#include "ADC.h"
#include <stdint.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000 //valor por defecto
#endif


#ifndef ADC_CHANELS
#define ADC_CHANELS 12 // canales que se van a usar del adc 
#endif

uint8_t ADC_VALUE[ADC_CHANELS]; //puntero que tendra el valor del ADC


void initADC(){
    // dependiendo del valodr de XTAL se colocara un valor u otro en la 
    // frecuencia del oscildor
    
    #if _XTAL_FREQ <= 1000000
    ADCON0bits.ADCS = 0;
    #elif _XTAL_FREQ <= 4000000
    ADCON0bits.ADCS = 1;
    #else
    ADCON0bits.ADCS = 2;
    #endif
    
    PIE1bits.ADIE = 1; // interrupcion activada
    
    ADCON1bits.ADFM = 0; // justificado a la izquierda
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.VCFG0 = 0; // referencias en la alimentacion
    ADCON0bits.ADON = 1; // se enciende
    return;
}

uint8_t* readADC(uint8_t pin){
    if (ADCON0bits.GO ==0 ){
         ADCON0bits.CHS = pin;
        __delay_us(3);
        ADCON0bits.GO = 1; // inicia la conversion
    }
    return &ADC_VALUE[pin]; // retorna el valor para tener acceso al valor
}
// para evitar conflictos de vectores de interrupcion llame a esta funcion
// dentro de la funcion de interrupcion
void isrADC(){
    if(PIR1bits.ADIF == 1){
        ADC_VALUE[ADCON0bits.CHS] = ADRESH;
        PIR1bits.ADIF = 0;
    }
    return;
}


