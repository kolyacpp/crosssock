#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include <limits>

#include <crosssock/Config.hpp>

#include <crosssock/Socket.hpp>
#include <crosssock/IPAddress.hpp>

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
        

        bool set_broadcast(bool state = true);
        inline bool is_connected() { return connected; };

        sockaddr_in saddr{};

    private:
        void on_close() override;

#ifdef _WIN32
        int sizeofaddr
#else
        socklen_t sizeofaddr
#endif
            = sizeof(saddr);

        bool connected = false;
        bool broadcast = false;
    };

} // namespace sl

#endif // __UDPSOCKET_H__