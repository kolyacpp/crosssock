#include <iostream>

#include "TestConfig.h"
#include <socklib/TCPSocket.hpp>

int main()
{
    try
    {
        sl::TCPSocket socket;
        if (!socket.connect(sl::IPAddress("173.194.73.113"), 80, 1000))
            FAIL;
        
        socket.create();

        if (!socket.connect(sl::IPAddress("google.com"), 80, 1000))
            FAIL;

        socket.create();

        if (!socket.connect(sl::IPAddress("173.194.73.113"), 80))
            FAIL;
    }
    catch (...)
    {
        std::cout << "Exception";
        return -1;
    }

    PASS;
}