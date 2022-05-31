#include <bits/stdc++.h>
#include "Driver.h"
#include "Vehicle.h"
#include "Accident.h"
#include "VehicleAccidents.h"
#include "DrinkDrivingAccident.h"
#include "SpeedDrivingAccident.h"
#include "SafetyRelatedAccident.h"
#include "DistractedDrivingAccident.h"

using namespace std;

// 4 Main vectors to store all data in
vector<Driver> All_Drivers;
vector<Vehicle> All_Vehicles;
vector<Accident*> All_Accidents;
vector<VehicleAccidents> All_vehicleAccidents;

// Declaring Functions
void Urban_vs_highway();
void MostFrequentType();
Time Time_adjuster(string str);
void TextAnalyzer(string input_line);
string Erase(string s, string chars);
void Data_by_Liscence_date(int year);
double percentage_of_casualities(int age);
vector<string> func_1(string s, char condition);
Date Date_adjuster(string str, char condition);
void print_accident_data(VehicleAccidents obj);
bool is_already_there(string t_country, vector <Accident*> t_accidents, vector <Vehicle> t_vehicles);

//Exception Class -> to check double exceptions in accidents
class Duplicate_Exception: public exception
{
  virtual const char* what() const throw()
  {
    return "A Duplicate Accident is Caught!"; // Error message in case on duplicates
  }
} myex;

// Testing class -> to test the application using functions (unit tests) that executes
// different scenarios with an expected output that I prepared.
class Testing
{
public:
    // Testing the validity of the input date
    void TestDateValidity(string d_name, int d_age, string d_gender, int d_year, int d_month, int d_day)
    {
        try
        {
            Driver d;
            Date d_date;
            d_date.day = d_day;
            d_date.year = d_year;
            d_date.month = d_month;
            d.set_issue_date(d_date);
            d.set_name(d_name);
            d.set_age(d_age);
            d.set_gender(d_gender);
        }
        catch(const char* msg){ cout << "Error! "  << msg; }
    }
    // Testing the validity of date and time for the input Accident
    void TestTimeValidity( int hour, int minute)
    {
        try
        {
            Accident *obj;
            Time t;
            t.hour = hour; t.minute = minute;
            obj->set_accident_time(t);
        }
        catch(const char* msg){ cout << "Error! "  << msg; }
    }
};

int main()
{
    int option;
    cout << "\t\t\t*****************Welcome to Accident Tracking system******************\n";
    cout << "\t\t\t**************Choose an option from the list of options***************\n";


    // loading data from file
    fstream Data;
    Data.open("Data.txt",ios::in); //open a file in read mode
    if (Data)
    {
      string input_line;
      while(getline(Data, input_line))
      {
        TextAnalyzer(input_line); // processing each line to be converted into an object of type Vehicle Accident
      }
      Data.close();
    }
    cout << "\t\t\t********************* Data loaded successfully ***********************\n";


    goto Home_screen;
    // Display all operations and let the user choose an option
    Home_screen:
    {
        cout << endl;
        cout << "\t\t\t 1 -> Unit Testing.\n";
        cout << "\t\t\t 2 -> Display Most Frequent accident category.\n";
        cout << "\t\t\t 3 -> Find percentage of casualties in accidents involving drivers over a certain age.\n";
        cout << "\t\t\t 4 -> Compare number of accidents in urban areas to those that occur in highways.\n";
        cout << "\t\t\t 5 -> Display details for accidents having driver's license issued after a certain year.\n";
        cout << "\t\t\t 6 -> Display all the vehicle accidents data.\n";
        cout << "\t\t\t 7 -> Save accidents report in a tabular format.\n";
        cout << "\t\t\t 8 -> Exit program.\n" << endl;
        cout << "\t\t\tEnter your choice:\t";
        cin >> option;
        cout << endl;

        switch(option)
        {
            case 1:
                Testing unit_test;
                unit_test.TestDateValidity("Yasmeen",20,"Female",2050,10,1);
                unit_test.TestTimeValidity(90,2);
                goto Home_screen;

            case 2:
                MostFrequentType(); // Finding the most frequent accident category
                goto Home_screen;   // Move to home screen again

            case 3:
                // Finding percentage of causalities in accidents involving drivers over age 60
                cout << "\n\nPercentage of causalities in accidents involving drivers over age 60 is "
                     << percentage_of_casualities(60) << "%\n";
                goto Home_screen;

            case 4:
                Urban_vs_highway(); // Comparing accidents in urban areas vs in highways
                goto Home_screen;

            case 5:
                // Display accident details for the drivers involved in accidents having driver's license issued after 2019.
                cout << "\n\n--- Accidents data for drivers with licenses issued after 2019 ---\n\n";
                cout << "Country:\n|Category\tLocation\tTime\t Date\t Casualties\t[Vehicles Data]| \n\n";
                Data_by_Liscence_date(2019);
                goto Home_screen;

            case 6:
                // Displaying all vehicle accidents data.
                cout << "\n\n--- All Accidents data ---\n\n";
                cout << "Country:\n|Category\tLocation\tTime\t Date\t Casualties\t[Vehicles Data]| \n\n";
                for (VehicleAccidents v_a : All_vehicleAccidents)
                {
                    print_accident_data(v_a);
                    cout << endl;
                }
                goto Home_screen;

            case 7:
                 // Saving all vehicle accidents data in a file in tabular form
                for (VehicleAccidents v_a : All_vehicleAccidents)
                {
                    v_a.print_TabularForm();
                }
                cout << "Data saved in " << "AccidentsReport(Tabular_Form).txt" << " in tabular form\n\n";
                goto Home_screen;
            case 8:
                cout << "Exiting program...\n";
                exit(1);
        }
    }
    return 0;
}

/******** Functions Definition: **************/

/* This function takes an input string-line from file (each line represents a separate Accident Vehicle object),
and analyze this line, check whether the object already exists or not,
Then -> separates the string to fill the 4 main vectors with the data of the object, and finally creates it */
void TextAnalyzer(string input_line)
{
        VehicleAccidents obj;  Accident *obj1; Driver obj3; Vehicle obj2;
        // creating temporary vectors to store data in
        vector<string> country_then_accidents = func_1(input_line,';');
        vector<Accident*> TrueAccidents; vector<Vehicle> TrueVehicles; vector<Driver> TrueDrivers;
        // Tracking data for the Vehicle accident object
        string country = country_then_accidents[0];
        obj.set_country(country);
        // Track whole data for an accident
        for(int i=1; i< country_then_accidents.size(); i++)
        {
            string temp = country_then_accidents[i];
            temp = Erase(temp,"{}"); // removing unnecessary chars

            vector<string> accident_data = func_1(temp,' ');
            if(accident_data[0] == "Drink") // Determining accident type
            {
                obj1 = new DrinkDrivingAccident();
            }
            else if(accident_data[0] == "Distracted")
            {
                obj1 = new DistractedDrivingAccident();
            }
            else if(accident_data[0] == "Speed")
            {
                obj1 = new SpeedDrivingAccident();
            }
            else if(accident_data[0] == "SafetyRelated")
            {
                obj1 = new SafetyRelatedAccident();
            }
            else cout << "\nAccident type is not Defined!!\n";
            obj1->set_location(accident_data[1]);
            Time t0 = Time_adjuster(accident_data[2]);
            obj1->set_accident_time(t0);
            Date d0 = Date_adjuster(accident_data[3],'/');
            obj1->set_accident_date(d0);
            obj1->set_casualities(stoi(accident_data[5]));
            string temp_vehicle_data = accident_data[4];
            vector<string> vehicles_data = func_1(temp_vehicle_data,'#');

            // track whole data for a vehicle
            for (string j : vehicles_data)
            {
                j = Erase(j,"[]");
                string Vehicle_driver = j;
                vector<string> Vehicle_info = func_1(Vehicle_driver,'_');

                obj3.set_name(Vehicle_info[1]);
                obj3.set_age(stoi(Vehicle_info[2]));
                obj3.set_gender(Vehicle_info[3]);
                Date d1 = Date_adjuster(Vehicle_info[4],'-');
                obj3.set_issue_date(d1);
                obj2.set_license_number(stoi(Vehicle_info[0]));
                obj2.set_driver(obj3);
                // pushing the vehicles and drivers' data to temporary vectors
                TrueDrivers.push_back(obj3);
                TrueVehicles.push_back(obj2);
            }
            obj1->set_vehicles(TrueVehicles);
        } /*finished creating an accident object*/

        //creating a Vehicle accident object
        TrueAccidents.push_back(obj1);
        obj.set_accidents(TrueAccidents);

        try //checking whether the object already exists in the data (Duplicates)
        {
            //is_already_there() -> is a function that check duplicates by looping through the data set, and returns true if the object exists
            bool is_there = is_already_there(country , TrueAccidents , TrueVehicles);
            if( is_there == false )
            {
                // case of no duplicates -> push the object data to the 4 main vectors
                All_vehicleAccidents.push_back(obj);
                All_Accidents.push_back(obj1);
                for (Vehicle tmp_v: TrueVehicles)
                {
                    All_Vehicles.push_back(tmp_v);
                }
                for(Driver tmp_d: TrueDrivers)
                {
                    All_Drivers.push_back(tmp_d);
                }
            }
            else
            {
                throw myex; // Case of duplicates
            }
        }
        catch (exception& e)
        {
            cout << "Error: " << e.what() << '\n'; //Error message
        }
}

// Erase() function -> takes a string and removes the specified characters from it, and returns the string (after removing chars) again.
string Erase(string s, string chars)
{
    for(char c : chars)
        s.erase(remove(s.begin(), s.end(),c), s.end());
    return s;
}

// Func_1() function -> takes an input string and a condition, and splits the string at this condition
// and returns the splited strings in a vector
vector<string> func_1(string s, char condition)
{
    vector<string> vec;
    stringstream check(s);
    string token;
    // Tokenizing
    while(getline(check, token, condition))
        vec.push_back(token);
    return vec;
}
// Time_adjuster() -> takes an input string and split it to form a Time object and returns it.
Time Time_adjuster(string str)
{
    Time t; // creating Time object to be returned
    vector<string> v = func_1(str,':'); // splitting data
    t.hour = stoi(v[0]);
    t.minute = stoi(v[1]);
    return t;
}
// Date_adjuster() -> takes an input string and split it to form a Date object and returns it.
Date Date_adjuster(string str, char condition)
{
    Date d; // creating date object to be reurned
    vector<string> v = func_1(str,condition); // splitting data
    d.day = stoi(v[0]);
    d.month = stoi(v[1]);
    d.year = stoi(v[2]);
    return d;
}
// MostFrequentType() -> compares the number of accidents from each category to check the the most frequent accident category
void MostFrequentType()
{
    int num1 = DrinkDrivingAccident::DrinkDriving_count;
    int num2 = DistractedDrivingAccident::DistractedDriving_count;
    int num3 = SpeedDrivingAccident::SpeedDriving_count;
    int num4 = SafetyRelatedAccident::SafetyRelatedDriving_count;
    if (num1 > num2 && num1 > num3 && num1 > num4)
        cout << "\n\nThe most frequent accident type is Drink Driving.\n\n";
    else if(num2 > num1 && num2 > num3 && num2 > num4)
        cout << "\n\nThe most frequent accident type is Distracted Driving.\n\n";
    else if (num3 > num1 && num3 > num2 && num3 > num4)
        cout << "\n\nThe most frequent accident type is Speed Driving.\n\n";
    else
        cout << "\n\nThe most frequent accident type is Safety-Related Driving.\n\n";
}
// Urban_vs_highway() -> compares the number of accidents that occur in urban and highways and prints the relation between them ( > / = / <)
void Urban_vs_highway()
{
    // counting  the number of accidents in both areas
    int c_urban = 0, c_highway = 0;
    for (Accident *i: All_Accidents)
    {
        if(i->get_location() == "Urban" || i->get_location() == "urban")
            c_urban++;
        else
            c_highway++;
    }
    if(c_urban == c_highway)
        cout << "\n\nNumber of accidents in Urban areas *is equal to* those that occur in Highways.\n";
    else if(c_urban > c_highway)
        cout << "\n\nNumber of accidents in Urban areas *is more than* those that occur in Highways.\n";
    else
        cout << "\n\nNumber of accidents in Urban areas *is less than* those that occur in Highways.\n";
    cout << "Number of accidents in Urban areas = " << c_urban << "   and those that occur in Highways = " << c_highway << endl;
}

// percentage_of_casualities() -> Returns the percentage of causalities in accidents involving drivers over the given age.
double percentage_of_casualities(int age)
{
    double sum = 0, ctr = 0;
    for(Accident *obj : All_Accidents)
    {
        sum += obj->get_casualities();
        vector<Vehicle> obj_vehicles = obj->get_vehicles();
        for(Vehicle v : obj_vehicles)
        {
            if (v.get_driver().get_age() > age)
            {
                ctr += obj->get_casualities();
                break;
            }
        }
     }
    return (ctr / sum) * 100;
}

//Display the country name and accidents list which shows the accident details for the
//drivers involved in accidents having driver's license issued after the specified year.
void Data_by_Liscence_date(int input_year)
{
    try
    {
        // checking the input date
        if(input_year > 2020)
            throw "Exception caught: Invalid issue year!!\n";
        // looping through the object data to check if the driver's license was issued after the specified year
        for(VehicleAccidents obj: All_vehicleAccidents)
        {
            bool printed = false; // to prevent data from being printed twice
            vector<Accident*> obj_accidents = obj.get_accidents();
            // checking all object's accidents
            for(Accident *a : obj_accidents)
            {
                vector<Vehicle> obj_vehicles = a->get_vehicles();
                for(Vehicle v : obj_vehicles)
                {
                    Driver d = v.get_driver();
                    if ((d.get_issue_date().year) > input_year) // checking the driver's license issue date
                    {
                        print_accident_data(obj); // printing accident data
                        printed = true;
                        break;
                    }
                }
                if(printed == true) break;
            }
        }
    }
    catch(const char* msg){ cout << "Error! "  << msg; }

}

// print_accident_data() -> Takes a Vehicle Accident object and prints its data
void print_accident_data(VehicleAccidents obj)
{
    cout << obj.get_country() << ":\t\n|";
    vector<Accident*> obj_accidents = obj.get_accidents();
    for(Accident *a : obj_accidents)
    {
        vector<Vehicle> obj_vehicles = a->get_vehicles();
        int tmp_v = obj_vehicles.size(); // Determining number of Vehicles included in each accident
        for(Accident *acc: obj_accidents)
        {
            // Printing data for each accident
            cout << acc->get_accident_type()      << "\t" << acc->get_location()             << "\t"
                 << setfill('0') << setw(2) << acc->get_accident_time().hour << ":" << setfill('0')
                 << setw(2) << acc->get_accident_time().minute << "\t";
            cout << acc->get_accident_date().day  << "/"  <<  acc->get_accident_date().month << "/"
                 << acc->get_accident_date().year << "\t" << acc->get_casualities()          <<"\t" ;
            for(int i=0; i<tmp_v; i++) // printing data for each vehicle
            {
                cout << "[ " << obj_vehicles[i].get_lincense_number()
                     << "\t" << obj_vehicles[i].get_driver().get_name()
                     << "\t" << obj_vehicles[i].get_driver().get_gender()
                     << "\t" << obj_vehicles[i].get_driver().get_age()
                     << "\t" << obj_vehicles[i].get_driver().get_issue_date().year  << " ] " ;
            }   cout << "|  ";
        }
    } cout << endl;
}

// is_already_there() -> A function to check if the given object exists in the data (Duplicates!!!!)
bool is_already_there(string t_country, vector <Accident*> t_accidents, vector <Vehicle> t_vehicles)
{
    if(All_vehicleAccidents.size() == 0) // Case: No previous data
    {
        return false;
    }
    bool flag = true; // Assuming the object already exists in the data
    for(VehicleAccidents obj : All_vehicleAccidents)
    {
        if(obj.get_country() == t_country) // comparing countries
        {
            vector<Accident*> obj_accidents = obj.get_accidents();
            for(Accident *t_acc : t_accidents)
            {
                for(Accident *acc : obj_accidents)
                {
                    // comparing : accident type & accident location & accident time & date -> casualties for both accidents
                    if((t_acc->get_accident_type() == acc->get_accident_type()) &&
                       (t_acc->get_location() == acc->get_location()) &&
                       (t_acc->get_casualities() == acc->get_casualities()) &&
                       (t_acc->get_accident_date().day == acc->get_accident_date().day) &&
                       (t_acc->get_accident_date().month == acc->get_accident_date().month) &&
                       (t_acc->get_accident_date().year == acc->get_accident_date().year) &&
                       (t_acc->get_accident_time().minute == acc->get_accident_time().minute) &&
                       (t_acc->get_accident_time().hour == acc->get_accident_time().hour))
                       {
                           vector<Vehicle> obj_vehicles = acc->get_vehicles();
                           for(Vehicle t_vcl : t_vehicles)
                           {
                               for(Vehicle obj_vcl : obj_vehicles)
                               {
                                   // comparing vehicle's license number >> since each vehicle has a unique one
                                   if(t_vcl.get_lincense_number() == obj_vcl.get_lincense_number())
                                   {
                                       continue; // case : data already present ->> flag = true
                                   }
                                   else
                                   {
                                       flag = false; // case : data is not present ->> flag = false and break from all loops
                                       break;
                                   }
                               }
                               if (flag == false) break;
                           }
                       }
                       else
                       {
                           flag = false; break;
                       }
                }
                if (flag == false) break;

            }
            if (flag == false) break;
        }
        else
        {
            flag = false;  break;
        }
    }
    if(flag == false) // No duplicates
        return false;
    else  // Duplicates!
        return true;
}
