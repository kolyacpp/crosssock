#ifndef __SOCKETBASE_T__
#define __SOCKETBASE_T__

namespace sl
{

    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    SocketBase<_SocketHandle, _invalid_socket, _type>::SocketBase()
    {
        create();
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    SocketBase<_SocketHandle, _invalid_socket, _type>::SocketBase(SocketHandle handle)
    {
        this->s = handle;
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    void SocketBase<_SocketHandle, _invalid_socket, _type>::create()
    {
        close();

        s = socket(AF_INET, type == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);

        if (s == invalid_socket)
            return;

        if (type == TCP)
        {
            int disable = 1;
            if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char *)&disable, sizeof(disable)) == -1)
                s = invalid_socket;
        }
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    void SocketBase<_SocketHandle, _invalid_socket, _type>::close()
    {
        if (s != invalid_socket)
        {
            OS::close(s);
            s = invalid_socket;
        }
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    bool SocketBase<_SocketHandle, _invalid_socket, _type>::wait(long timeout)
    {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(s, &set);

        timeval tv;
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        if (::select(s + 1, &set, NULL, NULL, &tv) > 0)
            return true;
        else
            return false;
    }

    template <typename _SocketHandle, _SocketHandle _invalid_socket, Type _type>
    SocketBase<_SocketHandle, _invalid_socket, _type>::~SocketBase()
    {
        close();
    }

} // namespace sl

#endif