#include <iostream>

#include "../include/project.h"
#include "../lib/cpptoml.h"

using namespace std;

Project::Project(): name("Unnamed project"), dev_time(0), managing_time(0)
{

}

Project::Project(string name, int dev_time, int managing_time, cpptoml::local_datetime deadline): name(name), dev_time(dev_time), managing_time(managing_time), deadline(deadline)
{
    if(dev_time < 0)
        dev_time = 0;
    if(managing_time < 0)
        managing_time = 0;
}

Project::Project(string name): name(name), dev_time(0), managing_time(0)
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

cpptoml::local_datetime Project::get_deadline()
{
    return this->deadline;
}