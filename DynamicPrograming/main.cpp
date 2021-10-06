/*********************************************************
* Summary: Entry point of the program. Reads in user input for denominations
* and problems and starts the different algorithms.
*
* Author: Nathanael Cook
* Created: Oct 2021
* 
* Running the test and handle all io, so taking in the parameters and printing the results of the tests
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
    //this is called after the size has been given it reads in all the values into the buffer
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
    //this is called to get the intial size of each vector. 
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
    // all test return a vector of Result Structs this function the reads the valeus and prints them out
    // also sorting through the empty values that were not used
    for (const auto& i : testResults) {
        std::cout << i.problem << " cents =";
        auto iter = denominations.rbegin();
        // loops thought for number of each denomitation used
        while (iter != denominations.rend()) {
            //checks if coin was used in test or it the coin was initalozed but then not used
            if (i.coins.find(*iter) != i.coins.end() && i.coins.at(*iter) != 0) {
                std::cout << " " << * iter << ":" << i.coins.at(*iter);
            }
            iter++;
        }
        std::cout << std::endl;
    }
}
