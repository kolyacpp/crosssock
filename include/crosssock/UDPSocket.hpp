#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include <limits>
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

        UDPSocket(UDPSocket &&o) : Socket(std::move(o))
        {
            std::swap(connected, o.connected);
            std::swap(broadcast, o.broadcast);
            std::swap(sizeofaddr, o.sizeofaddr);
            std::swap(saddr, o.saddr);
        }
        UDPSocket &operator=(UDPSocket &&o)
        {
            std::swap(connected, o.connected);
            std::swap(broadcast, o.broadcast);
            std::swap(sizeofaddr, o.sizeofaddr);
            std::swap(saddr, o.saddr);
            return static_cast<UDPSocket &>(Socket::operator=(std::move(o)));
        }

        bool connect(const IPAddress &ip, uint16_t port);
        void set_addr(const IPAddress &address, uint16_t port);

        int send(const char *data, int size);
        int recv(char *data, int size);

        bool set_broadcast(bool state = true);
        inline bool is_connected() { return connected; };

    protected:
        std::unique_ptr<sockaddr> saddr;
        virtual void on_create() override;

        socklen_t sizeofaddr = 0;

        bool connected = false;
        bool broadcast = false;
    };

} // namespace crs

#endif // __UDPSOCKET_H__