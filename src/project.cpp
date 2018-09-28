#include <iostream>

#include "../include/project.h"
#include "../lib/cpptoml.h"

using namespace std;

Deadline::Deadline(int year, int month, int day): year(year), month(month), day(day)
{

}

int Deadline::get_year()
{
    return this->year;
}

int Deadline::get_month()
{
    return this->month;
}

int Deadline::get_day()
{
    return this->day;
}

Project::Project(): name("Unnamed project"), dev_time(0), managing_time(0), deadline(Deadline(0, 0, 0))
{

}

Project::Project(string name, int dev_time, int managing_time, int deadline_year, int deadline_month, int deadline_day): name(name), dev_time(dev_time), managing_time(managing_time), deadline(Deadline(deadline_year, deadline_month, deadline_day))
{
    if(dev_time < 0)
        dev_time = 0;
    if(managing_time < 0)
        managing_time = 0;
}

Project::Project(string name): name(name), dev_time(0), managing_time(0), deadline(Deadline(0, 0, 0))
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


Deadline Project::get_deadline()
{
    return this->deadline;
}