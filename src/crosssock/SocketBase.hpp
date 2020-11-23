#ifndef __SOCKETBASE_H__
#define __SOCKETBASE_H__

#include <stdexcept>
#include <chrono>

#include <crosssock/Config.hpp>
#include <crosssock/Enums.hpp>
#include <crosssock/IPAddress.hpp>
#include <crosssock/OS.hpp>

namespace sl
{
    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    class CROSSSOCK_DLL SocketBase
    {
    public:
        typedef _SocketHandle SocketHandle;
        static const SocketHandle invalid_socket = _invalid_socket;
        static const Type type = _type;

        static const int error = -1;

        SocketBase();
        SocketBase(SocketHandle handle);
        ~SocketBase();

        void create();
        void close();

        bool connect(const IPAddress &ip, uint16_t port);

        inline bool is_blocking() const { return blocking; }
        inline bool is_invalid() const { return s == invalid_socket; }
        inline SocketHandle get_handle() const { return s; }
        bool bind(const IPAddress &address, uint16_t port);

        bool wait(long timeout);

        inline operator bool() { return !is_invalid(); }

    protected:
        virtual void on_close(){};

        bool blocking = true;
        SocketHandle s = invalid_socket;
    };

} // namespace sl

#include <crosssock/SocketBase.tpp>

#endif // __SOCKETBASE_H__