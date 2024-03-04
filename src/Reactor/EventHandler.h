#pragma once

#include <Winsock2.h>

class Connector;

class EventHandler
{
public:
    typedef SOCKET SocketType;

    enum EventHandlerType
    {
        EVENT_HANDLER_SOCKET,
        EVENT_HANDLER_TIMER
    };

public:
    EventHandler()
    {
        socketFD_ = INVALID_SOCKET;
        type_ = EVENT_HANDLER_SOCKET;
        timerTimeout_ = 0;
        timerResetTime_ = 0;
    }
    virtual ~EventHandler() {}
    
    // connection or data
    virtual bool HandleInput() { return false; }
    
    // output possible or non-blocking connection completes
    virtual bool HandleOutput() { return false; }

    // called when the handler is removed from the Reactor
    virtual void HandleClose() {}

    // called when timer expires
    virtual void HandleTimeout() {}

    SocketType GetFD() const { return socketFD_; }

    EventHandlerType GetType() const { return type_; }
    void SetType(EventHandlerType type) { type_ = type; }

    void SetTimerTimeout(unsigned int timeout) { timerTimeout_ = timeout; }

    unsigned long long GetTimerResetTime() const { return timerResetTime_; }
    void SetTimerResetTime(unsigned long long time) { timerResetTime_ = time; }

protected:
    SocketType socketFD_;
    EventHandlerType type_;

    unsigned int timerTimeout_;
    unsigned long long timerResetTime_;
};
