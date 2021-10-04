#pragma once
#include <iostream>

struct CoinUnit
{
    int count;
    int lastCoin;
};

std::ostream& operator<<(std::ostream& out, const CoinUnit& coin);
