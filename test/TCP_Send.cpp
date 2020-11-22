#include <iostream>
#include <thread>
#include <future>

#include "TestConfig.h"
#include <socklib/TCPSocket.hpp>

int main()
{
    try
    {
        sl::TCPSocket listener;
        listener.listen(PORT);

        auto thread = std::async([]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            sl::TCPSocket send_socket;
            send_socket.create();

            if (send_socket.connect(sl::IPAddress::loopback, PORT, 1000))
            {
                if (send_socket.send("PASS", sizeof("PASS")) != send_socket.all)
                    throw;
            }
            else
                throw;
        });

        sl::TCPSocket s(listener.accept());
        
        if (s.is_invalid())
            FAIL;

        char msg[1024];
        if (s.recv(msg, 5) != s.all)
            FAIL;

        if (std::string(msg) != "PASS")
            FAIL;

        thread.get();
    }
    catch (...)
    {
        std::cout << "Exception";
        return -1;
    }

    PASS;
}