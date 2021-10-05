#pragma once
#include <vector>
#include <string>
#include "ResultStruct.h"

struct CoinUnit
{
    int count;
    int lastCoin;
};

std::vector<ResultStruct> bottomup(std::vector<int>& denominations, std::vector<int>& problems);

std::vector<ResultStruct> recursive(const std::vector<int>& denominations, const std::vector<int>& problems);

void solveIndex(const std::vector<int>& denominations, ResultStruct& solution);
