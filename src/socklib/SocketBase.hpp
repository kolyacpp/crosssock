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
    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    class SOCKLIB_DLL SocketBase
    {
    public:
        typedef _SocketHandle SocketHandle;
        static const SocketHandle invalid_socket = _invalid_socket;
        static const Type type = _type;

        static constexpr size_t all = std::numeric_limits<size_t>::max();
        static constexpr size_t error = std::numeric_limits<size_t>::max() / 2;

        SocketBase();
        SocketBase(SocketHandle handle);
        ~SocketBase();

        void create();
        void close();
        bool is_blocking() const { return blocking; }
        bool is_invalid() const { return s == invalid_socket; }
        SocketHandle get_handle() const { return s; }

        bool wait(long timeout);

    protected:
        bool blocking = true;
        SocketHandle s = invalid_socket;
    };

} // namespace sl

#include <socklib/SocketBase.tpp>

#endif // __SOCKET_H__