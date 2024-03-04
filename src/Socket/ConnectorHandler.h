#pragma once

class Connector;
class Socket;

class ConnectorHandler
{
public:
    ConnectorHandler(Connector* connector, Socket* socket) : connector_(connector), socket_(socket) {}

    virtual void OnConnect() = 0;
    virtual void OnDisconnect() = 0;
    
    virtual void OnSend() = 0;
    virtual void OnRecv() = 0;
    
protected:
    Connector* connector_;
    Socket* socket_;
};

class ConnectorHandlerFactory
{
public:
    virtual ConnectorHandler* CreateConnectorHandler(Connector* connector, Socket* socket) = 0;
};
