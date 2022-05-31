#include "VehicleAccidents.h"

VehicleAccidents:: VehicleAccidents()
{
}
// setters
void VehicleAccidents::set_country(string s)
{
    country = s;
}
void VehicleAccidents::set_accidents(vector <Accident*> v)
{
    accidents = v;
}
// getters
string VehicleAccidents::get_country()
{
    return country;
}
vector<Accident*> VehicleAccidents::get_accidents()
{
    return accidents;
}
// A function to print object data to a file in tabular form
void  VehicleAccidents::print_TabularForm()
{
    ofstream out("AccidentsReport(Tabular_Form).txt", ios::app);
    struct
    {
        int width;
        string header;
    } columns[] = { { 15, "Country" }, { 15, "Category" }, { 15, "Location" }, { 15, "Time" },
                    { 15, "Date" }, {15, "Casualties"}, {15, " [Drivers Data]"}};

    for (auto& col: columns)
    {
        out << left << setfill(' ') << setw(18)  << col.header ;
    }
    out << "\n";
    for (int i=0; i<6; i++) out << setw(18) << setfill('-') << "+";
    for (int i=0; i<3; i++) out << setw(48) << setfill('-') << "+";
    out << "\n";


    out << setfill(' ') << setw(18) << country << "  ";
    for(Accident *acc : accidents)
    {
        out << setfill(' ') << setw(18) << acc->get_accident_type()
            << setfill(' ') << setw(18) << acc->get_location();
        out << setfill('0') << setw(2)
            << acc->get_accident_time().hour << ":" << setfill('0')
            << setw(2) << acc->get_accident_time().minute << setfill(' ') << setw(13) <<" " ;

        out << setw(18) << setfill('0') << setw(2) << acc->get_accident_date().day << "/";
        out << right << setfill('0') << setw(2) << acc->get_accident_date().month << "/"
            << right << setfill('0') << setw(4) << acc->get_accident_date().year << setfill(' ') << setw(10) << " ";
        out << left  << setfill(' ') << setw(18) << acc->get_casualities();
        for(Vehicle vcl: acc->get_vehicles())
        {
            out << "[";
            out << setw(7) << vcl.get_lincense_number() << " "
                << setw(4) << vcl.get_driver().get_name() << " "
                << setw(2) << vcl.get_driver().get_age() << " ";
            out << setw(4) << vcl.get_driver().get_gender() << " ";
            out << right << setfill('0') << setw(2) << vcl.get_driver().get_issue_date().day << "/";
            out << right << setfill('0') << setw(2) << vcl.get_driver().get_issue_date().month << "/"
                << vcl.get_driver().get_issue_date().year << " ]";
        }
        out << "  ";
    }
    out << "\n";
    for (int i=0; i<6; i++) out << setw(18) << setfill('-') << "+";
    for (int i=0; i<3; i++) out << setw(48) << setfill('-') << "+";
    out << "\n\n";
}

