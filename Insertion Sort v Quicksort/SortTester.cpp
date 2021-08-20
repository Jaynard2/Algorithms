#include "SortTester.h"
#include <algorithm>
#include <ctime>
#include <random>
#include <thread>
#include <exception>
#include <vector>
#include <future>

SortTester::SortTester(unsigned long dataSize)
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
	std::sort(_sortedData.begin(), _sortedData.end());
	std::reverse_copy(_sortedData.begin(), _sortedData.end(), _reverseSortedData.begin());
}

void SortTester::addFunction(std::string name, std::function<void(std::list<int>&)> func)
{
	_testAmount++;
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
					auto dataCopy = _testData;

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					//Check that vakues are correctly sorted
					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
						return false;
					}

					_times.at(i.first).unsorted = end-start;
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
					auto dataCopy = _testData;

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
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
					auto dataCopy = _testData;

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
						return false;
					}

					_times.at(i.first).revSorted = end - start;
					return true;
				}
			)
		);
	}

	//Return true only if all tests passed
	for (auto& i : threads)
	{
		if (!i.get())
		{
			return false;
		}
	}

	return true;
}
