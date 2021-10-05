#include "MakeChange.h"
#ifndef INT_MAX
    #define INT_MAX 2147483647
#endif

std::vector<ResultStruct> recursive(const std::vector<int>& denominations, const std::vector<int>& problems)
{
    std::vector<ResultStruct> solutions;

    for (const auto& i : problems)
    {
        if (i > 40)
        {
            break;
        }

        ResultStruct result;
        result.problem = i;

        solveIndex(denominations, result);
        solutions.push_back(result);
    }

    return solutions;
}

void solveIndex(const std::vector<int>& denominations, ResultStruct& solution)
{
    if (solution.problem < 1)
    {
        solution.count = INT_MAX;
        return;
    }

    ResultStruct bestSol;
    bestSol.count = INT_MAX;
    for (const auto& i : denominations)
    {
        if (i == solution.problem)
        {
            solution.coins.insert({ i, 1 });
            solution.count = 1;

            return;
        }

        ResultStruct temp;
        temp.problem = solution.problem - i;

        solveIndex(denominations, temp);

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

    solution = bestSol;

}