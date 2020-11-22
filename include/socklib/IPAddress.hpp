#ifndef __IPADDRES_H__
#define __IPADDRES_H__

#include <string>
#include <ws2tcpip.h>
#include <socklib/Config.hpp>
#include <socklib/Socket.hpp>

namespace sl
{

    class SOCKLIB_DLL IPAddress
    {
    public:
        static const IPAddress broadcast, any, loopback, none;

        bool operator==(const IPAddress &r) const { return memcmp(&addr, &r.addr, sizeof(addr)) == 0; }

        IPAddress(const std::string &str);
        IPAddress(uint32_t address);

        in_addr get_in_addr() const { return addr; }
        bool is_none() const { return *this == none; }

    private:
        in_addr addr;
    };

} // namespace sl

#endif // __IPADDRES_H__