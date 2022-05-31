#include "Accident.h"

Accident::Accident()
{
}
// setters
void Accident::set_location(string l)
{
    location = l;
}
void Accident::set_accident_date(Date d)
{
     if(d.year > 2021 || d.month > 12 || d.month < 1 || d.day < 1 || d.day > 31)
            throw "Invalid Date for Accident object!!\n";
    else
        accident_date = d;
}
void Accident::set_accident_time(Time t)
{
    if(t.minute > 59 || t.minute < 0 || t.hour > 23 || t.hour < 0)
        throw "Invalid time for Accident object!!\n";
    else
    accident_time = t;
}
void Accident::set_casualities(int c)
{
    casualities = c;
}
void Accident::set_vehicles(vector<Vehicle> v)
{
    vehicles = v;
}
// getters
string Accident::get_location()
{
    return location;
}
Date Accident::get_accident_date()
{
    return accident_date;
}
Time Accident::get_accident_time()
{
    return accident_time;
}
int Accident::get_casualities()
{
    return casualities;
}
vector<Vehicle> Accident::get_vehicles()
{
    return vehicles;
}
