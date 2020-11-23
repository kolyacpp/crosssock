#ifndef __OS_H__
#define __OS_H__

#include <crosssock/Config.hpp>

#ifdef _WIN32
#include <crosssock/Winsock2/OS.hpp>
#else
#include <crosssock/Unix/OS.hpp>
#endif

#endif // __OS_H__