#pragma once
#include <vector>
#include "ResultStruct.h"
/*********************************************************
* Summary: Class decleration for the memoization solution for the coin counter.
*
* Author: Joshua Grieve
* Created: Oct 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

class MemoizationSolver
{
public:
	std::vector<ResultStruct> operator()(const std::vector<int>& denoms, const std::vector<int>& problems);

private:
	void solveIndexWithMemory(const std::vector<int> denoms, ResultStruct& result);

	std::vector<ResultStruct> _results;
};

