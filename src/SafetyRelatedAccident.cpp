#include "SafetyRelatedAccident.h"

SafetyRelatedAccident::SafetyRelatedAccident()
{
    accident_type = "SafetyRelated";
    SafetyRelatedDriving_count++;
}
int SafetyRelatedAccident::SafetyRelatedDriving_count = 0;
// getter
string SafetyRelatedAccident::get_accident_type()
{
    return accident_type;
}

