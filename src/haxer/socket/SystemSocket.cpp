#include "SystemSocket.hpp"


int SystemSocket::socket(int domain, int type, int protocol)
{
    ::socket(domain, type, protocol);
}
int SystemSocket::bind(int fileDescriptor, const sockaddr* addr, socklen_t addrLen)
{
    return ::bind(fileDescriptor, addr, addrLen);
}
int SystemSocket::close(int fileDescriptor)
{
    return ::close(fileDescriptor);
}
ssize_t SystemSocket::sendto(int fileDescriptor, const void* buf, size_t bufLen, int flags, const sockaddr* destAddr,
                       socklen_t addrLen)
{
    return ::sendto(fileDescriptor, buf, bufLen, flags, destAddr, addrLen);
}
ssize_t SystemSocket::recvfrom(int fileDescriptor, void* buf, size_t bufLen, int flags, sockaddr* remoteAddr,
                         socklen_t* addrLen)
{
    return ::recvfrom(fileDescriptor, buf, bufLen, flags, remoteAddr, addrLen);
}
int SystemSocket::fcntl(int fileDescriptor, int cmd, int flag)
{
    return ::fcntl(fileDescriptor, cmd, flag);
}
