#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include <arpa/inet.h>
#include <stdint.h>

#include <openssl/err.h>
#include <openssl/ssl.h>
namespace {

constexpr int invalidFd = -1;

} // unnamed namespace

class SSLConnection
{
public:
    SSLConnection(const uint_least16_t port, const std::string& ip);

    int getFd();

    class SSLExceptions : public std::runtime_error
    {
    public:
        SocketException(const std::string& method, const std::string& err)
            : std::runtime_error("Socket Exception: failed to " + method + ": " + err)
        {
        }
    };

private:
    void config(const uint_least16_t port, const std::string& ip);
    void connectSocket();
    void openSocket();
    void bindSocket();
    void connectSSLSocket();
    void setNonBlocking();
    void closeSocket();
    void setSockAddress(uint_least32_t ip, uint_least16_t port, sockaddr_in& sockAddress);
    void getIpAndPort(uint_least32_t& ip, uint_least16_t& port, const sockaddr_in& sockAddress);

    struct SSLConfiguration
    {
        int            domain;
        int            type;
        int            protocol;
        uint_least32_t ip;
        uint_least16_t port;
        sockaddr_in    address;
    };

    int              mUnixFileDescriptor;
    int              mSSLFileDescriptor;
    SSLConfiguration mConfig;
    SSL*             ssl;
};
