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
        closesocket(s);
    }

    class __WinSockInitializer
    {
    public:
        __WinSockInitializer()
        {
            if (started)
                return;
            started = true;

            WSAData data;

            if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
                abort();

            if (LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion) != 2)
                abort();
        }
        ~__WinSockInitializer()
        {
            if (!started)
                return;

            started = false;
            WSACleanup();
        }

        static bool started;
    } _WinSockInitializer;
    bool __WinSockInitializer::started = false;

} // namespace sl