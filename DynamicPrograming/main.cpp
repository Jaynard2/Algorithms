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
void printResults(const std::vector<CoinUnit>& purse);

std::vector<CoinUnit> bottomup(std::vector<int>& denomiations, std::vector<int>& problems);

std::map<int, std::vector<int>> recursive(std::vector<int>& denominations, std::vector<int>& problems);
void solveIndex(std::vector<int>& denomiations, int value, std::vector<int>& solution);

int main() {
    std::vector<int> denomiations = {1, 5, 10, 25};
    std::vector<int> problems(0);

    /*sizeVector(denomiations, "DENOMIATION INPUT ");

    do
    {
        //populate the Denomiations Vector
        fillVector(denomiations, "Denomination input ");
        std::sort(denomiations.begin(), denomiations.end());
    } while (denomiations[0] != 1);
    */
    //Get the number of problems
    sizeVector(problems, "NUMBER OF PROBLEMS ");

    //populate the problems Vector
    fillVector(problems, "Problem Input ");

    std::sort(problems.begin(), problems.end());

    const auto dynamicPurse = bottomup(denomiations, problems);
    //const auto dynamicPurse = recursive(denomiations, problems);

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
std::vector<CoinUnit> bottomup(std::vector<int>& denomiations, std::vector<int>& problems) {
    std::vector<int>::iterator currentProblem = problems.begin();
    std::vector<CoinUnit> coinPurse(*problems.rbegin());
    coinPurse.at(0) = { 1,1 };
    coinPurse.at(1) = { 1,1 };

    for (int i = 2; i < *problems.rbegin(); i++) {
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
            subResult.coins.insert(*obj, 0);
            obj++;
        }
        while (index > 0) {
            int coin = coinPurse.at(index).lastCoin;
            subResult.coins.at(coin) = subResult.coins.at(coin) + 1;
            index -= coin;
        }
        currentProblem++;
    }
    return coinPurse;
}

std::map<int, std::vector<int>> recursive(std::vector<int>& denominations, std::vector<int>& problems) 
{
    std::map<int, std::vector<int>> solutions;

    for (const auto& i : problems)
    {
        std::pair<int, std::vector<int>> probSolution;
        probSolution.first = i;
        solveIndex(denominations, i, probSolution.second);

        solutions.insert(probSolution);
   }

    return solutions;
}

void solveIndex(std::vector<int>& denomiations, int value, std::vector<int>& solution) 
{
    if (value < 1)
    {
        return;
    }

    int best = INT_MAX;
    for (const auto& i : denomiations)
    {
        if (i == value)
        {
            solution.push_back(i);
            return;
        }

        std::vector<int> temp;
        solveIndex(denomiations, value - i, temp);

        if (temp.size() < best && !temp.empty())
        {
            solution = temp;
            solution.push_back(i);

            best = temp.size();
        }
    }
    
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
        std::cout << i.problem << "cents ";
        auto iter = denominations.begin();
        while (iter != denominations.end()) {
            std::cout << *iter << ":" << i.coins.at(*iter);
        }
        std::cout << std::endl;
    }
}
