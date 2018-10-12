#include "include/recruitement_center.h"
#include <iostream>
#include <vector>

/*
 * Constructor
 */
RecruitementCenter::RecruitementCenter()
{
    // nothing
}

/*
 * Adding an employee
 */
void RecruitementCenter::add_employee(std::string name, int job, QDate date)
{
    employees.push_back(std::make_pair(name,std::make_pair(job,date)));
}

// custom employee comparator (closest date)
struct EmployeeComparator
{
    inline bool operator() (std::pair<std::string,std::pair<int,QDate>> e1,
                            std::pair<std::string,std::pair<int,QDate>> e2)
    {
        return e1.second.second < e2.second.second;
    }
};

/*
 * sorting
 */
void RecruitementCenter::sort()
{
    std::sort(employees.begin(), employees.end(), EmployeeComparator());

    // debug
    for (std::pair<std::string,std::pair<int,QDate>> e: employees)
    {
        std::cerr << "* " << e.first << " : " << e.second.second.toString("yyyy.MM.dd").toStdString() << std::endl;
    }
}
