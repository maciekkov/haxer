#pragma once
#include <string>
#include <json.hpp>

namespace GetChartLastRequest {

struct Request
{
    struct arguments
    {
        struct info
        {
            int         period;
            int64_t     start;
            std::string symbol;
        } inf;
    };

    std::string command;
    arguments   args;

    friend void to_json(nlohmann::json& j, const Request& p)
    {
        nlohmann::json local;
        local["command"]                     = p.command;
        local["arguments"]["info"]["period"] = p.args.inf.period;
        local["arguments"]["info"]["start"]  = p.args.inf.start;
        local["arguments"]["info"]["symbol"] = p.args.inf.symbol;
        j                                    = local;
    }
};

struct Response
{

    struct returnData
    {
        int digits;
        struct rateInfos
        {
            float       close;
            int64_t     ctm;
            std::string ctmString;
            float       high;
            float       low;
            float       open;
            float       vol;
        };
        std::vector<rateInfos> rates{1000000};
    };

    bool status;
    returnData ret;


    friend void from_json(const nlohmann::json& j, Response& p)
    {
//        j.at("status").get_to(p.status);
//        j.at("returnData").get_to(p.ret.digits); ?????
    }
};

} // namespace GetChartLastRequest
