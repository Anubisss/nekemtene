#pragma once

#include "Socket/ConnectorHandler.h"
#include "Socket/Connector.h"

class IRC_ConnectorHandler : public ConnectorHandler
{
public:
	IRC_ConnectorHandler(Connector* connector, Socket* socket) : ConnectorHandler(connector, socket) {}

    /* virtual */ void OnConnect();
    /* virtual */ void OnDisconnect();

    /* virtual */ void OnSend();
    /* virtual */ void OnRecv();
};

class IRC_ConnectorHandlerFactory : public ConnectorHandlerFactory
{
public:
    ConnectorHandler* CreateConnectorHandler(Connector* connector, Socket* socket)
    {
        return new IRC_ConnectorHandler(connector, socket);
    }
};
