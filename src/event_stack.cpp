#include "include/event_stack.h"

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

/*
 * buildinf a single stack of events from two lists :
 * - a list of projects sorted in a closest deadline fashion
 * - a list of employees being recruited in a closest recruitement date fashion
 */
void EventStack::build_event_stack(std::vector<Project>& project_list,
                                   RecruitementCenter& rc)
{
    // sorting the project list
    std::sort(project_list.begin(), project_list.end(), ProjectComparator());
    // sorting the recruitement list
    rc.sort();

    // iterating through the sorted list and filling the stack
    __build(project_list.begin(), rc.employees.begin(), project_list, rc.employees);
}

/*
 * stack builder
 */
void EventStack::__build(std::vector<Project>::iterator pro_it, std::vector<std::pair<std::string,std::pair<int,QDate>>>::iterator rec_it,
                         std::vector<Project>& project_list, std::vector<std::pair<std::string,std::pair<int,QDate>>>& recruitement_list)
{
    // not empty, empty
    if (!project_list.empty() && recruitement_list.empty())
    {
        while (pro_it != project_list.end())
        {
            event_stack.push(Event((*pro_it), (*pro_it).get_deadline()));
            pro_it++;
        }
    }
    // empty, not empty
    else if (project_list.empty() && !recruitement_list.empty())
    {
        while (rec_it != recruitement_list.end())
        {
            event_stack.push(Event((*rec_it), (*rec_it).second.second));
            rec_it++;
        }
    }
    // general case
    else if (!project_list.empty() && !recruitement_list.empty())
    {
        while (pro_it != project_list.end() || rec_it != recruitement_list.end())
        {
            if (rec_it == recruitement_list.end())
            {
                event_stack.push(Event((*pro_it), (*pro_it).get_deadline()));
                pro_it++;
            }
            // case : end, no end
            else if (pro_it == project_list.end())
            {
                event_stack.push(Event((*rec_it), (*rec_it).second.second));
                rec_it++;
            }
            else
            {
                // general case
                if ((*pro_it).get_deadline() > (*rec_it).second.second)
                {
                    event_stack.push(Event((*pro_it), (*pro_it).get_deadline()));
                    pro_it++;
                }
                else
                {
                    event_stack.push(Event((*rec_it), (*rec_it).second.second));
                    rec_it++;
                }
            }
        }
    }
}
