#include "IRC_ConnectorHandler.h"

#include <iostream>

#include "Socket/Socket.h"

class JoinTimer : public EventHandler
{
public:
    JoinTimer(Socket* socket) : socket_(socket) {}
    Socket* socket_;

        /* virtual */ void HandleTimeout()
        {
            std::cout << "HandleTimeout" << std::endl;
            std::string nick = "nekemtene";

            std::string commandNick = "NICK :" + nick + "\n";

            socket_->Send(commandNick);

            // ------------------------------------------------------------------------

            std::string user = "mivanmi";
            std::string mode = "0";
            std::string unused = "*";
            std::string realname = "nekemtene";

            std::string commandUser = "USER " + user + " " + mode + " " +  unused + " :" + realname + "\n";

            socket_->Send(commandUser);

            // ------------------------------------------------------------------------

            std::string channel = "#Rworld";

            std::string commandJoin = "JOIN " + channel + "\n";

            socket_->Send(commandJoin);
    }
};

/* virtual */ void IRC_ConnectorHandler::OnConnect()
{
    std::cout << "IRC_ConnectorHandler::OnConnect" << std::endl;

    JoinTimer* jt = new JoinTimer(socket_);
    connector_->GetReactor()->RegisterHandler(jt, 3000);
}

/* virtual */ void IRC_ConnectorHandler::OnDisconnect()
{
    std::cout << "IRC_ConnectorHandler::OnDisconnect" << std::endl;
    
    // real disconnect
    if (connector_->GetStatus() == Connector::STATUS_CONNECTED)
        std::cout << "REAL DC" << std::endl;
    else
        std::cout << "can't connect reconnecting..." << std::endl;
}

/* virtual */ void IRC_ConnectorHandler::OnSend()
{
    //std::cout << "IRC_ConnectorHandler::OnSend" << std::endl;
}

/* virtual */ void IRC_ConnectorHandler::OnRecv()
{
    std::cout << "IRC_ConnectorHandler::OnRecv" << std::endl;
}
