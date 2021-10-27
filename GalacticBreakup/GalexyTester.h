#pragma once
#include <stack>
#include <vector>
#include "GalaxyMap.h"

/*********************************************************
* Summary: The bottom up implementation for counting coins.
*
* Author: Nathanael Cook
* Created: Oct 2021
*
* Class for holding the Galaxy map and Timeline of succession
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

class GalaxyTester {
public:
	GalaxyTester() : _Timeline(), _GM() {	}
	void initTest(uint32_t n, uint32_t m, uint32_t k);
	void AddEvent(std::vector<int> evt);
	bool Test();
	std::vector<int> getResult() { return _result; }
private:
	std::stack<std::vector<int>> _Timeline;
	GalaxyMap _GM;
	std::vector<int> _result;
};