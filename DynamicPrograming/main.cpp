#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <iterator>
#include <algorithm>

struct CoinUnit {
    int count;
    int lastCoin;
};

void fillVector(std::vector<int>* vec, std::string type);
void sizeVector(std::vector<int>* vec, std::string type);
std::vector<CoinUnit> bottomup(std::vector<int>* denomiations, std::vector<int>* problems);
std::vector<CoinUnit> Recursive(std::vector<int>* denominations, std::vector<int>* problems);
CoinUnit solveIndex(std::vector<int>* denomiations, int value);

int main() {
    std::vector<int>* denomiations = nullptr;
    std::vector<int>* problems = nullptr;

    sizeVector(denomiations, "DENOMIATION INPUT ");

        //populate the Denomiations Vector
    fillVector(denomiations, "Denomination input ");

    //Get the number of problems
    sizeVector(problems, "NUMBER OR PROBLEMS ");

    //populate the problems Vector
    fillVector(problems, "Problem Input ");

    std::sort(problems->begin(), problems->end());



    delete denomiations;
    delete problems;
}

std::vector<CoinUnit> bottomup(std::vector<int>* denomiations, std::vector<int>* problems) {
    std::vector<int>::reverse_iterator currentProblem = problems->rbegin();
    int lastcalcuated = 1;
    std::vector<CoinUnit> coinPurse(*problems->rbegin());
    coinPurse.at(1) = {1,1};
    while (currentProblem != problems->rend()) {
        for (int i = lastcalcuated + 1; i < *currentProblem; i++) {
            coinPurse.at(i) = { i + 1, i + 1 };
            std::vector<int>::reverse_iterator obj = denomiations->rbegin();
            while (obj != denomiations->rend()) {
                int subp = *currentProblem - *obj;
                if (subp >= 0 && coinPurse.at(i).count > 1 + coinPurse.at(subp).count) {
                    coinPurse.at(i).count = 1 + coinPurse.at(subp).count;
                    coinPurse.at(i).lastCoin = *obj;
                }
            }
            lastcalcuated++;
        }
        currentProblem++;
    }
    return coinPurse;
}

std::vector<CoinUnit> Recursive(std::vector<int>* denominations, std::vector<int>* problems) {
    std::vector<CoinUnit> coinpurse(problems->size());
    for(int i = 0; i < problems->size(); i++){
        coinpurse.at(i) = solveIndex(denominations, problems->at(i));
    }
    return coinpurse;
}

CoinUnit solveIndex(std::vector<int>* denomiations, int value) {
    if (value == 1) {
        return CoinUnit{1,1};
    }
    CoinUnit best = { 2000000, 2000000 };
    std::vector<int>::iterator currentdenom = denomiations->begin();
    while (currentdenom != denomiations->end()) {
        CoinUnit temp = solveIndex(denomiations, value - *currentdenom);
        if (best.count > temp.count) {
            best.count = temp.count + 1;
            best.lastCoin = *currentdenom;
        }
    }
    return best;
}

void fillVector(std::vector<int>* vec, std::string type) {
    std::string buffer = "";
    for (int i = 0; i < vec->size(); i++) {
        try {
            buffer.clear();
            std::getline(std::cin, buffer);
            vec->at(i) = std::stoi(buffer, nullptr, buffer.length());
        }
        catch (const std::invalid_argument& e) {
            std::cout << type << i << "is not a Number" << std::endl;
        }
    }
}

void sizeVector(std::vector<int>* vec, std::string type) {
    std::string buffer = "";
    int temp = 0;
    std::getline(std::cin, buffer);
    try {
        temp = std::stoi(buffer, nullptr, buffer.length());
    }
    catch (const std::invalid_argument& e) {
        std::cout << type << "parmeter is not a Number" << std::endl;
    }
    vec = new std::vector<int>(temp);
}