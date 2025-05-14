#include "GPS.h"

const int Places_Quantity = 6;

// char receive[] = "$GPGSV,4,4,13,08,09,245,*49 $GPRMC,121432.000,A,3003.8672,N,3116.8205,E,0.26,55.91,121017,,,A*58 $GPVTG,55.91,T,,M,0.26,N,0.49,K,A*0C $GPGGA,121431.000,1832.9618,N,07347.1183,E,1,8,1.02,611.1,M,-64.6,M,,*78 $GPGLL,1832.9618,N,07347.4183,E,121433.000,A,A*58 $GPGSA,A,3,14,18,19,32,11,26,31,,,,,1.34,1.02,0.87*39 $GPGSV,4,1,13,01,32,180,17,08,14,47,358,38,10,45,086,36,32,39,020,28*72";
// to be removed later 
float Coordinate_fixed_places[Places_Quantity][2] = {
    {3003.8531, 3116.8222}, // Hall A & B
    {3003.8219, 3116.8358}, // Hall C & D
    {3003.8076, 3116.6998}, // Credit
    {3003.8904, 3116.7280}, // Main Building
    {3003.7884, 3116.7706},  // Luban
	{3003.8119, 3116.3864}   // Metro
};

// ----------------------------------------------

// GPS Read Function

// ----------------------------------------------

bool is_match(char *logName_buffer, char i)
{
    return (logName_buffer[(i + 1) % 6] == '$' &&
            logName_buffer[(i + 2) % 6] == 'G' &&
            logName_buffer[(i + 3) % 6] == 'P' &&
            logName_buffer[(i + 4) % 6] == 'R' &&
            logName_buffer[(i + 5) % 6] == 'M' &&
            logName_buffer[i % 6] == 'C');
}

void readGPS(char *Lat, char *Log)
{
    char logName_buffer[7] = {0};
    bool capture = false;
    bool success_Flag = false;
    char comma_counter = 0;
    char lat_and_log_index = 0;
    char GPS_Char_index = 0;
		volatile int i;

    while (1)
    {
        //$GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C

        char c = UART2_CharRX(); // receive[GPS_Char_index]; (Uncomment this line to use UART for receiving data)

        logName_buffer[GPS_Char_index % 6] = c;

        if (c == 'C' && is_match(logName_buffer, GPS_Char_index % 6))
        {
            capture = true;
        }

        if (capture)
        {
            if (c == '*')
            {
                capture = false;
                break;
            }
            else if (c == 'A' && success_Flag == false)
            {
                success_Flag = true;
            }
            else if (success_Flag == true)
            {
                if (c == ',')
                {
                    comma_counter++;
                    lat_and_log_index = 1;
                }
                else if (comma_counter == 1)
                {
                    Lat[lat_and_log_index] = c;
                    lat_and_log_index++;
                }
                else if (comma_counter == 2)
                {
                    Lat[0]=(c=='N'?'+':'-');
                }
                else if (comma_counter == 3)
                {
                    // if(c >= '0' && c <= '9' ){
                        Log[lat_and_log_index] = c;
                        lat_and_log_index++;
                    // }
                }
                else if (comma_counter == 4)
                {
                    Log[0]=(c=='E'?'+':'-');
                }
                else if (comma_counter > 4)
                {
                    capture = false;
                    break;
                }
            }
        }
        GPS_Char_index++;
    }
}

// ----------------------------------------------

// Harvesine law to Get Distance between 2 points

// ----------------------------------------------

float ToDegree(float angle)
{
    int degree = (int)(angle / 100);
    float minutes = angle - (float)degree * 100;
    return (degree + (minutes / 60.0));
}

float ToRad(float angle)
{
    return angle * PPI / 180.0;
}

float GPS_getDistance(float FirstPoint_Lat, float FirstPoint_Log, float SecondPoint_Lat, float SecondPoint_Log)
{

    // Get Radian Angle
    float FirstPoint_Log_Rad = ToRad(ToDegree(FirstPoint_Log));
    float FirstPoint_Lat_Rad = ToRad(ToDegree(FirstPoint_Lat));
    float SecondPoint_Log_Rad = ToRad(ToDegree(SecondPoint_Log));
    float SecondPoint_Lat_Rad = ToRad(ToDegree(SecondPoint_Lat));

    // Get Difference
    float longDiff = SecondPoint_Log_Rad - FirstPoint_Log_Rad;
    float latDiff = SecondPoint_Lat_Rad - FirstPoint_Lat_Rad;

    // Calculate Distance
    float a = pow(sin(latDiff / 2), 2) + cos(FirstPoint_Lat_Rad) * cos(SecondPoint_Lat_Rad) * pow(sin(longDiff / 2), 2); // Haversine formula: a=sin2(Ap/2)+ cos p1 [ cos q2 0 sin(AA/2)
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS * c;
}

// ----------------------------------------------

// Nearest Place

// ----------------------------------------------

void GPS_getNearestPlace(float Lat, float Log, float* NearestPlace)
{
    float minDistance = -1;
    char nearestIndex = 0;
		char i;
    for (i = 0; i < Places_Quantity; i++)
    {
        float distance = GPS_getDistance(Lat, Log, Coordinate_fixed_places[i][0], Coordinate_fixed_places[i][1]);
        if (minDistance < 0 || distance < minDistance)
        {
            minDistance = distance;
            nearestIndex = i;
        }
    }
    NearestPlace[0] = nearestIndex;
    NearestPlace[1] = minDistance;
}

float GPS_get_Distance_from_SELECTED_Place(float Lat, float Log, int index)
{
    float distance = GPS_getDistance(Lat, Log, Coordinate_fixed_places[index][0], Coordinate_fixed_places[index][1]);
    return distance;
}

