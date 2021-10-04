#include "CoinUnit.h"

std::ostream& operator<<(std::ostream& out, const CoinUnit& coin)
{
    std::cout << "(" << coin.count << ", " << coin.lastCoin << ")";
    return out;
}
