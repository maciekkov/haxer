#pragma once
#include <json.hpp>

namespace Login {
struct Request
{
    struct arguments
    {
        int         userId;
        std::string password;
    };

    std::string command;
    arguments   args;

    friend void to_json(nlohmann::json& j, const Request& p)
    {
        nlohmann::json local;
        local["command"]               = p.command;
        local["arguments"]["userId"]   = p.args.userId;
        local["arguments"]["password"] = p.args.password;
        j                              = local;
    }
};
struct Response
{
    bool        status;
    std::string streamSessionId;

    friend void from_json(const nlohmann::json& j, Response& p)
    {
        j.at("status").get_to(p.status);
        j.at("streamSessionId").get_to(p.streamSessionId);
    }
};
} // namespace Login
