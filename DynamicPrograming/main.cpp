/*********************************************************
* Summary: Entry point of the program. Reads in user input for denominations
* and problems and starts the different algorithms.
*
* Author: Nathan Cook
* Created: Oct 2021
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include "MakeChange.h"
#include "MemoizationSolver.h"


void fillVector(std::vector<int>& vec, std::string type);
void sizeVector(std::vector<int>& vec, std::string type);
void printResults(const std::vector<ResultStruct>& testResults, std::vector<int> denominations);

int main() {
    std::vector<int> denominations(0);
    std::vector<int> problems(0);

    sizeVector(denominations, "DENOMINATION INPUT ");

    do {
        //populate the Denomiations Vector
        fillVector(denominations, "Denomination input ");
        std::sort(denominations.begin(), denominations.end());
    } while (denominations[0] != 1);
    
    //Get the number of problems
    sizeVector(problems, "NUMBER OF PROBLEMS ");

    //populate the problems Vector
    fillVector(problems, "Problem Input ");

    const auto dynamicPurse = bottomup(denominations, problems);
    printResults(dynamicPurse, denominations);

    const auto recursivePurse = recursive(denominations, problems);
    printResults(recursivePurse, denominations);

    const auto mPurse = MemoizationSolver()(denominations, problems);
    printResults(mPurse, denominations);

}

void fillVector(std::vector<int>& vec, std::string type) {
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
        std::cout << i.problem << " cents =";
        auto iter = denominations.rbegin();
        while (iter != denominations.rend()) {
            if (i.coins.find(*iter) != i.coins.end() && i.coins.at(*iter) != 0) {
                std::cout << " " << * iter << ":" << i.coins.at(*iter);
            }
            iter++;
        }
        std::cout << std::endl;
    }
}
