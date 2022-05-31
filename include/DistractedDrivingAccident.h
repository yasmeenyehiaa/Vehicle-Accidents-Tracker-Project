using namespace std;
#include <Accident.h>
#include <string>

class DistractedDrivingAccident: public Accident
{
private:
    string accident_type;
public:
    static int DistractedDriving_count;
    DistractedDrivingAccident();
    string get_accident_type();
};
