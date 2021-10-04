#include "MemoizationSolver.h"

void MemoizationSolver::operator()(const std::vector<int>& denoms, const std::vector<int>& problems)
{
    std::vector<ResultStruct> solutions;

    for (const auto& i : problems)
    {
        ResultStruct result;
        result.problem = i;

        solveIndexWithMemory(denoms, result);
        solutions.push_back(result);
    }

    return solutions;
}
