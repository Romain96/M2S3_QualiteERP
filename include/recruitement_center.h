#ifndef RECRUITEMENTCENTER_H
#define RECRUITEMENTCENTER_H

#include <iostream>
#include <vector>
#include <QDate>

/*
 * The Recruitement Center represents the employees being added after the simulation has started
 * they need to be stored somewhere until they can rejoin their collegues on "deadline" day
 */
class RecruitementCenter
{
public:
    std::vector<std::pair<std::string,std::pair<int,QDate>>> employees;

    // ctor
    RecruitementCenter();

    // adding a new recruit
    void add_employee(std::string name, int job, QDate date);

    // sorting
    void sort();
};

#endif // RECRUITEMENTCENTER_H
