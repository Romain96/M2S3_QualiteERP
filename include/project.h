#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <QDate>
#include "lib/cpptoml.h"


class Project{
    public:
        Project();
        Project(std::string name, int dev_time, int managing_time, int deadline_year, int deadline_month, int deadline_day);
        Project(std::string name);

        std::string get_name();
        int get_dev_time();
        int get_managing_time();
        QDate get_deadline();
    protected:
        std::string name;
        int dev_time;
        int managing_time;
        QDate deadline;
};

#endif
