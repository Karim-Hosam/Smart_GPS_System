//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Name: Karim Hosam Ahmed Ali || ID: 2201405 || Department: CSE 
//
//  Name: Ahmed Emad Mohamed Zaghloul || ID: 2201374 || Department: ECE
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "App.h"

char Lat[10] = {0};
char Log[10] = {0};
float NearestPlace[2] = {0};
float Lat_float = 0;
float Log_float = 0;
float SAVED_Lat_float = 3003.8904;
float SAVED_Log_float = 3116.7280;
char Place_Index;
int SELECTED_Index = 0;
float Place_Distance;
char Place_Distance_string[10] = {0};
volatile int i;
int y;
char c;

int main()
{
    UART2_Init();
    UART0_Init();
    LCD_Init();
    GPIO_InitPort('A');
    GPIO_InitPort('F');
    GPIO_InitPort('E');
    GPIO_SetPinDirection('A', 3, 'I');
    GPIO_SetPinDirection('A', 4, 'I');
    GPIO_SetPinDirection('E', 3, 'I');
    GPIO_SetPinDirection('F', 1, 'I');
    // GPIO_PORTB_PUR_R = 0x40;
    wait_ms(500);

    LCD_Command(0x80); // Move cursor to first line
    LCD_String("State 1:        ");

    LCD_Command(0xC0); // Move cursor to first line
    LCD_String("Nearest Place   ");

    wait_ms(2000);
    LCD_Command(0x01); // Clear the LCD
    wait_ms(100);

    while (1)
    {
        readGPS(Lat, Log);
        wait_ms(100);
        // Convert to float
        Lat_float = atof(Lat);
        Log_float = atof(Log);

        if (DATA_RECIEVED_FROM_GPS_CORRECTLY)
        {
            if (RESET_TIMER_BTN != 0)
            {
                Timer_Reset();
            }
            if (!timer_running)
            {
                LCD_Command(0x8B); // Move cursor to first line, 11th position
                LCD_String("      ");
                wait_ms(100);
                Timer0A_Init();
                Timer_Start();
            }
            if ((GPIO_PORTE_DATA_R & (1 << 3)) != 0)
            {
                SAVED_Lat_float = Lat_float;
                SAVED_Log_float = Log_float;
                LCD_Command(0x01);
                wait_ms(100);
                LCD_Command(0xC0);
                LCD_String("Place SAVED  ");
                wait_ms(2000);
                LCD_Command(0x01);
                wait_ms(100);
            }
            if (SWITCH_STATE_BTN != 0)
            {
                Timer_Pause();
                switch_state();
                LCD_Command(0x80);
                switch (state)
                {
                case 0:
                    LCD_String("State 1:        ");

                    LCD_Command(0xC0);
                    LCD_String("Nearest Place   ");
                    break;
                case 1:
                    LCD_String("State 2:        ");

                    LCD_Command(0xC0);
                    LCD_String("SAVED Place     ");
                    break;
                case 2:
                    SELECTED_Index = 0;
                    LCD_String("State 3:        ");

                    LCD_Command(0xC0);
                    LCD_String("Select Manually ");
                    break;
                default:
                    break;
                }
                wait_ms(2000);
                LCD_Command(0x01);
                wait_ms(100);
            }

            switch (state)
            {
            case 0:
                // Get nearest place index and distance
                GPS_getNearestPlace(Lat_float, Log_float, NearestPlace);

                Place_Index = (char)NearestPlace[0];
                Place_Distance = NearestPlace[1]; // Get nearest distance
                break;
            case 1:
                Place_Index = 'S';
                Place_Distance = GPS_getDistance(Lat_float, Log_float, SAVED_Lat_float, SAVED_Log_float);
                break;
            case 2:
                if (SWITCH_PLACE_BTN != 0)
                {
                    SELECTED_Index++;
                    if (SELECTED_Index > Places_Quantity - 1)
                    {
                        SELECTED_Index = 0;
                    }
                    LCD_Command(0x01);
                    wait_ms(100);
                }
                Place_Index = SELECTED_Index;
                Place_Distance = GPS_get_Distance_from_SELECTED_Place(Lat_float, Log_float, SELECTED_Index); // Get nearest distance
                break;
            default:
                break;
            }

            LCD_Command(0x80); // Move cursor to first line
            switch (Place_Index)
            {
            case 0:
                // Hall A & C
                LCD_String("Hall A-B   ");
                break;
            case 1:
                // Hall B & D
                LCD_String("Hall C-D   ");
                break;
            case 2:
                // Credit
                LCD_String("Credit     ");
                break;
            case 3:
                // Main Building
                LCD_String("Main Build.");
                break;
            case 4:
                // Luban
                LCD_String("Luban      ");
                break;
            case 5:
                // New Place
                LCD_String("Metro      ");
                break;
            case 'S':
                // New Place
                LCD_String("SAVED PLACE");
                break;
            default:
                // Invalid index
                LCD_String("Invalid      ");
            }

            sprintf(Place_Distance_string, "%d", (int)Place_Distance);
            Alert_If_Close((int)Place_Distance);

            LCD_Command(0xC0); // Move cursor to second line
            LCD_String("Distance: ");

            LCD_String(Place_Distance_string);

            LCD_String(" m   ");
        }

        else
        {
            // Optional: display waiting message
            LCD_Command(0x80);
            LCD_String("Waiting for GPS ");

            LCD_Command(0xC0);
            LCD_String("Loading.    ");

            wait_ms(300);
            LCD_Command(0xC0);
            LCD_String("Loading..   ");

            wait_ms(300);
            LCD_Command(0xC0);
            LCD_String("Loading...  ");

            wait_ms(100);
        }
        wait_ms(100);
    }

    return 0;
}
