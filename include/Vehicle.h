#pragma once
using namespace std;
#include "driver.h"
#include <string>

class Vehicle
{
private:
    int license_number; Driver driver;
public:
    Vehicle();
    //setters
    void set_license_number(int n);
    void set_driver(Driver d);
    //getters
    int get_lincense_number();
    Driver get_driver();
};

