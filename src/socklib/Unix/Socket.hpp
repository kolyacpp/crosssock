#ifndef __UNIX__SOCKET_H__
#define __UNIX__SOCKET_H__

#include <cstdint>
#include <stdexcept>

#include <ws2tcpip.h>

#include <socklib/Config.hpp>
#include <socklib/Enums.hpp>
#include <socklib/SocketBase.hpp>
#include <socklib/OS.hpp>

namespace sl
{

    template <Type _type>
    class CROSSSOCK_DLL Socket : public SocketBase<SOCKET, INVALID_SOCKET, _type>
    {
    public:
        typedef typename SocketBase<SOCKET, INVALID_SOCKET, _type>::SocketHandle SocketHandle;
        Socket();
        Socket(SocketHandle handle);

        void set_blocking(bool state);

        Status get_status() const;
    };

} // namespace sl

#include <socklib/Unix/Socket.tpp>

#endif // __UNIX__SOCKET_H__