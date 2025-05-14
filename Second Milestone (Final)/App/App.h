#ifndef APP_H
#define APP_H

#include "../../Services - Utilities/TM4C123.h"
#include "TM4C123.h"
#include "../../Services - Utilities/bit_utilies.h"
#include <stdint.h>
#include "../MCAL/TIMER/TIMER.h"
#include "../MCAL/GPIO/GPIO.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/SYSTICK/SYSTICK.h"
#include "../HAL/GPS/GPS.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/LED_BUZZER/LED_BUZZER.h"
#include "../HAL/SWITCH_BTN/SWITCH_BTN.h"

#define Save_LAT_LOG_BTN (GPIO_PORTE_DATA_R & (1 << 3))
#define SWITCH_STATE_BTN (GPIO_PORTA_DATA_R & (1 << 3))
#define SWITCH_PLACE_BTN (GPIO_PORTA_DATA_R & (1 << 4))
#define RESET_TIMER_BTN (GPIO_PORTF_DATA_R & (1 << 1))
#define DATA_RECIEVED_FROM_GPS_CORRECTLY (Lat_float > 0 && Log_float > 0)

#endif // APP_H

