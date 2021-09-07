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

	for (unsigned int testcount = _testStartIndex; testcount <= _testLength; testcount = testcount + _step) {
		for (auto& i : _sortFuncs)
		{
			if (testcount == _testStartIndex)
			{
				//pre-construct TimeCompleted to prevent race conditions
				_times.emplace(i.first, std::vector<TimeCompleted>());
				_times.at(i.first).reserve(_testLength - _testStartIndex);
			}

			_times.at(i.first).emplace_back(TimeCompleted{ std::chrono::duration<float>(0.0), std::chrono::duration<float>(0.0), std::chrono::duration<float>(0.0), testcount});

			//Unsorted data----------------------------------------------------------------------
			_threadManager->requestThread<int>
			(
				[this, i, testcount]
				{
					std::list<int> dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_testData.begin(), this->_testData.begin() + testcount);

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					//Check that vakues are correctly sorted
					if (!std::equal(this->_sortedData.begin(), this->_sortedData.begin() + testcount, dataCopy.begin()))
					{
						std::lock_guard lock(this->_badSort_lock);
						this->_badSorts.push_back(std::pair(i.first + " Unsorted", testcount));
					}

					_times.at(i.first).at(testcount - this->_testStartIndex).unsorted = end - start;

					return 0;
				}
			);
			//Sorted data-------------------------------------------------------------------------
			_threadManager->requestThread<int>
			(
				[this, i, testcount]
				{
					std::list<int> dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_sortedData.begin(), this->_sortedData.begin() + testcount);

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(this->_sortedData.begin(), this->_sortedData.begin() + testcount, dataCopy.begin()))
					{
						std::lock_guard lock(this->_badSort_lock);
						this->_badSorts.push_back(std::pair(i.first + " Sorted", testcount));
					}

					this->_times.at(i.first).at(testcount - this->_testStartIndex).sorted = end - start;

					return 0;
				}
			);
			//Reverse sorted data----------------------------------------------------------------
			_threadManager->requestThread<int>
			(
				[this, i, testcount]
				{
					std::list<int> dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_reverseSortedData.begin(), this->_reverseSortedData.begin() + testcount);

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!std::equal(this->_sortedData.begin(), this->_sortedData.begin() + testcount, dataCopy.begin()))
					{
						std::lock_guard lock(this->_badSort_lock);
						this->_badSorts.push_back(std::pair(i.first + " Reverse Sorted", testcount));
					}

					this->_times.at(i.first).at(testcount - this->_testStartIndex).revSorted = end - start;

					return 0;
				}
			);
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
	out << rhs.iteration << "," <<  rhs.unsorted.count() << "," << rhs.sorted.count()  << "," << rhs.revSorted.count();
	return out;
}
