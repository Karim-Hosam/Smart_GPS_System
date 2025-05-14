#include "Systick.h"

void wait_ms(uint32_t num){
    unsigned long k;
	for(k = 0; k < num; k++){
        NVIC_ST_CTRL_R = 0;
        NVIC_ST_RELOAD_R = MAX_M_SEC-1; //1 msec.
        NVIC_ST_CURRENT_R = 0; //clear current register and COUNTFLAG
        NVIC_ST_CTRL_R = 5; //enable and clock source 101 = 5
        while((NVIC_ST_CTRL_R & 0x10000) == 0){}
	}
}
