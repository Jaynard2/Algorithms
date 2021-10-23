#include "GalexyTester.h"

void GalaxyTester::initTest(uint32_t n, uint32_t m, uint32_t k) {
	_GM.reset();
	_GM.create(n, m, k);
}

void GalaxyTester::AddEvent(std::vector<int> evt) {
	for (int i = 1; i < evt.size(); i++) {
		evt[i - 1] = evt[i];
	}
	evt.erase(--evt.end());
	_Timeline.push(evt);
	_GM.addKingdom(_Timeline.size() + 'A', evt);
}

bool GalaxyTester::Test() {
	_GM.createSets();
	_result.push_back(0);


	if (_GM.countKingdomOccurences(0) > 1) {
		_result.back() += 1;
	}
	return true;
}