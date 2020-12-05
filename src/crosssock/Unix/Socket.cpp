#include <crosssock/Unix/Socket.hpp>

namespace crs
{
    Socket::Socket() : SocketBase<int, -1>() {}

    Socket::Socket(SocketHandle handle) : SocketBase<int, -1>(handle) {}

    void Socket::set_blocking(bool state)
    {
        int flags = fcntl(this->s, F_GETFL, 0);
        if (flags == -1)
        {
            this->close();
            return;
        }

        flags = state ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);

        if (fcntl(this->s, F_SETFL, flags) != 0)
        {
            this->close();
            return;
        }

        this->blocking = state;
    }

    Status Socket::get_status() const
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
} // namespace crs