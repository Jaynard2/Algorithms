#include "SortTester.h"
#include <algorithm>
#include <ctime>
#include <random>
#include <list>

SortTester::SortTester(unsigned int dataSize, unsigned int start, unsigned int step, ThreadManager* threads) : _sortFuncs(), _times()
{
	_testLength = dataSize;
	_testStartIndex = start;
	_step = step;
	_threadManager = threads;
	
	srand(time(NULL));
}

void SortTester::addFunction(std::string name, std::function<void(std::list<int>&)> func)
{
	if (_sortFuncs.find(name) == _sortFuncs.end())
	{
		_sortFuncs.emplace(std::make_pair(name, func));
	}
}

void SortTester::startTest()
{
	//Make vectors large enough to hold all data
	_testData.resize(_testLength);
	_sortedData.resize(_testLength);
	_reverseSortedData.resize(_testLength);

	//Generate random values for test data
	std::generate(_testData.begin(), _testData.end(), rand);

	//Create sorted data for comparison and sorted runs
	std::copy(_testData.begin(), _testData.end(), _sortedData.begin());
	std::sort(_sortedData.begin(), _sortedData.end());
	std::reverse_copy(_sortedData.begin(), _sortedData.end(), _reverseSortedData.begin());

	for (unsigned int testcount = _testStartIndex; testcount <= _testLength; testcount++) {

		for (auto& i : _sortFuncs)
		{
			//pre-construct TimeCompleted to prevent race conditions
			_times.emplace(i.first, TimeCompleted());
			_times.at(i.first).iteration = testcount;

			//Unsorted data----------------------------------------------------------------------
			_threadManager->requestThread<int>
			(
				[this, &i, &testcount]
				{
					std::list<int> dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_testData.begin(), this->_testData.begin() + (testcount - 1));

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					//Check that vakues are correctly sorted
					if (!std::equal(dataCopy.begin(), dataCopy.end(), this->_sortedData.begin()))
					{
						std::lock_guard lock(this->_badSort_lock);
						this->_badSorts.push_back(std::pair(i.first, testcount));
					}

					_times.at(i.first).unsorted = end - start;

					return 0;
				}
			);
			//Sorted data-------------------------------------------------------------------------
			/*_threadManager->requestThread<int>
			(
				[&]
				{
					std::list<int> dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_sortedData.begin(), this->_sortedData.begin() + (testcount - 1));

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
						std::lock_guard lock(this->_badSort_lock);
						this->_badSorts.push_back(std::pair(i.first, testcount));
					}

					this->_times.at(i.first).sorted = end - start;

					return 0;
				}
			);*/
			//Reverse sorted data----------------------------------------------------------------
			/*_threadManager->requestThread<int>
			(
				[&]
				{
					std::list<int> dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_reverseSortedData.begin(), this->_reverseSortedData.begin() + (testcount - 1));

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(dataCopy.begin(), dataCopy.end(), _sortedData.begin()))
					{
						std::lock_guard lock(this->_badSort_lock);
						this->_badSorts.push_back(std::pair(i.first, testcount));
					}

					this->_times.at(i.first).revSorted = end - start;

					return 0;
				}
			);*/
		}
	}
	
	_threadManager->joinAll();

	//clear memory
	_testData.clear();
	_sortedData.clear();
	_reverseSortedData.clear();
}

bool SortTester::writeToFile()
{
	return false;
}

std::ostream& operator<<(std::ostream& out, const TimeCompleted& rhs)
{
	out << rhs.iteration << "," << rhs.sorted.count() << "," << rhs.unsorted.count() << "," << rhs.revSorted.count();
	return out;
}
