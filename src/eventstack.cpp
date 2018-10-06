#include "include/eventstack.h"

EventStack::EventStack() :
    event_stack()
{
    // nothing
}


// project comparator
struct ProjectComparator
{
    inline bool operator() (Project p1, Project p2)
    {
        return p1.get_deadline() > p2.get_deadline();
    }
};

void EventStack::build_event_stack(std::vector<Project>& project_list)
{
    // sorting the list
    std::sort(project_list.begin(), project_list.end(), ProjectComparator());

    // iterating through the sorted list and filling the stack
    for (Project pro: project_list)
    {
        std::cout << "pushing " << pro.get_name() << std::endl;
        event_stack.push(Event(pro, pro.get_deadline()));
    }

    // debug
    while (!event_stack.empty())
    {
        Event e = event_stack.top();
        std::cout << "Project : " << e.proj.get_name() << " with deadline "
                  << e.date.year() << "-" << e.date.month() << "-" << e.date.day() << std::endl;
        event_stack.pop();
    }
}
