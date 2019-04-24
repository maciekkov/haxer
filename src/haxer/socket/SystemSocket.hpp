#pragma onnce
#include <stdexcept>
#include <arpa/inet.h>

class SystemSocket
{
public:
    class SocketExceptions : public std::runtime_error
    {
        SocketExceptions(const std::string& err)
            : std::runtime_error{err}
        {
        }
    };
    virtual int     socket(int domain, int type, int protocol);
    virtual int     bind(int fileDescriptor, const sockaddr* addr, socklen_t addrLen);
    virtual int     close(int fileDescriptor);
    virtual int     fcntl(int fileDescriptor, int cmd, int flag);
    virtual ssize_t sendto(int fileDescriptor, const void* buf, size_t bufLen, int flags, const sockaddr* destAddr,
                           socklen_t addrLen);
    virtual ssize_t recvfrom(int fileDescriptor, void* buf, size_t bufLen, int flags, sockaddr* remoteAddr,
                             socklen_t* addrLen);
};
