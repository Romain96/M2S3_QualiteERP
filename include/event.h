#ifndef EVENT_H
#define EVENT_H

#include <QDate>
#include <include/project.h>

class Event
{
    // TODO add project//employee disambiguation
    // for now only projects

public:
    QDate date;
    Project proj;

    Event();
    Event(Project pro, QDate date);
};

#endif // EVENT_H
