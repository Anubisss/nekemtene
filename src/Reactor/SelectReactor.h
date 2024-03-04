#pragma once

#include "Reactor/Reactor.h"

#include <Winsock2.h>

class SelectReactor : public Reactor
{
public:
    /* virtual */ void HandleEvents();
        
private:
    fd_set readSockets_;
    fd_set writeSockets_;
    fd_set exceptSockets;
};
