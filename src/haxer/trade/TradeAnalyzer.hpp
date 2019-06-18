#pragma once

#include <vector>
#include "Common.hpp"
#include <messages/GetChartLastRequest.hpp>

enum class TrenDirection
{
    UpTrend,
    DownTrend
};

enum class Momomentum
{
    NotDetected,
    Yes,
    No
};

class Trend
{
public:
    virtual bool isProcessing();
};

template <typename Data>
class Analyzer
{
public:
    void detecting(const Data& data) = 0;
    void transferDetectedPattern()   = 0;
};

struct TrendDetails
{
    Candle High;
    Candle Low;
    Candle Open;
    Candle Close;

    TrenDirection trend;
};
using rateInfos = GetChartLastRequest::Response::returnData::rateInfos;

class TradeAnalyzer : public Analyzer < std::vector<rateInfos>
{
public:
    TradeAnalyzer();

    void detecting(const std::vector<rateInfos>& chart);
    void chartProcessing();


private:
    std::vector<Observer> chartWatchers;

};
