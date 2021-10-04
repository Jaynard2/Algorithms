#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include "CoinUnit.h"
#include "ResultStruct.h"

void fillVector(std::vector<int>& vec, std::string type);
void sizeVector(std::vector<int>& vec, std::string type);
void printResults(const std::vector<ResultStruct>& testResults, std::vector<int> denominations);

std::vector<ResultStruct> bottomup(std::vector<int>& denomiations, std::vector<int>& problems);

std::vector<ResultStruct> recursive(const std::vector<int>& denominations, const std::vector<int>& problems);
void solveIndex(const std::vector<int>& denomiations, ResultStruct& solution);

int main() {
    std::vector<int> denomiations(0);
    std::vector<int> problems(0);

    sizeVector(denomiations, "DENOMIATION INPUT ");

    do
    {
        //populate the Denomiations Vector
        fillVector(denomiations, "Denomination input ");
        std::sort(denomiations.begin(), denomiations.end());
    } while (denomiations[0] != 1);
    
    //Get the number of problems
    sizeVector(problems, "NUMBER OF PROBLEMS ");

    //populate the problems Vector
    fillVector(problems, "Problem Input ");

    std::sort(problems.begin(), problems.end());

    const auto dynamicPurse = bottomup(denomiations, problems);
    const auto recursivePurse = recursive(denomiations, problems);

    printResults(dynamicPurse, denomiations);
    printResults(recursivePurse, denomiations);

}

/*
* Found bug where it enters infite loop. Try folloing inputs
* DENOMINATIONS: 3
* 2, 7, 24
* NUMBER OF PROBLEMS: 5
* 2, 5, 24, 56, 4
* 
* Appears to get stuck on case 56 when checks for a solution with coin 24
*/
std::vector<ResultStruct> bottomup(std::vector<int>& denomiations, std::vector<int>& problems) {
    std::vector<int>::iterator currentProblem = problems.begin();
    std::vector<CoinUnit> coinPurse(*(problems.rbegin()) + 1);
    coinPurse.at(0) = { 0,0 };
    coinPurse.at(1) = { 1,1 };

    for (int i = 2; i <= *problems.rbegin(); i++) {
        coinPurse.at(i) = { i + 1, i + 1 };
        std::vector<int>::reverse_iterator obj = denomiations.rbegin();
        while (obj != denomiations.rend()) {
            int subp = i - *obj;
            if (subp >= 0 && coinPurse.at(i).count > 1 + coinPurse.at(subp).count) {
                coinPurse.at(i).count = 1 + coinPurse.at(subp).count;
                coinPurse.at(i).lastCoin = *obj;
                break;
            }
            obj++;
        }
    }
    std::vector<ResultStruct> result(problems.size());
    for (int i = 0; currentProblem != problems.end(); i++) {
        ResultStruct subResult;
        int index = *currentProblem;
        subResult.problem = index;
        subResult.count = coinPurse.at(index).count;

        auto obj = denomiations.begin();
        while (obj != denomiations.end()) {
            subResult.coins.insert({ *obj, 0 });
            obj++;
        }
        while (index > 0) {
            int coin = coinPurse.at(index).lastCoin;
            subResult.coins.at(coin) = subResult.coins.at(coin) + 1;
            index -= coin;
        }
        result.at(i) = subResult;
        currentProblem++;
    }
    return result;
}

std::vector<ResultStruct> recursive(const std::vector<int>& denominations, const std::vector<int>& problems) 
{
    std::vector<ResultStruct> solutions;

    for (const auto& i : problems)
    {
        ResultStruct result;
        result.problem = i;

        solveIndex(denominations, result);
        solutions.push_back(result);
   }

    return solutions;
}

void solveIndex(const std::vector<int>& denomiations, ResultStruct& solution)
{
    if (solution.problem < 1)
    {
        solution.count = INT_MAX;
        return;
    }

    int best = INT_MAX;
    ResultStruct bestSol;
    for (const auto& i : denomiations)
    {
        if (i == solution.problem)
        {
            solution.coins.insert({ i, 1 });
            solution.count = 1;

            return;
        }

        ResultStruct temp;
        temp.problem = solution.problem - i;

        solveIndex(denomiations, temp);

        if (temp.count < best)
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

            best = bestSol.count;
        }
    }

    solution = bestSol;
    
}

void fillVector(std::vector<int>& vec, std::string type) {

    std::cout << type << std::endl;

    std::string buffer = "";
    for (int i = 0; i < vec.size(); i++) {
        try {
            buffer.clear();
            std::getline(std::cin, buffer);
            vec.at(i) = std::stoi(buffer);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << type << i << "is not a Number" << std::endl;
        }
    }
}

void sizeVector(std::vector<int>& vec, std::string type) {

    std::cout << type << std::endl;

    std::string buffer = "";
    int temp = 0;
    std::getline(std::cin, buffer);
    try {
        temp = std::stoi(buffer);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << type << "parmeter is not a Number" << std::endl;
    }
    vec.resize(temp);
}

void printResults(const std::vector<ResultStruct>& testResults, std::vector<int> denominations) {
    for (const auto& i : testResults) {
        std::cout << i.problem << " cents = ";
        auto iter = denominations.rbegin();
        while (iter != denominations.rend()) {
            if (i.coins.find(*iter) != i.coins.end() && i.coins.at(*iter) != 0) {
                std::cout << *iter << ":" << i.coins.at(*iter) << " ";
            }
            iter++;
        }
        std::cout << std::endl;
    }
}
