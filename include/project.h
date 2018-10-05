#ifndef PROJECT_H
#define PROJECT_H

#include <string>

#include "lib/cpptoml.h"

class Date{
    public:
        Date();
        Date(int year, int month, int day);

        int get_year();
        int get_month();
        int get_day();

    protected:
        int year, month, day;
};

class Project{
    public:
        Project();
        Project(std::string name, int dev_time, int managing_time, int deadline_year, int deadline_month, int deadline_day);
        Project(std::string name);

        std::string get_name();
        int get_dev_time();
        int get_managing_time();
        Date get_deadline();
    protected:
        std::string name;
        int dev_time;
        int managing_time;
        Date deadline;
};

#endif
