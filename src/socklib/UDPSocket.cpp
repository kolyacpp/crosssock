#include <socklib/UDPSocket.hpp>

namespace sl
{
    UDPSocket::UDPSocket() : Socket<Type::UDP>() {}

    UDPSocket::UDPSocket(SocketHandle handle) : Socket<Type::UDP>(handle) {}

    size_t UDPSocket::send(const char *data, size_t size)
    {
        if (size == 0)
            return 0;

        if (s == invalid_socket)
            return error;

        for (size_t sent = 0; sent < size;)
        {
            int res = ::sendto(s, data + sent, size - sent, 0, (sockaddr *)&addr, sizeofaddr);

            if (res < 0)
            {
                close();
                return error;
            }

            sent += res;
        }

        return all;
    }

    size_t UDPSocket::recv(char *data, size_t size)
    {
        if (size == 0)
            return 0;

        if (s == invalid_socket)
            return error;

        int recved = ::recvfrom(s, data, size, 0, 0, 0);
        if (recved == size)
            return all;

        if (recved <= 0)
        {
            close();
            return error;
        }

        return recved;
    }

    bool UDPSocket::set_broadcast(bool state)
    {
        broadcast = state;

        int yes = state ? 1 : 0;
        if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes)) == -1)
            return false;

        return true;
    }

    void UDPSocket::set_addr(const IPAddress &address, uint16_t port)
    {
        addr = OS::create_sockaddr(address.get_in_addr(), port);

        if (addr.sin_addr.s_addr == INADDR_BROADCAST)
        {
            if (!broadcast)
                set_broadcast(true);
        }
        else if (broadcast)
            set_broadcast(false);
    }

    bool UDPSocket::bind(const IPAddress &address, uint16_t port)
    {
        create();

        sockaddr_in addr = OS::create_sockaddr(address.get_in_addr(), port);
        if (::bind(s, (sockaddr *)&addr, sizeof(addr)) == -1)
            return false;
        
        return true;
    }

} // namespace sl