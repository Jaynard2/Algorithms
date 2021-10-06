#include "MemoizationSolver.h"
#include <algorithm>
/*********************************************************
* Summary: Definition for MemoizationSolver
*
* Author: Joshua Grieve
* Created: Oct 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/
#ifndef INT_MAX
    #define INT_MAX 2147483647
#endif

std::vector<ResultStruct> MemoizationSolver::operator()(const std::vector<int>& denoms, const std::vector<int>& problems)
{
    std::vector<ResultStruct> solutions;

    const auto& max = std::max_element(problems.begin(), problems.end());
    _results.resize(*max);
    for (auto& i : _results)
    {
        i.problem = -1;
        i.count = -1;
    }

    for (const auto& i : problems)
    {
        ResultStruct result;
        result.problem = i;

        solveIndexWithMemory(denoms, result);
        solutions.push_back(result);
    }

    return solutions;
}

void MemoizationSolver::solveIndexWithMemory(const std::vector<int> denoms, ResultStruct& result)
{
    ResultStruct bestSol;
    bestSol.count = INT_MAX;
    for (const auto& i : denoms)
    {
        if (i == result.problem)
        {
            result.coins.insert({ i, 1 });
            result.count = 1;

            return;
        }

        ResultStruct temp;
        temp.problem = result.problem - i;
        temp.count = INT_MAX;

        if (temp.problem > 0)
        {
            if (_results[temp.problem - 1].problem != -1)
                temp = _results[temp.problem - 1];
            else
                solveIndexWithMemory(denoms, temp);
        }

        if (temp.count < bestSol.count)
        {
            bestSol = temp;
            bestSol.problem += i;

            if (bestSol.coins.find(i) != bestSol.coins.end())
            {
                bestSol.coins.at(i) += 1;
                bestSol.count += 1;
            }
            else
            {
                bestSol.coins.insert({ i, 1 });
                bestSol.count += 1;
            }
        }
    }

    _results[bestSol.problem - 1] = bestSol;
    result = bestSol;
}
