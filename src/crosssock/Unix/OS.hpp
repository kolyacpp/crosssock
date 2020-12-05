#ifndef __UNIX__OS_H__
#define __UNIX__OS_H__

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

namespace crs
{

    class CROSSSOCK_DLL OS
    {
    public:
        static sockaddr_in create_sockaddr(const in_addr &addr, uint16_t port);
        static void close(int s);

    private:
        OS() {}
    };

} // namespace crs

#endif // __UNIX__OS_H__