#ifndef __ENUMS_H__
#define __ENUMS_H__
#include <crosssock/Config.hpp>
namespace crs
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
} // namespace crs

#endif // __ENUMS_H__