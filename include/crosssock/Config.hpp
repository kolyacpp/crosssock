#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef MSVC
#ifdef CROSSSOCK_EXPORT
#define CROSSSOCK_DLL __declspec(dllexport)
#else
#define CROSSSOCK_DLL __declspec(dllimport)
#endif
#else
#define CROSSSOCK_DLL
#endif


#if defined(__GNUC__) && defined(WIN32)
#include <ws2tcpip.h>
extern "C"
{
    WINSOCK_API_LINKAGE INT WSAAPI inet_pton(INT Family, PCSTR pszAddrString, PVOID pAddrBuf);
    WINSOCK_API_LINKAGE PCSTR WSAAPI inet_ntop(INT Family, PVOID pAddr, PSTR pStringBuf, size_t StringBufSize);
}
#endif

#endif // __CONFIG_H__