#ifndef __ENUMS_H__
#define __ENUMS_H__
#include <crosssock/Config.hpp>
namespace sl
{
    enum CROSSSOCK_DLL Status
    {
        Done,
        Error,
        Disconnected,
        WouldBlock,
    };

    enum CROSSSOCK_DLL Type
    {
        TCP,
        UDP,
    };
} // namespace sl

#endif // __ENUMS_H__