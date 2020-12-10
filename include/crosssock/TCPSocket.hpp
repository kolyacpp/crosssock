#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include <crosssock/Config.hpp>
#include <crosssock/Socket.hpp>
#include <crosssock/IPAddress.hpp>

namespace crs
{

    class CROSSSOCK_DLL TCPSocket : public Socket
    {
    public:
        typedef typename Socket::SocketHandle SocketHandle;

        TCPSocket();
        TCPSocket(SocketHandle handle);

        TCPSocket(TCPSocket &&o) : Socket(std::move(o)) {}
        TCPSocket &operator=(TCPSocket &&o) { return static_cast<TCPSocket &>(Socket::operator=(std::move(o))); }

        bool connect(const IPAddress &ip, uint16_t port);
        bool connect(const IPAddress &ip, uint16_t port,
                     int timeout);

        int send(const char *data, int size);
        int recv(char *data, int size);

        bool listen(uint16_t port);
        inline TCPSocket accept() { return ::accept(s, NULL, NULL); };
        SocketHandle accept(int timeout);

    protected:
        virtual void on_create() override;
    };

} // namespace crs

#endif // __TCPSOCKET_H__