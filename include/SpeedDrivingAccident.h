using namespace std;
#include <string>
#include "Accident.h"

class SpeedDrivingAccident: public Accident
{
private:
    string accident_type;
public:
    SpeedDrivingAccident();
    string get_accident_type();
    static int SpeedDriving_count;
};
