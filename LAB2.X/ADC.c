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

uint8_t* ADC_VALUE; //puntero que tendra el valor del ADC
uint8_t* ADC_PINS;
uint8_t contador = 0;
/**
*@param pines array with number pin that will use
**/
void initADC(uint8_t *pines, uint8_t noPines){
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

    uint8_t valores[noPines];
    ADC_VALUE = valores;

    return;
}

uint8_t* readADC(uint8_t pin){
    int i;
    for (i = 0; i <12; i++ ){
        if(ADC_PINS[i] == pin) break;
    }
    return &ADC_VALUE[i]; // retorna el valor para tener acceso al valor
}
// para evitar conflictos de vectores de interrupcion llame a esta funcion
// dentro de la funcion de interrupcion
void isrADC(){
    if(PIR1bits.ADIF){
        ADC_VALUE[ADCON0bits.CHS] = ADRESH;
        contador++;
        ADCON0bits.CHS = ADC_PINS[contador];
        ADCON0bits.GO = 1; // inicia la conversion
        PIR1bits.ADIF = 0;
    }
    return;
}


