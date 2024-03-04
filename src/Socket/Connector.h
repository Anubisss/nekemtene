#pragma once

#include <string>

#include "Reactor/EventHandler.h"
#include "Reactor/Reactor.h"
#include "Socket/Socket.h"
#include "Socket/ConnectorAddress.h"
#include "Socket/ConnectorHandler.h"

// TODO: use templates instead of factory
class Connector : public EventHandler
{
public:
    enum ConnectorStatus
    {
        STATUS_NONE,
        STATUS_CONNECTED,
        SATUS_DISCONNECTED
    };

public:
    Connector(Reactor* reactor, SocketFactory* socketFactory, ConnectorHandlerFactory* connectorHandlerFactory, ConnectorAddress const* address);

    void Connect();

    /* virtual */ bool HandleInput();
    /* virtual */ bool HandleOutput();
    /* virtual */ void HandleClose();

    Socket* GetSocket() const { return socket_; }

    ConnectorStatus GetStatus() const { return status_; }

    Reactor* GetReactor() const { return reactor_; }

private:
    ConnectorStatus status_;
    ConnectorAddress const* address_;

    Socket* socket_;
    Reactor* reactor_;
    ConnectorHandler* handler_;
};
