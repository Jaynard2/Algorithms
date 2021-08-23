#include "SortTester.h"
#include <algorithm>
#include <ctime>
#include <random>
#include <thread>
#include <exception>
#include <future>

SortTester::SortTester(unsigned dataSize) : _sortFuncs(), _times()
{
	//Make vectors large enough to hold all data
	_testData.resize(dataSize);
	_sortedData.resize(dataSize);
	_reverseSortedData.resize(dataSize);
	
	srand(time(NULL));

	//Generate random values for test data
	std::generate(_testData.begin(), _testData.end(), rand);
	
	//Create sorted data for comparison and sorted runs
	std::copy(_testData.begin(), _testData.end(), _sortedData.begin());
	_sortedData.sort();
	std::reverse_copy(_sortedData.begin(), _sortedData.end(), _reverseSortedData.begin());
}

void SortTester::addFunction(std::string name, std::function<void(std::list<int>&)> func)
{
	if (_sortFuncs.find(name) == _sortFuncs.end())
	{
		_sortFuncs.emplace(std::make_pair(name, func));
	}
}

bool SortTester::startTest()
{
	std::vector<std::future<bool>> threads;

	for (auto& i : _sortFuncs)
	{
		//pre-construct TimeCompleted to prevent race conditions
		_times.emplace(i.first, TimeCompleted());

		//Unsorted data----------------------------------------------------------------------
		threads.push_back
		(
			std::async
			(
				[&] 
				{
					std::list<int> dataCopy = _testData;

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					//Check that vakues are correctly sorted
					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
						_badSorts.push_back(i.first);
						return false;
					}

					_times.at(i.first).unsorted = end - start;
					return true;
				}
			)
		);
		//Sorted data-------------------------------------------------------------------------
		threads.push_back
		(
			std::async
			(
				[&] 
				{
					std::list<int> dataCopy = _testData;

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
						_badSorts.push_back(i.first);
						return false;
					}

					_times.at(i.first).sorted = end - start;
					return true;
				}
			)
		);
		//Reverse sorted data----------------------------------------------------------------
		threads.push_back
		(
			std::async
			(
				[&] 
				{
					std::list<int> dataCopy = _testData;

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
						_badSorts.push_back(i.first);
						return false;
					}

					_times.at(i.first).revSorted = end - start;
					return true;
				}
			)
		);
	}

	//Return true only if all tests passed
	bool success = true;
	for (auto& i : threads)
	{
		if (!i.get())
		{
			success = false;
		}
	}

	//clear memory
	_testData.clear();
	_sortedData.clear();
	_reverseSortedData.clear();

	return success;
}
