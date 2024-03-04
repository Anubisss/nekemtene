#include <iostream>

#include <Winsock2.h>

#include "IRC/IRC_ConnectorHandler.h"
#include "Reactor/SelectReactor.h"
#include "Socket/Connector.h"

int main()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
    {
        std::cout << "WSAStartup error" << std::endl;
        return 1;
    }

    Reactor* r = new SelectReactor();
    SocketFactory socketFactory;
    IRC_ConnectorHandlerFactory chf;
    
    ConnectorAddress ca1("80.65.50.142", 6667);
    ConnectorAddress ca2("83.140.172.212", 6667);
    ConnectorAddress ca3("213.92.8.4", 6667);

    Connector* c1 = new Connector(r, &socketFactory, &chf, &ca1);
    //c1->Connect();
    
    Connector* c2 = new Connector(r, &socketFactory, &chf, &ca2);
    //c2->Connect();
    
    Connector* c3 = new Connector(r, &socketFactory, &chf, &ca3);
    //c3->Connect();
    
    while (1)
    {
        r->HandleEvents();
        Sleep(100);
    }
    
    WSACleanup();
    return 0;
}
