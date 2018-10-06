#include "include/event.h"

Event::Event()
{
    // nothing
}

Event::Event(Project pro, QDate date) :
    date(date),
    proj(pro)
{
    // nothing
}
