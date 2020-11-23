#ifndef __SOCKETBASE_H__
#define __SOCKETBASE_H__

#include <stdexcept>
#include <chrono>

#include <ws2tcpip.h>

#include <socklib/Config.hpp>
#include <socklib/Enums.hpp>
#include <socklib/IPAddress.hpp>
#include <socklib/OS.hpp>

namespace sl
{
    class IPAddress;

    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    class CROSSSOCK_DLL SocketBase
    {
    public:
        typedef _SocketHandle SocketHandle;
        static const SocketHandle invalid_socket = _invalid_socket;
        static const Type type = _type;

        static constexpr size_t all = std::numeric_limits<int>::max();
        static constexpr size_t error = std::numeric_limits<int>::max() - 1;

        SocketBase();
        SocketBase(SocketHandle handle);
        ~SocketBase();

        void create();
        void close();

        bool connect(const IPAddress &ip, uint16_t port);

        inline bool is_blocking() const { return blocking; }
        inline bool is_invalid() const { return s == invalid_socket; }
        inline SocketHandle get_handle() const { return s; }

        bool wait(long timeout);

    protected:
        virtual void on_close(){};

        bool blocking = true;
        SocketHandle s = invalid_socket;
    };

} // namespace sl

#include <socklib/SocketBase.tpp>

#endif // __SOCKET_H__