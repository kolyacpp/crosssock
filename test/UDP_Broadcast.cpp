#include <iostream>
#include <thread>
#include <chrono>

#include "TestConfig.h"
#include <crosssock/UDPSocket.hpp>

int main()
{
    try
    {
        sl::UDPSocket socket_recv;
        socket_recv.bind(sl::IPAddress::any, PORT);

        sl::UDPSocket socket_send;
        socket_send.set_broadcast(true);
        socket_send.set_addr(sl::IPAddress::broadcast, PORT);

        char buff[] = "test";

        if (socket_send.send(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (socket_recv.recv(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (std::string(buff) != "test")
            FAIL;
    }
    catch (...)
    {
        std::cout << "Exception";
        return -1;
    }

    PASS;
}