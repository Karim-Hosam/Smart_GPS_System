#ifndef UART_H_

#include "../../../Services - Utilities/TM4C123.h"
#include <stdint.h>


#define TXFULL 0x00000020  // fifo is full ?
#define RXEMPTY 0x00000010 // fifo is not empty?
#define clock 16000000

// UART0
void UART0_Init(void);
char UART0_CharRX(void);
void UART0_CharTX(unsigned char ch);
void UART0_StringTX(char *str);
void UART0_StringRX(char *str, char stopCh);


#endif /* UART_H_ */
