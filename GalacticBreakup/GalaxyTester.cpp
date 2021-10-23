#include "GalexyTester.h"

void GalaxyTester::initTest(uint32_t n, uint32_t m, uint32_t k) {
	_GM.reset();
	_GM.create(n, m, k);
}

void GalaxyTester::AddEvent(std::vector<int> evt) {
	_Timeline.push(evt);
}

int GalaxyTester::Test() {

}