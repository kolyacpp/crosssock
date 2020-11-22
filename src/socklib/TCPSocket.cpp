#include <socklib/TCPSocket.hpp>

namespace sl
{
    TCPSocket::TCPSocket() : Socket<Type::TCP>() {}

    TCPSocket::TCPSocket(SocketHandle handle) : Socket<Type::TCP>(handle) {}

    bool TCPSocket::connect(const IPAddress &ip, uint16_t port)
    {
        if(ip.is_none())
            return false;

        auto addr = OS::create_sockaddr(ip.get_in_addr(), port);

        if (::connect(s, (sockaddr *)&addr, sizeof(addr)) == -1)
            return false;

        return true;
    }

    bool TCPSocket::connect(const IPAddress &ip, uint16_t port, int timeout)
    {
        if(ip.is_none())
            return false;

        auto addr = OS::create_sockaddr(ip.get_in_addr(), port);

        bool last_blocking = blocking;
        if (last_blocking)
            set_blocking(false);

        if (::connect(s, (sockaddr *)&addr, sizeof(addr)) >= 0)
        {
            if (last_blocking)
                set_blocking(true);

            return true;
        }

        auto status = get_status();

        if (status == WouldBlock)
        {
            timeval tv;
            tv.tv_sec = timeout / 1000;
            tv.tv_usec = (timeout % 1000) * 1000;

            fd_set setW, setE;
            FD_ZERO(&setW);
            FD_SET(s, &setW);
            memcpy(&setE, &setW, sizeof(setE));

            if (select(s + 1, NULL, &setW, &setE, &tv) > 0)
            {
                if (FD_ISSET(s, &setE))
                {
                    status = Error;
                    return false;
                }
                else
                {
                    status = Done;
                    return true;
                }
            }
        }

        if (last_blocking)
            set_blocking(true);

        return false;
    }

    size_t TCPSocket::send(const char *data, size_t size)
    {
        if (size == 0)
            return 0;

        if (s == invalid_socket)
            return error;

        for (size_t sent = 0; sent < size;)
        {
            int res = ::send(s, data + sent, size - sent, 0);

            if (res < 0)
            {
                close();
                return error;
            }

            sent += res;
        }

        return all;
    }

    size_t TCPSocket::recv(char *data, size_t size)
    {
        if (size == 0)
            return 0;

        if (s == invalid_socket)
            return error;

        int recved = ::recv(s, data, size, 0);
        if (recved == size)
            return all;

        if (recved < 0)
        {
            close();
            return error;
        }

        return recved;
    }

    bool TCPSocket::listen(uint16_t port)
    {
        sockaddr_in addr = OS::create_sockaddr(IPAddress::any.get_in_addr(), port);
        if (::bind(s, (sockaddr *)&addr, sizeof(addr)) == -1)
            return false;

        if (::listen(s, SOMAXCONN) == -1)
            return false;

        return true;
    }

    TCPSocket::SocketHandle TCPSocket::accept() 
    {
        return ::accept(s, NULL, NULL);
    }

    TCPSocket::SocketHandle TCPSocket::accept(int timeout)
    {
        bool last_blocking = is_blocking();
        if (last_blocking)
            set_blocking(false);

        fd_set set;
        FD_ZERO(&set);
        FD_SET(s, &set);

        timeval tv;
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        if (::select(s + 1, &set, NULL, NULL, &tv) > 0)
            return ::accept(s, NULL, NULL);

        if (last_blocking)
            set_blocking(true);

        return invalid_socket;
    }

} // namespace sl