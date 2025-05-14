//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Name: Nour Ahmed Khalaf Ahmed || ID: 22000715 || Department: ECE 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "UART.h"

//////////////// UART0 INITIALIZATION //////////////////

void UART0_Init(void) {
	SYSCTL_RCGCUART_R |= 0x01;                // Enable clock for UART0 (bit 0)
	while ((SYSCTL_PRUART_R & 0x01) == 0) {}  // Wait until UART0 is ready

	SYSCTL_RCGCGPIO_R |= 0x01;                // Enable clock for Port A (bit 0)
	while ((SYSCTL_PRGPIO_R & 0x01) == 0) {}  // Wait until Port A is ready            

	UART0_CTL_R &= ~0x00000001;               // Disable UART
	UART0_IBRD_R = 104;                       // Integer part of baud rate (assuming 16MHz clock for 9600 baud)
	UART0_FBRD_R = 11;                        // Fractional part of baud rate
	UART0_LCRH_R |= 0x00000070;               // 8-bit word length, FIFO enabled
	UART0_CTL_R |= 0x00000301;                // Enable RXE, TXE, and UART

	GPIO_PORTA_AFSEL_R |= 0x03;               // Enable alternate functions on PA0, PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011; // PA0->U0Rx, PA1->U0Tx
	GPIO_PORTA_DEN_R |= 0x03;                 // Digital enable on PA0, PA1
	GPIO_PORTA_AMSEL_R &= ~0x03;              // Disable analog functions on PA0, PA1
}

//////////////// UART0 RECEIVE ONE CHAR //////////////////

char UART0_CharRX(void) {
	while ((UART0_FR_R & RXEMPTY) != 0);       // Wait until RX buffer is not empty
	return (char)(UART0_DR_R & 0xFF);          // Return the received byte
}

//////////////// UART0 TRANSMIT ONE CHAR //////////////////

void UART0_CharTX(unsigned char ch) {
	while ((UART0_FR_R & TXFULL) != 0);        // Wait until TX buffer is not full
	UART0_DR_R = ch;                           // Send character
}

//////////////// UART0 TRANSMIT STRING //////////////////

void UART0_StringTX(char *str) {
	while (*str != '\0') {
		UART0_CharTX(*str);                    // Send current character
		str++;         		// Move to next
	}
}

//////////////// UART0 RECEIVE STRING //////////////////

void UART0_StringRX(char *str, char stopCh) {
	char c = UART0_CharRX();
	while (c != stopCh) {
		*str = c;                              // Store character
		str++;
		c = UART0_CharRX();
	}
	*str = '\0';                               // Null-terminate the string
}
