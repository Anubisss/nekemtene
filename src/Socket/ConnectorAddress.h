#pragma once

#include <string>

class ConnectorAddress
{
public:
    ConnectorAddress(std::string ip, unsigned int port)
    {
        ip_ = ip;
        port_ = port;
    }
    
    std::string GetIP() const { return ip_; }
    unsigned int GetPort() const { return port_; }

private:
    std::string ip_;
    unsigned int port_;
};
