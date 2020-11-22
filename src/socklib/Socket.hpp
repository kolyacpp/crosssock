#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <socklib/Config.hpp>

#ifdef _WIN32
#include <socklib/Winsock2/Socket.hpp>
#else
#include <socklib/Unix/Socket.hpp>
#endif

#endif // __SOCKET_H__