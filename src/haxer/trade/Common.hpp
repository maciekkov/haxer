#pragma once


enum class CandleColor
{
    Bearish,
    Bullish
};

class Candle
{
    float high;
    float low;
    float open;
    float close;

    CandleColor color;
};
