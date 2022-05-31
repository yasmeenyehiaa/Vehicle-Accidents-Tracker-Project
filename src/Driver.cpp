#include "Driver.h"

Driver::Driver()
{
}
// setter functions
void Driver::set_name(string n)
{
    name = n;
}
void Driver::set_gender(string g)
{
    gender = g;
}
void Driver::set_age(int a)
{
    age = a;
}
void Driver::set_issue_date(Date i)
{
    if(i.year > 2021 || i.month > 12 || i.month < 1 || i.day < 1 || i.day > 31)
            throw "Invalid Date for Driver object!!\n";
    else
    {
        issue_date = i;
    }

}
// getter functions
string Driver::get_name()
{
    return name;
}
string Driver::get_gender()
{
    return gender;
}
int Driver::get_age()
{
    return age;
}
Date Driver::get_issue_date()
{
    return issue_date;
}
