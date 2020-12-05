#include <crosssock/OS.hpp>

namespace crs
{

    sockaddr_in OS::create_sockaddr(const in_addr &addres, u_short port)
    {
        sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_port = htons(port);
        addr.sin_addr = addres;
        addr.sin_family = AF_INET;

        return addr;
    }

    void OS::close(int s)
    {
        ::close(s);
    }

} // namespace crs