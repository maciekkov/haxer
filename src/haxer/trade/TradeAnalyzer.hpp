#pragma once

#include <vector>
#include <messages/GetChartLastRequest.hpp>

enum class Direction
{
    UP,
    DOWN
};

enum class MomentumCandle
{
    Yes,
    No
};
struct TrackingParameters
{
    float high{};
    float low{};
    float open{};
    float close{};

    MomentumCandle momo;
    Direction      trend;
};

class TradeAnalyzer
{
public:
    TradeAnalyzer();

    void detecting(const std::vector<GetChartLastRequest::Response::returnData::rateInfos>& chart)
    {
        for (const auto candle : chart)
        {
            tracker.high  = candle.high;
            tracker.low   = candle.low;
            tracker.open  = candle.open;
            tracker.close = candle.close;
            tracker.momo  = candle.close < candle.open ? MomentumCandle::Yes : MomentumCandle::No;
        }
    }

private:
    TrackingParameters tracker;
};
