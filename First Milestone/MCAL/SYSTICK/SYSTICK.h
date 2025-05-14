#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "../../../Services - Utilities/TM4C123.h"
#include <stdint.h>


#define MAX 0x00FFFFFF      /* MAX value of the Reload Register */
#define MAXSEC 16000000
#define MAX_M_SEC 16000

void wait_ms(uint32_t num);

#endif                        /* SYSTICK_H_ */
