#ifndef __SOCKETBASE_H__
#define __SOCKETBASE_H__

#include <algorithm>

#include <crosssock/Config.hpp>
#include <crosssock/Enums.hpp>
#include <crosssock/IPAddress.hpp>
#include <crosssock/OS.hpp>

namespace crs
{
    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    class CROSSSOCK_DLL SocketBase
    {
    public:
        typedef _SocketHandle SocketHandle;
        static const SocketHandle invalid_socket = _invalid_socket;

        static const int error = -1;

        SocketBase(const SocketBase &) = delete;
        SocketBase &operator=(const SocketBase &) = delete;

        SocketBase(SocketBase &&o)
        {
            std::swap(blocking, o.blocking);
            std::swap(s, o.s);
        };

        SocketBase& operator=(SocketBase &&o)
        {
            if (this != &o)
            {
                close();
                std::swap(blocking, o.blocking);
                std::swap(s, o.s);
            }

            return *this;
        };

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
        virtual void on_create() = 0;

        bool blocking = true;
        SocketHandle s = invalid_socket;
    };

} // namespace crs

#include <crosssock/SocketBase.tpp>

#endif // __SOCKETBASE_H__