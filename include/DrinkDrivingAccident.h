#include "Accident.h"
using namespace std;
#include <string>

class DrinkDrivingAccident: public Accident
{
private:
    string accident_type;
public:
    static int DrinkDriving_count;
    DrinkDrivingAccident();
    string get_accident_type();
};
