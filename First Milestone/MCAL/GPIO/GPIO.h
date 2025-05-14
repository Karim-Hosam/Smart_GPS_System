#ifndef GPIO_H_
#define GPIO_H_

#include "../../../Services - Utilities/TM4C123.h"
#include "../../../Services - Utilities/bit_utilies.h"
#include <stdint.h>

void GPIO_InitPort(uint8_t port);
void GPIO_SetPinValue(uint8_t port, uint8_t pin, uint8_t value );
void GPIO_SetPinDirection(uint8_t port, uint8_t pin, uint8_t direction );
void GPIO_SetPortValue(uint8_t port, uint8_t value);
uint8_t GPIO_GetPinValue(uint8_t port, uint8_t pin);
uint8_t Button_Read(uint8_t portname, uint8_t pinnumber);

#endif
