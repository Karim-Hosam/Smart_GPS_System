#ifndef APP_H
#define APP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../../Services - Utilities/TM4C123.h"
#include "TM4C123.h"
#include "../../Services - Utilities/bit_utilies.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/SYSTICK/SYSTICK.h"


#define RED_LED     (1U << 1) // PF1
#define BLUE_LED    (1U << 2) // PF2
#define GREEN_LED   (1U << 3) // PF3

#define SW1         (1U << 4) // PF4
#define SW2         (1U << 0) // PF0


#endif // APP_H