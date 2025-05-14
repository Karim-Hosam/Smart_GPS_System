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
void UART0_StringTX_withLen(char *str, int x);
void UART0_StringRX(char *str, char stopCh);

// UART1
void UART1_Init (void);
char UART1_CharRX(void);
void UART1_CharTX(unsigned char ch);
void UART1_StringTX(char *str);
void UART1_StringRX(char *str, char stopCh);

// UART2
void UART2_Init (void);
char UART2_CharRX(void);
void UART2_CharTX(unsigned char ch);
void UART2_StringTX(char *str);
void UART2_StringRX(char *str, char stopCh);


#endif /* UART_H_ */
