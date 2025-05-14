#include "UART.h"

////////////////////////////////////////////// UART0 INITIALIZATION //////////////////////////////////////////////////////////////////////////////////

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

void UART0_StringTX_withLen(char *str, int x) {
	for (char i = 0; i < x; i++)
	{
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

////////////////////////////////////////////// UART1 INITIALIZATION //////////////////////////////////////////////////////////////////////////////////

void UART1_Init (void) {
	SYSCTL_RCGCUART_R |= 0x02;                // Enable clock for UART1 (bit 1)
	while ((SYSCTL_PRUART_R & 0x02) == 0) {}  // Wait until UART1 is ready

	SYSCTL_RCGCGPIO_R |= 0x02;                // Enable clock for Port B (bit 1)
	while ((SYSCTL_PRGPIO_R & 0x02) == 0) {}  // Wait until Port B is ready            

	UART1_CTL_R &= ~0x00000001;               // Disable UART
	UART1_IBRD_R = 104;                       // Integer part of baud rate
	UART1_FBRD_R = 11;                        // Fractional part of baud rate
	UART1_LCRH_R |= 0x00000070;                // 8-bit word length, FIFO enabled
	UART1_CTL_R |= 0x00000301;                 // Enable RXE, TXE and UART

	GPIO_PORTB_AFSEL_R |= 0x03;               // Enable alt functions on PB0, PB1
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) | 0x00000011; // PB0->U1Rx, PB1->U1Tx
	GPIO_PORTB_DEN_R |= 0x03;                 // Digital enable on PB0, PB1
	GPIO_PORTB_AMSEL_R &= ~0x03;              // Disable analog functions on PB0, PB1
}

//////////////// UART1 RECEIVE ONE CHAR //////////////////

char UART1_CharRX(void) {
	while ((UART1_FR_R & RXEMPTY) != 0);       // Wait until RX buffer is not empty
	return (char)(UART1_DR_R & 0xFF);         // Return the received byte
}

//////////////// UART1 TRANSMIT ONE CHAR //////////////////

void UART1_CharTX(unsigned char ch) {
	while ((UART1_FR_R & TXFULL) != 0);       // Wait until TX buffer is not full
	UART1_DR_R = ch;                          // Send character
}

//////////////// UART1 TRANSMIT STRING //////////////////

void UART1_StringTX(char *str) {
	while (*str != '\0') {
		UART1_CharTX(*str);                   // Send current character
		str++;                                // Move to next
	}
}

//////////////// UART1 RECEIVE STRING //////////////////

void UART1_StringRX(char *str, char stopCh) {
	char c = UART1_CharRX();
	while (c != stopCh) {
		*str = c;                             // Store character
		str++;
		c = UART1_CharRX();
	}
	*str = '\0';                              // Null-terminate the string
}

////////////////////////////////////////////// UART2 INITIALIZATION //////////////////////////////////////////////////////////////////////////////////

void UART2_Init(void) {
    SYSCTL_RCGCUART_R |= 0x04;                // Enable clock for UART2 (bit 2)
    while ((SYSCTL_PRUART_R & 0x04) == 0) {}  // Wait until UART2 is ready

    SYSCTL_RCGCGPIO_R |= 0x08;                // Enable clock for Port D (bit 3)
    while ((SYSCTL_PRGPIO_R & 0x08) == 0) {}  // Wait until Port D is ready

    UART2_CTL_R &= ~0x00000001;               // Disable UART2
    UART2_IBRD_R = 104;                       // Integer part of baud rate (assuming 16 MHz and 9600 bps)
    UART2_FBRD_R = 11;                        // Fractional part of baud rate
    UART2_LCRH_R |= 0x00000070;               // 8-bit word length, FIFO enabled
    UART2_CTL_R |= 0x00000301;                // Enable RXE, TXE and UART

    GPIO_PORTD_AFSEL_R |= 0xC0;               // Enable alt functions on PD6, PD7 (0xC0 = 11000000)
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) | 0x11000000; // PD6->U2Rx, PD7->U2Tx
    GPIO_PORTD_DEN_R |= 0xC0;                 // Digital enable on PD6, PD7
    GPIO_PORTD_AMSEL_R &= ~0xC0;              // Disable analog functions on PD6, PD7
}

///////////////// UART2 RECEIVE ONE CHAR //////////////////

char UART2_CharRX(void) {
	while ((UART2_FR_R & RXEMPTY) != 0);       // Wait until RX buffer is not empty
	return (char)(UART2_DR_R & 0xFF);         // Return the received byte
}

//////////////// UART2 TRANSMIT ONE CHAR //////////////////

void UART2_CharTX(unsigned char ch) {
	while ((UART2_FR_R & TXFULL) != 0);       // Wait until TX buffer is not full
	UART2_DR_R = ch;                          // Send character
}

//////////////// UART2 TRANSMIT STRING //////////////////

void UART2_StringTX(char *str) {
	while (*str != '\0') {
		UART2_CharTX(*str);                   // Send current character
		str++;                                // Move to next
	}
}

//////////////// UART2 RECEIVE STRING //////////////////

void UART2_StringRX(char *str, char stopCh) {
	char c = UART2_CharRX();
	while (c != stopCh) {
		*str = c;                             // Store character
		str++;
		c = UART2_CharRX();
	}
	*str = '\0';                              // Null-terminate the string
}