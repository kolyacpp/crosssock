#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include <chrono>

#include <socklib/Config.hpp>
#include <socklib/Socket.hpp>
#include <socklib/IPAddress.hpp>

namespace sl
{

    class SOCKLIB_DLL TCPSocket : public Socket<Type::TCP>
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

        size_t send(const char *data, size_t size);
        size_t recv(char *data, size_t size);

        bool listen(uint16_t port);
        SocketHandle accept();
        SocketHandle accept(int timeout);
    };

} // namespace sl

#endif // __TCPSOCKET_H__