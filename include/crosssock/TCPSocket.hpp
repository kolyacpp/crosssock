#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include <chrono>

#include <crosssock/Config.hpp>
#include <crosssock/Socket.hpp>
#include <crosssock/IPAddress.hpp>

namespace sl
{

    class CROSSSOCK_DLL TCPSocket : public Socket<Type::TCP>
    {
    public:
        typedef typename Socket<Type::TCP>::SocketHandle SocketHandle;

        TCPSocket(const TCPSocket &) = delete;
        TCPSocket &operator=(const TCPSocket &) = delete;

        TCPSocket();
        explicit TCPSocket(SocketHandle handle);

        bool connect(const IPAddress &ip, uint16_t port);
        bool connect(const IPAddress &ip, uint16_t port,
                     int timeout);

        int send(const char *data, int size);
        int recv(char *data, int size);

        bool listen(uint16_t port);
        inline SocketHandle accept() { return ::accept(s, NULL, NULL); };
        SocketHandle accept(int timeout);
    };

} // namespace sl

#endif // __TCPSOCKET_H__