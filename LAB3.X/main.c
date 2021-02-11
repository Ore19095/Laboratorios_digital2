/*
 * File:   main.c
 * Author: Angel Orellana
 *
 * Created on 8 de febrero de 2021, 09:40 AM
 */

#// CONFIG1
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

#include <xc.h>
#include <xc.h>
#include<stdint.h>
#include "LCD8bits.h"
#include "ADC.h"
#include "UART.h"
#define _XTAL_FREQ 4000000
char* analogToString(uint8_t value);
char* intToString(uint8_t value);


int main(){
  TRISD = 0;
  TRISE = 0;
  ANSEL = 3;
  ANSELH = 0;
  LcdInit();
  initADC();
  UARTInit(9600,1);
  volatile char *val;
  volatile char *val2;
  char *contadorString;
  uint8_t *adc1;
  uint8_t *adc2;
  
  uint8_t contador = 0;
  while(1){
      //LcdClear();
      //--------- se leen los valors del adc y se escribe en la lcd
    adc1 = readADC(0);
    //LcdClear();
    LcdSetCursor(1,1); // se deja un momento
    adc2 = readADC(1); //se lee el otro
    LcdWriteString("S1:   S2:   S3:");
    LcdSetCursor(2,1);
    // ---- aqu se imprimen los valors -----------------
    val = analogToString(*adc1);
    LcdWriteString(val);
    LcdWriteString("V ");
    // se envia por uart el valor --
    UARTSendString(val,6);
    UARTSendString("V ",3);
    val2 = analogToString(*adc2);
    LcdWriteString(val2);
    LcdWriteString("V ");
    //-- se enviia de nuevo, puesyo que val y val2 hacen referencia a la misma
    //variable
    UARTSendString(val,6);
    UARTSendString("V \n",3);
    
    
    // se verifica si hay algo en el uart 
    
    if (UARTDataReady()){
        char entrada  = UARTReadChar();
        if( entrada == '+'){
            contador++;
        }
        else if (entrada =='-'){
            contador--;
        }
    }
    
    contadorString = intToString(contador);
    LcdWriteString(contadorString);
   // __delay_ms(1000);
  }
  return 0;
}
// imprimira valroes con 2 decimales de presicion
char* analogToString(uint8_t value){
    float valor =  value *0.019;
    char string[5]; 
    uint8_t entero =  valor;
    
    string[0] = entero + 48;// se imprime el entero
    string[1]= '.'; //punto decimal
    valor =( valor - entero); // se elimina la parte entera y se corre el 
    // punto decimal
    valor*=10;
    entero =  valor  ; // se toma la parte entera
    string[2] = entero + 48;
    
    valor -= entero;
    valor*=10;
    
    entero =  valor  ; // se toma la parte entera
    string[3] = (entero + 48);
    string[4] ='\0';
    return string;
}


char* intToString(uint8_t value){
    char valor[4];
    
    uint8_t entero = value/100; // numeor de centennas 
    valor[0] = entero+48;
    
    value -= 100*entero; // se quitan las decenas
    
    valor[1] = value/10 + 48 ; // decenas
    valor[2] = value%10  + 48;// el resto
    valor[3] = '\0'; //caracter nulo
    
    return valor;
          
    
    
}


void __interrupt() isr(){
    isrADC();
}