#pragma once

#include <list>

#include "Reactor/EventHandler.h"

class Reactor
{
protected:
    typedef std::list<EventHandler*> HandlerList;
    typedef HandlerList::iterator HandlerList_Itr;

public:
    void RegisterHandler(EventHandler* handler);
    void RegisterHandler(EventHandler* handler, unsigned int timeout);
    void RemoveHandler(EventHandler* handler);

    virtual void HandleEvents() = 0;

protected:
    HandlerList handlers;
};
