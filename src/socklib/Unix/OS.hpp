#ifndef __UNIX__OS_H__
#define __UNIX__OS_H__

#include <stdexcept>

#include <ws2tcpip.h>

#include <socklib/Config.hpp>

namespace sl
{

    class CROSSSOCK_DLL OS
    {
    public:
        static sockaddr_in create_sockaddr(const in_addr &addr, uint16_t port);
        static void close(SOCKET s);

    private:
        OS(){}
    };

} // namespace sl

#endif // __UNIX__OS_H__