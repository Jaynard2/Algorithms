#pragma once
#include <map>

struct ResultStruct {
	int problem;
	int count;
	std::map<int, int> coins;
};