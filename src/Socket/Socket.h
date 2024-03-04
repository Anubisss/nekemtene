#pragma once

#include <string>

#include "Reactor/EventHandler.h"

class Socket
{
public:
    Socket();
    
    bool Connect(std::string ip, unsigned int port);
    bool Send(std::string const& message);
    bool Recv();
    
    EventHandler::SocketType GetFD() const { return _socketFD; }
    
private:
    bool CreateFD();
    
private:
    EventHandler::SocketType _socketFD;
};

class SocketFactory
{
public:
    Socket* CreateSocket()
    {
        return new Socket();
    }
};
