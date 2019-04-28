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
        int exemode;
        struct rateInfos
        {
            int64_t     ctm;
            std::string ctmString;
            float       close;
            float       high;
            float       low;
            float       open;
            float       vol;
        };
        std::vector<rateInfos> rates;
    };

    returnData ret;
    bool       status;

    friend void from_json(const nlohmann::json& j, Response& p)
    {
        j.at("status").get_to(p.status);
        for (auto x : j["returnData"]["rateInfos"])
        {
            p.ret.rates.emplace_back<Response::returnData::rateInfos>
                    (
{
                     x.at("ctm").get<int64_t>() ,
                     x.at("ctmString").get<std::string>() ,
                     x.at("open").get<float>() ,
                     x.at("close").get<float>() ,
                     x.at("high").get<float>() ,
                     x.at("low").get<float>() ,
                     x.at("vol").get<float>()
}
                     );
        }
    }
};

} // namespace GetChartLastRequest
