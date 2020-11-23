#ifndef __UNIX__SOCKET_T__
#define __UNIX__SOCKET_T__

namespace sl
{
    template <Type _type>
    Socket<_type>::Socket() : SocketBase<int, -1, _type>() {}

    template <Type _type>
    Socket<_type>::Socket(SocketHandle handle) : SocketBase<int, -1, _type>(handle) {}

    template <Type _type>
    void Socket<_type>::set_blocking(bool state)
    {
        u_long fionbio = !state;
        //ioctlsocket(this->s, FIONBIO, &fionbio);

        this->blocking = state;
    }

    template <Type _type>
    Status Socket<_type>::get_status() const
    {
        switch (errno)
        {
        case EWOULDBLOCK:
        case EINPROGRESS:
            return Status::WouldBlock;

        case ENETDOWN:
        case ENETUNREACH:
        case ENETRESET:
        case ECONNABORTED:
        case ECONNRESET:
        case ENOTCONN:
        case ESHUTDOWN:
        case ETIMEDOUT:
        case ECONNREFUSED:
        case EHOSTDOWN:
        case EHOSTUNREACH:
            return Status::Disconnected;

        case EISCONN:
            return Status::Done;

        default:
            return Status::Error;
        }
    }
} // namespace sl

#endif