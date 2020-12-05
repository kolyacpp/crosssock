#include <iostream>
#include <thread>
#include <future>

#include "TestConfig.h"
#include <crosssock/TCPSocket.hpp>

int main()
{
    try
    {
        crs::TCPSocket listener;
        listener.listen(PORT);

        auto thread = std::async([]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            crs::TCPSocket send_socket;
            send_socket.create();

            if (send_socket.connect(crs::IPAddress::loopback, PORT, 1000))
            {
                if (send_socket.send("PASS", sizeof("PASS")) == -1)
                    FAIL;
            }
            else
                FAIL;
        });

        crs::TCPSocket s = listener.accept();
        
        if (s.is_invalid())
            FAIL;

        char msg[1024];
        if (s.recv(msg, 5) == -1)
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