#include "Connector.h"

#include <iostream>

Connector::Connector(Reactor* reactor,
                     SocketFactory* socketFactory,
                     ConnectorHandlerFactory* connectorHandlerFactory,
                     ConnectorAddress const* address
                    ) : reactor_(reactor), address_(address)
{
    status_ = ConnectorStatus::STATUS_NONE;
    socket_ = socketFactory->CreateSocket();
    socketFD_ = socket_->GetFD();
    handler_ = connectorHandlerFactory->CreateConnectorHandler(this, socket_);
}

void Connector::Connect()
{
    socket_->Connect(address_->GetIP(), address_->GetPort());
    reactor_->RegisterHandler(this);
}

/* virtual */ bool Connector::HandleInput()
{
    std::cout << "Connector::HandleInput" << std::endl;
    handler_->OnRecv();
    return socket_->Recv();
}

/* virtual */ bool Connector::HandleOutput()
{
    //std::cout << "Connector::HandleOutput" << std::endl;
    if (status_ != ConnectorStatus::STATUS_CONNECTED)
    {
        status_ = ConnectorStatus::STATUS_CONNECTED;
        handler_->OnConnect();
    }
    else
        handler_->OnSend();
    return true;
}

/* virtual */ void Connector::HandleClose()
{
    std::cout << "Connector::HandleClose" << std::endl;
    handler_->OnDisconnect();
    status_ = ConnectorStatus::SATUS_DISCONNECTED;
}
