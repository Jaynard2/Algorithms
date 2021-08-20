#pragma once
#include <list>
#include <chrono>
#include <functional>
#include <string>
#include <map>

unsigned constexpr amountToTest = 6;

struct TimeCompleted
{
	std::chrono::duration<double> sorted;
	std::chrono::duration<double> unsorted;
	std::chrono::duration<double> revSorted;
};

class SortTester
{
public:
	SortTester(unsigned long dataSize);
	
	void addFunction(std::string name, std::function<void(std::list<int>&)> func);

	bool startTest();

private:
	unsigned _testAmount = 0;

	std::map<std::string, std::function<void(std::list<int>&)>> _sortFuncs;
	std::list<int> _testData;
	std::list<int> _sortedData;
	std::list<int> _reverseSortedData;

	std::map<std::string, TimeCompleted> _times;
};
