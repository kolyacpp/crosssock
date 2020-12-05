#include <crosssock/OS.hpp>

namespace crs
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
        closesocket(s);
    }

    OS::_WinSockInitializer OS::WinSockInitializer;

    OS::_WinSockInitializer::_WinSockInitializer()
    {
        WSAData data;

        if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
            abort();

        if (LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion) != 2)
            abort();
    }

    OS::_WinSockInitializer::~_WinSockInitializer()
    {
        WSACleanup();
    }

} // namespace crs