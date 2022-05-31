#include "SpeedDrivingAccident.h"

SpeedDrivingAccident::SpeedDrivingAccident()
{
    accident_type = "Speed";
    SpeedDriving_count++;
}
int SpeedDrivingAccident::SpeedDriving_count = 0;
// getter
string SpeedDrivingAccident::get_accident_type()
{
    return accident_type;
}
