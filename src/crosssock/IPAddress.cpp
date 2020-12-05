#include <crosssock/IPAddress.hpp>

namespace crs
{
    const IPAddress IPAddress::broadcast = IPAddress((uint32_t)INADDR_BROADCAST);
    const IPAddress IPAddress::any = IPAddress((uint32_t)INADDR_ANY);
    const IPAddress IPAddress::loopback = IPAddress((uint32_t)INADDR_LOOPBACK);
    const IPAddress IPAddress::none = IPAddress((uint32_t)INADDR_NONE);

    IPAddress::IPAddress(const std::string &str)
    {
        if (inet_pton(AF_INET, str.c_str(), &addr) == 1)
            return;

        addrinfo hints{}, *res;
        hints.ai_family = AF_INET;

        if (getaddrinfo(str.c_str(), NULL, &hints, &res) == 0)
        {
            if (res != NULL)
                addr = ((sockaddr_in*)res->ai_addr)->sin_addr;
            else
                *this = none;
        }

        freeaddrinfo(res);
    }

    IPAddress::IPAddress(uint32_t address)
    {
        addr.s_addr = htonl(address);
    }

} // namespace crs