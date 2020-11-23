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

#include <socklib/Config.hpp>
#include <socklib/Enums.hpp>
#include <socklib/SocketBase.hpp>
#include <socklib/OS.hpp>

namespace sl
{

    template <Type _type>
    class CROSSSOCK_DLL Socket : public SocketBase<int, -1, _type>
    {
    public:
        typedef typename SocketBase<int, -1, _type>::SocketHandle SocketHandle;
        Socket();
        Socket(SocketHandle handle);

        void set_blocking(bool state);

        Status get_status() const;
    };

} // namespace sl

#include <socklib/Unix/Socket.tpp>

#endif // __UNIX__SOCKET_H__