#ifndef __WINSOCK2__SOCKET_H__
#define __WINSOCK2__SOCKET_H__

#include <cstdint>
#include <stdexcept>

#include <ws2tcpip.h>

#include <crosssock/Config.hpp>
#include <crosssock/Enums.hpp>
#include <crosssock/SocketBase.hpp>
#include <crosssock/OS.hpp>

namespace crs
{
    class CROSSSOCK_DLL Socket : public SocketBase<SOCKET, INVALID_SOCKET>
    {
    public:
        typedef typename SocketBase<SOCKET, INVALID_SOCKET>::SocketHandle SocketHandle;
        Socket();
        Socket(SocketHandle handle);

        void set_blocking(bool state);

        Status get_status() const;
    };

} // namespace crs

#endif // __WINSOCK2__SOCKET_H__