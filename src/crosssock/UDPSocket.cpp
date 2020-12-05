#include <crosssock/UDPSocket.hpp>

namespace crs
{
    //int UDPSocket::sizeofaddr = sizeof(addr);

    UDPSocket::UDPSocket() : Socket() {}

    UDPSocket::UDPSocket(SocketHandle handle) : Socket(handle) {}

    bool UDPSocket::connect(const IPAddress &address, uint16_t port)
    {
        if (address.is_none())
            return false;

        saddr.reset(reinterpret_cast<sockaddr*>(new sockaddr_in));
        *reinterpret_cast<sockaddr_in*>(saddr.get()) = OS::create_sockaddr(address.addr, port);
        sizeofaddr = sizeof(sockaddr_in);

        if (::connect(s, saddr.get(), sizeofaddr) == -1)
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
                res = ::sendto(s, data + sent, size - sent, 0, saddr.get(), sizeofaddr);

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
            res = ::recvfrom(s, data, size, 0, saddr.get(), &sizeofaddr);

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
        saddr.reset(reinterpret_cast<sockaddr*>(new sockaddr_in));
        *reinterpret_cast<sockaddr_in*>(saddr.get()) = OS::create_sockaddr(address.addr, port);
        sizeofaddr = sizeof(sockaddr_in);

        if (reinterpret_cast<sockaddr_in*>(saddr.get())->sin_addr.s_addr == INADDR_BROADCAST)
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