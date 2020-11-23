#include <socklib/OS.hpp>

namespace sl
{

    sockaddr_in OS::create_sockaddr(const in_addr &addres, u_short port)
    {
        sockaddr_in addr;
        ZeroMemory(&addr, sizeof(addr));
        addr.sin_port = htons(port);
        addr.sin_addr = addres;
        addr.sin_family = AF_INET;

        return addr;
    }

    void OS::close(SOCKET s)
    {
        close(s);
    }

} // namespace sl