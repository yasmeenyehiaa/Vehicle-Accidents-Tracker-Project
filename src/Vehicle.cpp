#include "Vehicle.h"

Vehicle::Vehicle()
{

}
//setters
void Vehicle::set_license_number(int n)
{
    license_number = n;
}
void Vehicle:: set_driver(Driver d)
{
    driver = d;
}
//getters
int Vehicle::get_lincense_number()
{
    return license_number;
}
Driver Vehicle::get_driver()
{
    return driver;
}
