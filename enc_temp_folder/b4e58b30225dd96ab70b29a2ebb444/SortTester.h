#pragma once
#include <chrono>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "ThreadManager.h"

unsigned constexpr amountToTest = 6;

struct TimeCompleted
{
	std::chrono::duration<float> sorted;
	std::chrono::duration<float> unsorted;
	std::chrono::duration<float> revSorted;
	unsigned int iteration;
};

std::ostream& operator<<(std::ostream& out, const TimeCompleted& rhs);

template <typename T>
class SortTester
{
public:
	SortTester(unsigned int dataSize, unsigned int start, unsigned int step, ThreadManager *threads);
	
	void addFunction(std::string name, std::function<void(T&)> func);
	
	void startTest();

	const std::map<std::string, std::vector<TimeCompleted>>& getResults() const { return _times; }
	const std::vector<std::pair<std::string, std::uint32_t>>& getBadSorts() const { return _badSorts; }

private:
	bool isSorted(T& l);

	std::map<std::string, std::function<void(T&)>> _sortFuncs;
	std::vector<int> _testData;
	std::vector<int> _sortedData;
	unsigned int _testLength;
	unsigned int _testStartIndex;
	unsigned int _step;
	ThreadManager* _threadManager;

	std::map<std::string, std::vector<TimeCompleted>> _times;
	std::mutex _badSort_lock;
	std::vector<std::pair<std::string, std::uint32_t>> _badSorts;

};

#include "SortTester.cpp"
