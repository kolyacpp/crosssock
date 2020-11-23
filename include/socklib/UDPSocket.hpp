#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include <limits>

#include <socklib/Config.hpp>

#include <socklib/Socket.hpp>
#include <socklib/IPAddress.hpp>

namespace sl
{

    class CROSSSOCK_DLL UDPSocket : public Socket<Type::UDP>
    {
    public:
        typedef typename Socket<Type::TCP>::SocketHandle SocketHandle;

        UDPSocket(const UDPSocket &) = delete;
        UDPSocket &operator=(const UDPSocket &) = delete;

        UDPSocket();
        explicit UDPSocket(SocketHandle handle);

        bool connect(const IPAddress &ip, uint16_t port);
        void set_addr(const IPAddress &address, uint16_t port);

        int send(const char *data, int size);
        int recv(char *data, int size);
        bool bind(const IPAddress &address, uint16_t port);

        bool set_broadcast(bool state = true);
        inline bool is_connected() { return connected; };

        sockaddr_in saddr{};

    private:
        void on_close() override;

        int sizeofaddr = sizeof(saddr);
        bool connected = false;
        bool broadcast = false;
    };

} // namespace sl

#endif // __UDPSOCKET_H__