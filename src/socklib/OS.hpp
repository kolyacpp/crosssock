#ifndef __OS_H__
#define __OS_H__

#include <socklib/Config.hpp>

#ifdef _WIN32
#include <socklib/Winsock2/OS.hpp>
#else
#include <socklib/Unix/OS.hpp>
#endif

#endif // __OS_H__