set(irc_socket_SRC
    IRC/IRC_ConnectorHandler.cpp
    IRC/IRC_ConnectorHandler.h
    Reactor/EventHandler.h
    Reactor/Reactor.cpp
    Reactor/Reactor.h
    Reactor/SelectReactor.cpp
    Reactor/SelectReactor.h
    Socket/Connector.cpp
    Socket/Connector.h
    Socket/ConnectorAddress.h
    Socket/ConnectorHandler.h
    Socket/Socket.cpp
    Socket/Socket.h
    main.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(irc_socket ${irc_socket_SRC})

target_link_libraries(irc_socket
    Ws2_32.lib
)

install(TARGETS irc_socket DESTINATION bin)
