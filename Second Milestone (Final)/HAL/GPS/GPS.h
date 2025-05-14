#ifndef GPS_H
#define GPS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../MCAL/UART/UART.h"
#include "../../MCAL/Systick/Systick.h"

// Constants
#define EARTH_RADIUS 6371000.0
#define PPI 3.14159265358979323846

// Function declarations
bool is_match(char *logName_buffer, char i);
void readGPS(char *Lat, char *Log);
float ToDegree(float angle);
float ToRad(float angle);
float GPS_getDistance(float FirstPoint_Lat, float FirstPoint_Log, float SecondPoint_Lat, float SecondPoint_Log);
void GPS_getNearestPlace(float Lat, float Log, float* NearestPlace);
float GPS_get_Distance_from_SELECTED_Place(float Lat, float Log, int index);

// Coordinates of known places
extern const int Places_Quantity;
extern float Coordinate_fixed_places[6][2];

#endif // GPS_H
