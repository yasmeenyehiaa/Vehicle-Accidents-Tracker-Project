using namespace std;
#include <string>
#include "Accident.h"

class SafetyRelatedAccident: public Accident
{
private:
    string accident_type;
public:
    static int SafetyRelatedDriving_count;
    SafetyRelatedAccident();
    string get_accident_type();
};


