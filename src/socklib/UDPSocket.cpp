#include <socklib/UDPSocket.hpp>

namespace sl
{
    //int UDPSocket::sizeofaddr = sizeof(addr);

    UDPSocket::UDPSocket() : Socket<Type::UDP>() {}

    UDPSocket::UDPSocket(SocketHandle handle) : Socket<Type::UDP>(handle) {}

    bool UDPSocket::connect(const IPAddress &ip, uint16_t port)
    {
        if (ip.is_none())
            return false;

        saddr = OS::create_sockaddr(ip.addr, port);

        if (::connect(s, (sockaddr *)&saddr, sizeof(saddr)) == -1)
            return false;

        connected = true;
        return true;
    }

    int UDPSocket::send(const char *data, int size)
    {
        if (size == 0)
            return 0;

        if (s == invalid_socket)
            return error;

        for (int sent = 0; sent < size;)
        {
            int res;
            if(connected)
                res = ::send(s, data + sent, size - sent, 0);
            else
                res = ::sendto(s, data + sent, size - sent, 0, (sockaddr *)&saddr, sizeofaddr);

            if (res < 0)
            {
                close();
                return error;
            }

            sent += res;
        }

        return size;
    }

    int UDPSocket::recv(char *data, int size)
    {
        if (size == 0)
            return 0;

        if (s == invalid_socket)
            return error;

        int res;
        if(connected)
                res = ::recv(s, data, size, 0);
            else
                res = ::recvfrom(s, data, size, 0, (sockaddr *)&saddr, &sizeofaddr);

        if (res <= 0)
        {
            close();
            return error;
        }

        return res;
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
        saddr = OS::create_sockaddr(address.addr, port);

        if (saddr.sin_addr.s_addr == INADDR_BROADCAST)
        {
            if (!broadcast)
                set_broadcast(true);
        }
        else if (broadcast)
            set_broadcast(false);
    }

    void UDPSocket::on_close() 
    {
        broadcast = false;
        connected = false;
    }


} // namespace sl