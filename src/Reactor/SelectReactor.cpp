#include "Reactor/SelectReactor.h"

#include <iostream>
#include <cassert>
#include <queue>

#include "Socket/Connector.h"

/* virtual */ void SelectReactor::HandleEvents()
{
    // no job
    if (handlers.empty())
        return;

    FD_ZERO(&readSockets_);
    FD_ZERO(&writeSockets_);
    FD_ZERO(&exceptSockets);
    for (HandlerList_Itr itr = handlers.begin(); itr != handlers.end(); ++itr)
    {
        EventHandler* handler = *itr;
        // only sockets
        if (handler->GetType() != EventHandler::EVENT_HANDLER_SOCKET)
            continue;

        FD_SET(handler->GetFD(), &readSockets_);
        FD_SET(handler->GetFD(), &writeSockets_);
        FD_SET(handler->GetFD(), &exceptSockets);
    }

    std::queue<EventHandler*> removeQueue;
    /*struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 50 * 1000; // 50 ms*/
    int ret = select(0 /* handlers.size() * 3 + 1 */, &readSockets_, &writeSockets_, &exceptSockets, NULL /*&timeout*/);
    if (ret > 0)
    {
        for (HandlerList_Itr itr = handlers.begin(); itr != handlers.end(); ++itr)
        {
            EventHandler* handler = *itr;
            EventHandler::SocketType fd = handler->GetFD();
            if (FD_ISSET(fd, &readSockets_))
            {
                if (!handler->HandleInput())
                {
                    removeQueue.push(handler);
                    continue;
                }
            }
            if (FD_ISSET(fd, &writeSockets_))
            {
                if (!handler->HandleOutput())
                {
                    removeQueue.push(handler);
                    continue;
                }
            }
            // non-blocking connect fail triggers this
            if (FD_ISSET(fd, &exceptSockets))
            {
                handler->HandleClose();
                //assert(false);
            }
        }
    }
    else if (ret == SOCKET_ERROR)
        std::cout << "select error " << WSAGetLastError() << std::endl; // in Windows no errno from sockets

    for (HandlerList_Itr itr = handlers.begin(); itr != handlers.end(); ++itr)
    {
        EventHandler* handler = *itr;
        // only timers
        if (handler->GetType() != EventHandler::EVENT_HANDLER_TIMER)
            continue;

        if (handler->GetTimerResetTime() <= GetTickCount64())
        {
            handler->HandleTimeout();
            removeQueue.push(handler);
        }
    }

    // removes the handlers
    while (!removeQueue.empty())
    {
        EventHandler* handler = removeQueue.front();
        removeQueue.pop();

        RemoveHandler(handler);
    }
}
