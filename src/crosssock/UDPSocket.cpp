#include <crosssock/UDPSocket.hpp>

namespace crs
{
    UDPSocket::UDPSocket() : Socket() {}

    UDPSocket::UDPSocket(SocketHandle handle) : Socket(handle) {}

    UDPSocket::UDPSocket(UDPSocket &&o) : Socket(std::move(o))
    {
        std::swap(connected, o.connected);
        std::swap(broadcast, o.broadcast);
        std::swap(sizeofaddr, o.sizeofaddr);
        std::swap(saddr6, o.saddr6);
    }

    UDPSocket &UDPSocket::operator=(UDPSocket &&o)
    {
        std::swap(connected, o.connected);
        std::swap(broadcast, o.broadcast);
        std::swap(sizeofaddr, o.sizeofaddr);
        std::swap(saddr6, o.saddr6);

        return static_cast<UDPSocket &>(Socket::operator=(std::move(o)));
    }

    bool UDPSocket::connect(const IPAddress &address, uint16_t port)
    {
        if (address.is_none())
            return false;

        saddr4 = OS::create_sockaddr(address.addr, port);
        sizeofaddr = sizeof(sockaddr_in);

        if (::connect(s, &saddr, sizeofaddr) == -1)
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
            if (connected)
                res = ::send(s, data + sent, size - sent, 0);
            else
                res = ::sendto(s, data + sent, size - sent, 0, &saddr, sizeofaddr);

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
        if (connected)
            res = ::recv(s, data, size, 0);
        else
            res = ::recvfrom(s, data, size, 0, &saddr, &sizeofaddr);

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
        saddr4 = OS::create_sockaddr(address.addr, port);
        sizeofaddr = sizeof(sockaddr_in);

        if (saddr4.sin_addr.s_addr == INADDR_BROADCAST)
        {
            if (!broadcast)
                set_broadcast(true);
        }
        else if (broadcast)
            set_broadcast(false);
    }

    void UDPSocket::on_create()
    {
        s = socket(AF_INET, SOCK_DGRAM, 0);
        broadcast = false;
        connected = false;
    }

} // namespace crs