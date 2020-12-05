#ifndef __SOCKETBASE_T__
#define __SOCKETBASE_T__

namespace crs
{

    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    SocketBase<_SocketHandle, _invalid_socket>::SocketBase()
    {
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    SocketBase<_SocketHandle, _invalid_socket>::SocketBase(SocketHandle handle)
    {
        this->s = handle;
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    void SocketBase<_SocketHandle, _invalid_socket>::create()
    {
        close();
        on_create();
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    void SocketBase<_SocketHandle, _invalid_socket>::close()
    {
        if (s != invalid_socket)
        {
            OS::close(s);
            s = invalid_socket;
        }
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    bool SocketBase<_SocketHandle, _invalid_socket>::bind(const IPAddress &address, uint16_t port)
    {
        create();

        sockaddr_in addr = OS::create_sockaddr(address.addr, port);
        if (::bind(s, (sockaddr *)&addr, sizeof(addr)) == -1)
            return false;

        return true;
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    bool SocketBase<_SocketHandle, _invalid_socket>::wait(long timeout)
    {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(s, &set);

        timeval tv;
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        if (::select(static_cast<int>(s + 1), &set, NULL, NULL, &tv) > 0)
            return true;
        else
            return false;
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket>
    SocketBase<_SocketHandle, _invalid_socket>::~SocketBase()
    {
        close();
    }

} // namespace crs

#endif