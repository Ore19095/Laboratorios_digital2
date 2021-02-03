/**
 * File:   
 * Author: Angel Orellana
 * Comments:
 * Revision history: 
 *  Definiciones:
 * 
 * SEVEN_SEGMENT_SIZE: indica la cantidad de displays se utilizaran por
 * defecto son 2 
 * 
 * CHANEL_n: hacer tantas definiciones como canales sean requeridos segun 
 * el numero de displays a usar. por defecto se tiene CHANEL_0 como RA0 y 
 * CHANEL_1 como RA1.
 *
 * _XTAL_FREQ: por defecto 4000000, se utiliza para poder obtener el valor
 * necesario para obtener una intettupcion del timer 0 cada 1 mss
 * 
 * FORMAT_DISPLAY: por defecto hex, se indica el formanto en el que se quiere
 * desplegar el valor, defirnirlo como dec si se quiere en formato decimal
 * 
 * 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H

#ifndef SEVEN_SEGMENT_SIZE
#define SEVEN_SEGMENT_SIZE 2
#endif

#ifndef FORMAT_DISPLAY
#define FORMAT_DISPLAY hex
#endif

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif


#if _XTAL_FREQ == 4000000
// esto se realiza por si en un futuro se quieren usar otras frecuencias de 
//cristal que la interrupcion siga ocurriendo cada 1ms, 
#define TMR0_PS 1
#define TMR0_INIT_VALUE 6
#endif


#if SEVEN_SEGMENT_SIZE == 2

#ifndef CHANEL_0
    #define CHANEL_0 RA2
#endif

#ifndef CHANEL_1
    #define CHANEL_1 RA3
#endif


#endif



#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
void init7S(uint8_t*);
void displayValue(uint8_t);
void isrTimer0(void);


#endif	/* XC_HEADER_TEMPLATE_H */

