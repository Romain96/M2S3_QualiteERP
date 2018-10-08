#include "include/event.h"
#include <iostream>

Event::Event()
{
    // nothing
}

/*
 * Ctrating an event of type project
 */
Event::Event(Project pro, QDate date) :
    date(date),
    is_proj(true),
    proj(pro),
    employee()
{
    // nothing
    std::cerr << "PROJECT" << std::endl;
}

/*
 * Creating an event of type employee
 */
Event::Event(std::pair<std::string,std::pair<int,QDate>> employee, QDate date) :
    date(date),
    is_proj(false),
    proj(),
    employee(employee)
{
    // nothing
    std::cerr << "EMPLOYEE" << std::endl;
}
