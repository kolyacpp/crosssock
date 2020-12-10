#include <iostream>
#include <thread>
#include <chrono>

#include "TestConfig.h"
#include <crosssock/UDPSocket.hpp>

int main()
{
    try
    {
        crs::UDPSocket socket_recv;

        socket_recv.bind(crs::IPAddress::any, PORT);

        crs::UDPSocket socket_send, test;
        test.create();
        test.set_addr(crs::IPAddress::loopback, PORT);
        socket_send = std::move(test);

        char buff[] = "test";

        if (socket_send.send(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (socket_recv.recv(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (std::string(buff) != "test")
            FAIL;

        socket_send.connect(crs::IPAddress::loopback, PORT);

        if (socket_send.send(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (socket_recv.recv(buff, sizeof(buff)) < sizeof(buff))
            FAIL;

        if (std::string(buff) != "test")
            FAIL;

        socket_send.close();
    }
    catch (...)
    {
        std::cout << "Exception";
        return -1;
    }

    PASS;
}