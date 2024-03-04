#include <Winsock2.h>
#include <ws2tcpip.h>

#include <iostream>

#include "Socket.h"

#define DEFAULT_BUFLEN 512

Socket::Socket()
{
    _socketFD = INVALID_SOCKET;
    CreateFD();
}

bool Socket::CreateFD()
{
    _socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socketFD == INVALID_SOCKET)
    {
        std::cout << "CreateFD error " << WSAGetLastError() << std::endl;
        return false;
    }

    unsigned long enableNonBlockingMode = 1;
    if (ioctlsocket(_socketFD, FIONBIO, &enableNonBlockingMode))
    {
        std::cout << "ioctlsocket error " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

bool Socket::Connect(std::string ip, unsigned int port)
{
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(port);

    if (connect(_socketFD, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSAEWOULDBLOCK)
        {
            std::cout << "connect error " << WSAGetLastError() << std::endl;
            return false;
        }
    }
    return true;
}

bool Socket::Send(std::string const& message)
{
    if (send(_socketFD, message.c_str(), message.length(), 0) == SOCKET_ERROR)
    {
        std::cout << "send error " << WSAGetLastError() << std::endl;
        return false;
    }
    std::cout << "send [" << message.length() << "] " << message.c_str() << std::endl;
    return true;
}

bool Socket::Recv()
{
    char recvbuf[512];
    int res = 0;
    memset(recvbuf, 0, 512);
    res = recv(_socketFD, recvbuf, 512, 0);
    if (res > 0)
        std::cout << "recv [" << res << "] " << recvbuf << std::endl;
    else if (res == 0)
    {
        std::cout << "connection is closed" << std::endl;
        return false;
    }
    else
    {
        std::cout << "recv error " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}
