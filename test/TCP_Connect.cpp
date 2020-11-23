#include <iostream>

#include "TestConfig.h"
#include <crosssock/TCPSocket.hpp>

int main()
{
    try
    {
        sl::TCPSocket socket;
        if (!socket.connect(sl::IPAddress("1.1.1.1"), 80, 1000))
            FAIL;
        
        socket.create();

        if (!socket.connect(sl::IPAddress("google.com"), 80, 1000))
            FAIL;

        socket.create();

        if (!socket.connect(sl::IPAddress("1.1.1.1"), 80))
            FAIL;
    }
    catch (...)
    {
        std::cout << "Exception";
        return -1;
    }

    PASS;
}