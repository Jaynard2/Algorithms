#include "MakeChange.h"
#include <iterator>
#include <algorithm>
#include <exception>
/*********************************************************
* Summary: The bottom up implementation for counting coins.
*
* Author: Nathanael Cook
* Created: Oct 2021
* 
* Finds the Number of Coins from 2 up to the larges number given in the problem array.
* After the largest is found then all the rest of the problems given are looked up in the coinpuse
* which contains the already calculated values.
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

std::vector<ResultStruct> bottomup(std::vector<int>& denominations, std::vector<int>& problems) {
    //calculate the largest problem needing to be solved
    int max = *std::max_element(problems.begin(), problems.end());
    std::vector<int>::iterator currentProblem = problems.begin();
    std::vector<CoinUnit> coinPurse(max + 1);
    //preset the intial values
    coinPurse.at(0) = { 0,0 };
    coinPurse.at(1) = { 1,1 };
    //loop through every size upto and including the largest problem
    for (int i = 2; i <= max; i++) {
        //preset current values for intial comarison
        coinPurse.at(i) = { i + 1, i + 1 };
        std::vector<int>::iterator obj = denominations.begin();
        //walk through each denomiation calulating what is the best outcome
        while (obj != denominations.end()) {
            //get the index that the denomiation would subtract to from the current number
            int subp = i - *obj;
            //if the removal of the given denomiation is out of bounds or takes more coins then the current solution if is not entered
            if (subp >= 0 && coinPurse.at(i).count > 1 + coinPurse.at(subp).count) {
                coinPurse.at(i).count = 1 + coinPurse.at(subp).count;
                coinPurse.at(i).lastCoin = *obj;
            }
            obj++;
        }
    }
    //search through the results to find the specific solution for each problem
    std::vector<ResultStruct> result(problems.size());
    for (int i = 0; currentProblem != problems.end(); i++) {
        //storage struct for returning results
        ResultStruct subResult;
        int index = *currentProblem;
        //load the problem being solved and the saved number of coins
        subResult.problem = index;
        subResult.count = coinPurse.at(index).count;

        //walk the path back to zero to get the denomiation of coins used
        auto obj = denominations.begin();
        //preset the map to not have an if statement in the next loop
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