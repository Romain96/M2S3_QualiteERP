#ifndef EVENTSTACK_H
#define EVENTSTACK_H

#include <iostream>
#include <stack>
#include <vector>
#include "include/event.h"

/*
 * EventStack class holds a list of Events
 * each event is either a project deadline or a new employee comming
 * Events are stacked in a closest event (date) on top
 */
class EventStack
{
public:
    std::stack<Event,std::vector<Event>> event_stack;

    // ctor
    EventStack();

    // construct stack from list of projects
    void build_event_stack(std::vector<Project>& project_list);
};

#endif // EVENTSTACK_H
