#include <iostream>

#include "../include/project.h"
#include "../lib/cpptoml.h"

using namespace std;

Date::Date(int year, int month, int day): year(year), month(month), day(day)
{

}

int Date::get_year()
{
    return this->year;
}

int Date::get_month()
{
    return this->month;
}

int Date::get_day()
{
    return this->day;
}

Project::Project(): name("Unnamed project"), dev_time(0), managing_time(0), deadline(Date(0, 0, 0))
{

}

Project::Project(string name, int dev_time, int managing_time, int deadline_year, int deadline_month, int deadline_day): name(name), dev_time(dev_time), managing_time(managing_time), deadline(Date(deadline_year, deadline_month, deadline_day))
{
    if(dev_time < 0)
        dev_time = 0;
    if(managing_time < 0)
        managing_time = 0;
}

Project::Project(string name): name(name), dev_time(0), managing_time(0), deadline(Date(0, 0, 0))
{

}

std::string Project::get_name()
{
    return this->name;
}

int Project::get_dev_time()
{
    return this->dev_time;
}

int Project::get_managing_time()
{
    return this->managing_time;
}


Date Project::get_deadline()
{
    return this->deadline;
}
