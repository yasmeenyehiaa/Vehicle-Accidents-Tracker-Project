#include "DistractedDrivingAccident.h"

DistractedDrivingAccident::DistractedDrivingAccident()
{
    accident_type = "Distracted";
    DistractedDriving_count++;
}
int DistractedDrivingAccident::DistractedDriving_count = 0;
// getter
string DistractedDrivingAccident::get_accident_type()
{
    return accident_type;
}


