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
        socket_send.set_addr(sl::IPAddress::loopback, PORT);

        char buff[] = "test";

        if (socket_send.send(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (socket_recv.recv(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (std::string(buff) != "test")
            FAIL;

        socket_send.connect(sl::IPAddress::loopback, PORT);

        if (socket_send.send(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (socket_recv.recv(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (std::string(buff) != "test")
            FAIL;

        socket_send.close();
        if(socket_send.is_connected())
            FAIL;
    }
    catch (...)
    {
        std::cout << "Exception";
        return -1;
    }

    PASS;
}