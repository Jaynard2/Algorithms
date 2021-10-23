#pragma once
#include <stack>
#include <vector>
#include "GalaxyMap.h"

class GalaxyTester {
public:
	GalaxyTester() : _Timeline(), _GM() {	}
	void initTest(uint32_t n, uint32_t m, uint32_t k);
	void AddEvent(std::vector<int> evt);
	int Test();
private:
	std::stack<std::vector<int>> _Timeline;
	GalaxyMap _GM;
};