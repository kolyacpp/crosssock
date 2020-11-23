#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <crosssock/Config.hpp>

#ifdef _WIN32
#include <crosssock/Winsock2/Socket.hpp>
#else
#include <crosssock/Unix/Socket.hpp>
#endif

#endif // __SOCKET_H__