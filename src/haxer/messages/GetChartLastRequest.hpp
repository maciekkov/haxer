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
            Response::returnData::rateInfos temp;

            x.at("ctm").get_to(temp.ctm);
            x.at("ctmString").get_to(temp.ctmString);
            x.at("open").get_to(temp.open);
            x.at("close").get_to(temp.close);
            x.at("high").get_to(temp.high);
            x.at("low").get_to(temp.low);
            x.at("vol").get_to(temp.vol);

            p.ret.rates.push_back(temp);
        }
    }
};
} // namespace GetChartLastRequest
