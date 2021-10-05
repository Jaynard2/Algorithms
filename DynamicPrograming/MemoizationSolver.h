#pragma once
#include <vector>
#include "ResultStruct.h"

class MemoizationSolver
{
public:
	std::vector<ResultStruct> operator()(const std::vector<int>& denoms, const std::vector<int>& problems);

private:
	void solveIndexWithMemory(const std::vector<int> denoms, ResultStruct& result);

	std::vector<ResultStruct> _results;
};

