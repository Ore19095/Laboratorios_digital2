/**
 * File:   
 * Author: Angel Orellana
 * Comments:
 * Revision history: 
 * 
 * se recomienda definir la constante SEVEN_SEGMENTS_SIZE en donde se indique
 * la cantidad se display de 7 segmentos que se utilizara para la multiplexacion
 * ademas de que solo es posible conectar todos los segmentos de un display a 
 * un unico puerto, donde el bit menos significativo representa el segmento a
 * y el mas significativo representa el punto.
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
void init7S();



#endif	/* XC_HEADER_TEMPLATE_H */

