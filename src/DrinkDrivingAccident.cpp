#include "DrinkDrivingAccident.h"

DrinkDrivingAccident::DrinkDrivingAccident()
{
    accident_type = "Drink";
    DrinkDriving_count++;
}
int DrinkDrivingAccident::DrinkDriving_count = 0;
// getter
string DrinkDrivingAccident::get_accident_type()
{
    return accident_type;
}
