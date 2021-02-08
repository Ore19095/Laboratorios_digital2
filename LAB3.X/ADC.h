

/* 
 * File:   
 * Author: Angel Orellana 
 * Comments:
 * Revision history: primera version para pic 16F887
 
 * 
 * Cuando se desee utilizar esta libreria se debera de definir la cantidad
 * de canales de ADC que posea el pic, ademas de esto es recomendable definir
 * el valor de _XTAL_FREQ y colocar el valor que se utilizara debido a que 
 * en base a esa definicion se definira el valor de frecuencia que recibira 
 * el ADC
 * 
 * initADC()
 *  Esta funcion inicializa el adc asi como la interrupcion respectiva, no 
 * requiere parametros
 * 
 * readADC()
 *  el parametro pin es el que determina el canal que sera leido en el adc
 * este valor se coloca directamente en los bits CHS y retorna un puntero a la 
 * direccion de memoria en la cual se colocara el valor una vez se haya
 * completado la lectura, ademas para que se de la lectura, se debe de 
 * configurar el pin como una entrada analogica 
 * 
 
 * isrADC()
 * esta funcion debe ser colocada en el vector de interrupcion correcpondiente
 * en el adc, no se especifica directamente para evitar errores. 
 */

#ifndef ADC_H 
#define	ADC_H 

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
void initADC(void);
uint8_t* readADC(uint8_t pin );
void isrADC(void);

#endif	/* XC_HEADER_TEMPLATE_H */

