#pragma once
#include "Vehicle.h"
using namespace std;
#include <string>
#include <vector>

struct Time
{
    int minute, hour;
};
class Accident
{
private:
    string location;
    Date accident_date;
    Time accident_time;
    int casualities;
    vector<Vehicle> vehicles;

public:
    Accident();
    // setters
    void set_location(string l);
    void set_accident_date(Date d);
    void set_accident_time(Time t);
    void set_casualities(int c);
    void set_vehicles(vector<Vehicle> v);
    // getters
    string get_location();
    Date get_accident_date();
    Time get_accident_time();
    int get_casualities();
    vector<Vehicle> get_vehicles();
    // Pure virtual functions for the other 4-accident types classes
    virtual string get_accident_type() = 0;
};

