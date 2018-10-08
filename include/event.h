#ifndef EVENT_H
#define EVENT_H

#include <QDate>
#include <include/project.h>

class Event
{
public:
    QDate date;
    bool is_proj;

    Project proj;
    std::pair<std::string,std::pair<int,QDate>> employee;

    Event();
    Event(Project pro, QDate date);
    Event(std::pair<std::string,std::pair<int,QDate>> employee, QDate date);
};

#endif // EVENT_H
