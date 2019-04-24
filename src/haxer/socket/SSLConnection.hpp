#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include <arpa/inet.h>
#include <stdint.h>

#include <vector>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <json.hpp>

namespace {

constexpr int invalidFd = -1;

} // unnamed namespace
using json =  nlohmann::json;

class SSLConnection
{
public:
    SSLConnection(const uint_least16_t port, const std::string& ip);

    void                 send();
    std::vector<uint8_t> recive();

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
    void config(const uint16_t port, const std::string& ip);
    void connectSocket();
    void connectToServer();
    void openSocket();
    void connectSSLSocket();
    void setNonBlocking();
    void closeSocket();
    void setSockAddress(uint32_t ip, uint16_t port, sockaddr_in& sockAddress);
    void getIpAndPort(uint32_t& ip, uint16_t& port, const sockaddr_in& sockAddress);

    struct SSLConfiguration
    {
        int         domain;
        int         type;
        int         protocol;
        uint32_t    ip;
        uint16_t    port;
        sockaddr_in address;
    };

    int              mUnixFileDescriptor;
    int              mSSLFileDescriptor;
    SSLConfiguration mConfig;
    SSL*             mSSL;
};
