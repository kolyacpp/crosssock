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
        typedef SocketBase<SOCKET, INVALID_SOCKET> Base;
        typedef Base::SocketHandle SocketHandle;
        Socket();
        Socket(SocketHandle handle);

        Socket(Socket &&o) : Base(std::move(o)) {}
        Socket &operator=(Socket &&o) { return static_cast<Socket &>(Base::operator=(std::move(o))); }

        void set_blocking(bool state);

        Status get_status() const;
    };

} // namespace crs

#endif // __WINSOCK2__SOCKET_H__