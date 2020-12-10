#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include <memory>

#include <crosssock/Config.hpp>

#include <crosssock/Socket.hpp>
#include <crosssock/IPAddress.hpp>

namespace crs
{

    class CROSSSOCK_DLL UDPSocket : public Socket
    {
    public:
        typedef typename Socket::SocketHandle SocketHandle;

        UDPSocket();
        UDPSocket(SocketHandle handle);

        UDPSocket(UDPSocket &&o);
        UDPSocket &operator=(UDPSocket &&o);

        bool connect(const IPAddress &ip, uint16_t port);
        void set_addr(const IPAddress &address, uint16_t port);

        int send(const char *data, int size);
        int recv(char *data, int size);

        bool set_broadcast(bool state = true);
        inline bool is_connected() { return connected; };

    protected:
        union{
            sockaddr saddr;
            sockaddr_in saddr4;
            sockaddr_in6 saddr6;
        };
        socklen_t sizeofaddr = 0;

        virtual void on_create() override;

        bool connected = false;
        bool broadcast = false;
    };

} // namespace crs

#endif // __UDPSOCKET_H__