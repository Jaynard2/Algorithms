#include "MakeChange.h"
#include <iterator>
#include <algorithm>
#include <exception>

std::vector<ResultStruct> bottomup(std::vector<int>& denominations, std::vector<int>& problems) {
    int max = *std::max_element(problems.begin(), problems.end());
    std::vector<int>::iterator currentProblem = problems.begin();
    std::vector<CoinUnit> coinPurse(max + 1);
    coinPurse.at(0) = { 0,0 };
    coinPurse.at(1) = { 1,1 };
    for (int i = 2; i <= max; i++) {
        coinPurse.at(i) = { i + 1, i + 1 };
        std::vector<int>::reverse_iterator obj = denominations.rbegin();
        while (obj != denominations.rend()) {
            int subp = i - *obj;
            if (subp >= 0 && coinPurse.at(i).count > 1 + coinPurse.at(subp).count) {
                coinPurse.at(i).count = 1 + coinPurse.at(subp).count;
                coinPurse.at(i).lastCoin = *obj;
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

        auto obj = denominations.begin();
        while (obj != denominations.end()) {
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