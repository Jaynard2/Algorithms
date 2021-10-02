#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <iterator>
#include <algorithm>

struct CoinUnit {
    int cout;
    int lastCoin;
};

void fillVector(std::vector<int>* vec, std::string type);
void sizeVector(std::vector<int>* vec, std::string type);
void bottomup(std::vector<int>* denomiations, std::vector<int>* problems);

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

void bottomup(std::vector<int>* denomiations, std::vector<int>* problems) {
    std::vector<int>::reverse_iterator currentProblem = problems->rbegin();
    std::vector<CoinUnit> coinPurse(*problems->rbegin());
    while (currentProblem != problems->rend()) {
        for (int i = 0; i < *currentProblem; i++) {

        }

    }
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