#include "TIMER.h"

// Global variables
volatile unsigned int seconds = 0;
volatile unsigned int minutes = 0;
volatile unsigned char timer_running = 0;
char minutes_string[2] = {0};
char seconds_string[2] = {0};

void Timer0A_Init(void)
{
    SYSCTL_RCGCTIMER_R |= 0x01; // Enable Timer0 clock
    while ((SYSCTL_PRTIMER_R & 0x01) == 0)
    {
    } // Wait for it

    TIMER0_CTL_R = 0x00000000;     // Disable Timer0A during setup
    TIMER0_CFG_R = 0x00000000;     // 32-bit timer
    TIMER0_TAMR_R = 0x00000002;    // Periodic mode
    TIMER0_TAILR_R = 16000000 - 1; // 1 second interval (16 MHz)
    TIMER0_TAPR_R = 0;
    TIMER0_ICR_R = 0x00000001; // Clear timeout flag
    TIMER0_IMR_R = 0x00000001; // Enable timeout interrupt

    NVIC_EN0_R |= (1 << 19);    // Enable IRQ 19 (Timer0A)
    TIMER0_CTL_R |= 0x00000001; // Enable Timer0A
    timer_running = 1;
}

void Timer_Start(void)
{
    timer_running = 1;
    TIMER0_CTL_R |= 0x01;
}

void Timer_Pause(void)
{
    timer_running = 0;
    TIMER0_CTL_R &= ~0x01;
}

void Timer_Reset(void)
{   
    // timer_running = 0;
    seconds = 0;
    minutes = 0;
    // wait_ms(1000);
    // timer_running = 1;
}

void TIMER0A_Handler(void)
{
    TIMER0_ICR_R = 0x01; // Clear the interrupt flag

    if (timer_running)
    {
        seconds++;
        if (seconds >= 60)
        {
            seconds = 0;
            minutes++;
        }
        if (minutes >= 100)
        { // ??? ????? ??? 99:59? ???? ??????? ??? 00:00
            minutes = 0;
            seconds = 0;
        }
        sprintf(minutes_string, "%d", minutes);
        sprintf(seconds_string, "%d", seconds);

        LCD_Command(0x8B); // Move cursor to first line, 11th position
        if (minutes < 10)
        {
            LCD_String("0");
        }
        LCD_String(minutes_string);
        LCD_String(":");
        if (seconds < 10)
        {
            LCD_String("0");
        }
        LCD_String(seconds_string);
    }
}
