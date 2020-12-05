#ifndef __UNIX__SOCKET_H__
#define __UNIX__SOCKET_H__

#include <cstdint>
#include <stdexcept>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <unistd.h>
#include <errno.h>
#include <cstring>

#include <crosssock/Config.hpp>
#include <crosssock/Enums.hpp>
#include <crosssock/SocketBase.hpp>
#include <crosssock/OS.hpp>

namespace crs
{

    class CROSSSOCK_DLL Socket : public SocketBase<int, -1>
    {
    public:
        typedef typename SocketBase<int, -1>::SocketHandle SocketHandle;
        Socket();
        Socket(SocketHandle handle);

        void set_blocking(bool state);

        Status get_status() const;
    };

} // namespace crs

#endif // __UNIX__SOCKET_H__