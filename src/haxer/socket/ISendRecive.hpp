#pragma once
#include <cstdint>
#include <vector>

template <typename Message>
class ISendRecive
{
public:
    using Data              = Message;

    virtual void send(Data) = 0;
    virtual  std::vector<uint8_t> recive()   = 0;
};
