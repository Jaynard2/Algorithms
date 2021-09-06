#pragma once
#include <chrono>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "ThreadManager.h"
#include "CSVWriter.h"

unsigned constexpr amountToTest = 6;

struct TimeCompleted
{
	std::chrono::duration<float> sorted;
	std::chrono::duration<float> unsorted;
	std::chrono::duration<float> revSorted;
	unsigned int iteration;
};

std::ostream& operator<<(std::ostream& out, const TimeCompleted& rhs);

class SortTester
{
public:
	SortTester(unsigned int dataSize, unsigned int start, unsigned int step, ThreadManager *threads);
	
	void addFunction(std::string name, std::function<void(std::list<int>&)> func);

	void startTest();
	bool writeToFile();

	const std::map<std::string, TimeCompleted>& getResults() const { return _times; }
	const std::vector<std::pair<std::string, std::uint32_t>>& getBadSorts() const { return _badSorts; }

private:
	std::map<std::string, std::function<void(std::list<int>&)>> _sortFuncs;
	std::vector<int> _testData;
	std::vector<int> _sortedData;
	std::vector<int> _reverseSortedData;
	unsigned int _testLength;
	unsigned int _testStartIndex;
	unsigned int _step;
	ThreadManager* _threadManager;

	std::map<std::string, TimeCompleted> _times;
	std::mutex _badSort_lock;
	std::vector<std::pair<std::string, std::uint32_t>> _badSorts;

};
