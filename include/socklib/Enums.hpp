#ifndef __ENUMS_H__
#define __ENUMS_H__
#include <socklib/Config.hpp>
namespace sl
{
    enum SOCKLIB_DLL Status
    {
        Done,
        Error,
        Disconnected,
        WouldBlock,
    };

    enum SOCKLIB_DLL Type
    {
        TCP,
        UDP,
    };
} // namespace sl

#endif // __ENUMS_H__