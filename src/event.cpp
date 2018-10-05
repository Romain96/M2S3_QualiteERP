#include "include/event.h"

Event::Event()
{
    // nothing
}

Event::Event(Project *pro, QDate date) :
    proj(pro),
    date(date)
{
    // nothing
}
