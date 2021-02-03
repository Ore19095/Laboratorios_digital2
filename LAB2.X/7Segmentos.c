/*
 * File:   7Segmentos.c
 * Author: Angel Orellana
 *
 * Created on 2 de febrero de 2021, 03:28 PM
 */

#include "7Segmentos.h"

#ifndef SEVEN_SEGMENT_SIZE
#define SEVEN_SEGMENT_SIZE 2
#endif

#ifndef FORMAT_DISPLAY
#define FORMAT_DISPLAY hex
#endif

#if FORMAT_DISPLAY == hex

static uint8_t tableDisplay[] = { 0b00111111,//0
                                 0b00000110,//1
                                 0b01011011,//2
                                 0b01001111,//3
                                 0b01100110,//4
                                 0b01101101,//5
                                 0b01111101,//6
                                 0b00000111,//7
                                 0b01111111,//9
                                 0b01101111,//9
                                 0b01110111,//A
                                 0b01111100,//b
                                 0b01011000,//c
                                 0b01011110,//d
                                 0b01111001,//e
                                 0b01110001}; //F


#endif 


__bit* multiplexors[SEVEN_SEGMENT_SIZE]; //arreglo que contiene referencia 
//los pines a usar
uint8_t* displayPort;
uint8_t displayDigits[SEVEN_SEGMENT_SIZE]; // digitos a mostrar

void init7S(uint8_t* port, __bit* pines[]){
    //se debe de pasar por parametro el numero de 7segmentos a usar y el 
    //puerto a
    displayPort = port;
    // se asigan los valores
    for(uint8_t i = 0; i<SEVEN_SEGMENT_SIZE ; i++) {
        multiplexors[i]= pines[i];
    }
    return;
}

void displayValue(uint8_t valor){
    
#if FORMAT_DISPLAY == hex
    #if SEVEN_SEGMENT_SIZE == 2
    
    displayDigits[1] = valor/16;
    displayDigits[0] = valor%16; // se obtienen los digitos en hexadecimal
    
    #endif
#endif
    
}