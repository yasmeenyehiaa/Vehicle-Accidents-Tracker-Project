#pragma once
using namespace std;
#include <string>
struct Date
{
    int day, month, year;
};
class Driver
{
private:
    string name;
    string gender;
    int age;
    Date issue_date;
public:
    // constructors
    Driver();
    // setter functions
    void set_name(string n);
    void set_gender(string g);
    void set_age(int a);
    void set_issue_date(Date i);
    // getter functions
    string get_name();
    string get_gender();
    int get_age();
    Date get_issue_date();
};
