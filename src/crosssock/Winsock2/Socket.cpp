#include <crosssock/Winsock2/Socket.hpp>

namespace crs
{
    Socket::Socket() : Base() {}

    Socket::Socket(SocketHandle handle) : Base(handle) {}

    void Socket::set_blocking(bool state)
    {
        u_long fionbio = !state;
        if (ioctlsocket(this->s, FIONBIO, &fionbio) != 0)
        {
            this->close();
            return;
        }

        this->blocking = state;
    }

    Status Socket::get_status() const
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
} // namespace crs