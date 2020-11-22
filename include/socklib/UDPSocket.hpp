#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include <limits>

#include <socklib/Config.hpp>

#include <socklib/Socket.hpp>
#include <socklib/IPAddress.hpp>

namespace sl
{

    class SOCKLIB_DLL UDPSocket : public Socket<Type::UDP>
    {
    public:
        typedef typename Socket<Type::TCP>::SocketHandle SocketHandle;

        UDPSocket(const UDPSocket &) = delete;            
        UDPSocket &operator=(const UDPSocket &) = delete;

        UDPSocket();
        explicit UDPSocket(SocketHandle handle);

        void set_addr(const IPAddress &address, uint16_t port);
        size_t send(const char *data, size_t size);
        size_t recv(char *data, size_t size);
        bool bind(const IPAddress &address, uint16_t port);

        bool set_broadcast(bool state = true);

    private:
        sockaddr_in addr{};
        const int sizeofaddr = sizeof(addr);
        bool broadcast = false;
    };

} // namespace sl

#endif // __UDPSOCKET_H__