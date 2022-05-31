using namespace std;
#include <string>
#include "Accident.h"
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>


class  VehicleAccidents
{
private:
    string country;
    vector <Accident*> accidents;
public:
    VehicleAccidents();
    // setters
    void set_country(string s);
    void set_accidents(vector<Accident*> v);
    // getters
    string get_country();
    vector<Accident*> get_accidents();
    void print_TabularForm();
};

