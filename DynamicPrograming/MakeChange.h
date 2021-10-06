#pragma once
#include <vector>
#include <string>
#include "ResultStruct.h"
/*********************************************************
* Summary: Common file for declaring function signitures. 
* Makes working with Gradel easier.
*
* Author: Nathan Cook
* Created: Oct 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

struct CoinUnit
{
    int count;
    int lastCoin;
};

std::vector<ResultStruct> bottomup(std::vector<int>& denominations, std::vector<int>& problems);

std::vector<ResultStruct> recursive(const std::vector<int>& denominations, const std::vector<int>& problems);

void solveIndex(const std::vector<int>& denominations, ResultStruct& solution);
