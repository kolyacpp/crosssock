#ifndef __WINSOCK2__SOCKET_T__
#define __WINSOCK2__SOCKET_T__

namespace sl
{
    template <Type _type>
    Socket<_type>::Socket() : SocketBase<SOCKET, INVALID_SOCKET, _type>() {}

    template <Type _type>
    Socket<_type>::Socket(SocketHandle handle) : SocketBase<SOCKET, INVALID_SOCKET, _type>(handle) {}

    template <Type _type>
    void Socket<_type>::set_blocking(bool state)
    {
        u_long fionbio = !state;
        ioctlsocket(this->s, FIONBIO, &fionbio);

        this->blocking = state;
    }

    template <Type _type>
    Status Socket<_type>::get_status() const
    {
        switch (WSAGetLastError())
        {
        case WSAEALREADY:
        case WSAEWOULDBLOCK:
            return Status::WouldBlock;

        case WSAENETDOWN:
        case WSAENETUNREACH:
        case WSAENETRESET:
        case WSAECONNABORTED:
        case WSAECONNRESET:
        case WSAENOTCONN:
        case WSAESHUTDOWN:
        case WSAETIMEDOUT:
        case WSAECONNREFUSED:
        case WSAEHOSTDOWN:
        case WSAEHOSTUNREACH:
        case WSAHOST_NOT_FOUND:
            return Status::Disconnected;

        case WSAEISCONN:
            return Status::Done;

        default:
            return Status::Error;
        }
    }
} // namespace sl

#endif