#include "Reactor/Reactor.h"

void Reactor::RegisterHandler(EventHandler* handler)
{
    handlers.push_back(handler);
}

void Reactor::RemoveHandler(EventHandler* handler)
{
    handler->HandleClose();
    handlers.remove(handler);
    delete handler;
}

void Reactor::RegisterHandler(EventHandler* handler, unsigned int timeout)
{
    handler->SetType(EventHandler::EVENT_HANDLER_TIMER);
    handler->SetTimerTimeout(timeout);
    handler->SetTimerResetTime(GetTickCount64() + timeout);
    handlers.push_back(handler);
}
