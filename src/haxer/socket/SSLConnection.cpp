#include "SSLConnection.hpp"

#include <iostream>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

void print(const std::string& str)
{
    std::cout << str << "\n \n";
}
void print(const int str)
{
    std::cout << str << "\n \n";
}

SSLConnection::SSLConnection(const uint16_t port, const std::string& ip)
    : mUnixFileDescriptor{invalidFd}
{
    config(port, ip);
    connectSocket();
}
void SSLConnection::config(const uint16_t port, const std::string& ip)
{
    mConfig.domain   = AF_INET;
    mConfig.type     = SOCK_STREAM;
    mConfig.protocol = 0;
    mConfig.ipName   = ip;
    mConfig.port     = port;
    mConfig.address  = {};
}

void SSLConnection::connectSocket()
{
    openSocket();
    connectToServer();
    connectSSLSocket();
    // setNonBlocking();

    print(" -- connection established --");
}

void SSLConnection::connectToServer()
{
    setSockAddress();
    socklen_t socklen = sizeof(mConfig.address);

    if (connect(mUnixFileDescriptor, (struct sockaddr*)&mConfig.address, socklen) < 0)
        throw SSLExceptions(__func__, "Connectiing to server faild");
}

void SSLConnection::setSockAddress()
{
    socklen_t addressLength = sizeof(sockaddr_in);
    memset(&mConfig.address, 0, addressLength);

    mConfig.address.sin_addr.s_addr = inet_addr(mConfig.ipName.c_str());
    mConfig.address.sin_port        = htons(mConfig.port);
    mConfig.address.sin_family      = AF_INET;
}

void SSLConnection::openSocket()
{
    bool isSocketOpened = mUnixFileDescriptor != invalidFd;
    if (isSocketOpened)
    {
        print("Socked allready created");
        return;
    }

    mUnixFileDescriptor = socket(mConfig.domain, mConfig.type, mConfig.protocol);
    if (mUnixFileDescriptor == invalidFd)
    {
        throw SSLExceptions(__func__, "Error can't create Socket");
    }
}
void SSLConnection::send(Data msg)
{
    std::string buffor(msg.dump());
    print("Send: "+buffor);
    auto len = SSL_write(mSSL, buffor.data(), buffor.size());
    if (len < 0)
    {
        reportError(len);
    }
}
void SSLConnection::reportError(int len)
{
    int err = SSL_get_error(mSSL, len);
    switch (err)
    {
    case SSL_ERROR_WANT_WRITE:
        throw SSLExceptions(__func__, "Error can't send msg error code" + std::to_string(SSL_ERROR_WANT_WRITE));
    case SSL_ERROR_WANT_READ:
        throw SSLExceptions(__func__, "Error can't send msg error code" + std::to_string(SSL_ERROR_WANT_READ));
    case SSL_ERROR_ZERO_RETURN:
    case SSL_ERROR_SYSCALL:
    case SSL_ERROR_SSL:
    default:
        throw SSLExceptions(__func__, "Error can't send msg error something else");
    }
}
  std::vector<uint8_t> SSLConnection::recive()
{
    auto                 initBufferSize = 1000000;
    std::vector<uint8_t> buffor(initBufferSize);

    auto len = SSL_read(mSSL, static_cast<void*>(buffor.data()), buffor.size());
    buffor.resize(len);

    return buffor;
}

void SSLConnection::connectSSLSocket()
{
    SSL_library_init();
    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();
    SSL_METHOD* meth = const_cast<SSL_METHOD*>(TLSv1_2_client_method());
    SSL_CTX*    ctx  = SSL_CTX_new(meth);
    mSSL             = SSL_new(ctx);

    if (mSSL == nullptr)
        throw SSLExceptions(__func__, "Configuring SSL connection faild");

    mSSLFileDescriptor = SSL_get_fd(mSSL);
    SSL_set_fd(mSSL, mUnixFileDescriptor);
    if (SSL_connect(mSSL) <= 0)
    {
        throw SSLExceptions(__func__, "Cant connect SSL");
    }
}

void SSLConnection::setNonBlocking()
{
    if (fcntl(mUnixFileDescriptor, F_SETFL, O_NONBLOCK) == -1)
    {
        throw SSLExceptions(__func__, "Can set file descriptor as nonblocking");
    }
}
void SSLConnection::closeSocket()
{
    if (mUnixFileDescriptor != invalidFd)
    {
        close(mUnixFileDescriptor);
        mUnixFileDescriptor = invalidFd;
    }
}

