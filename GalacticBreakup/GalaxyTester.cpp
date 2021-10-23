#include "GalexyTester.h"

/*********************************************************
* Summary: The bottom up implementation for counting coins.
*
* Author: Nathanael Cook
* Created: Oct 2021
*
* Hold the stack of the and the galaxy map. Then runs the test for a single given
* problem class must be reset for the next problem. 
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/

void GalaxyTester::initTest(uint32_t n, uint32_t m, uint32_t k) {
	//Reset structures and resize the cube for the next test
	_GM.reset();
	_GM.create(n, m, k);
}

void GalaxyTester::AddEvent(std::vector<int> evt) {
	//removes the first integer, which is the length of the array
	for (int i = 1; i < evt.size(); i++) {
		evt[i - 1] = evt[i];
	}
	evt.erase(--evt.end());
	//store a representative to the kingdom
	_Timeline.push(evt[0]);
	//pass the kingdom to the galaxy map for initalization
	_GM.addKingdom(evt);
}

bool GalaxyTester::Test() {
	//intialize map for test
	_GM.createEmpireSets();
	_result.push_back((int)(!_GM.empireConncted()));

	while (_Timeline.size() > 0) {
		//walking in reverse order, this addes the kingdom back to the empire
		_GM.mergeKingdom(_Timeline.top());
		_Timeline.pop();

		//Check if the empire is split
		if (!_GM.empireConncted()) {
			_result.back() += 1;
		}
	}
	return true;
}