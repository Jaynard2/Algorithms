#ifndef SORTTESTER_CPP//Impl for template class
#define SORTTESTER_CPP
#include "SortTester.h" //Included for intellsense
#include <algorithm>
#include <ctime>
#include <random>
#include <list>

template <typename T>
SortTester<T>::SortTester(unsigned int dataSize, unsigned int start, unsigned int step, ThreadManager* threads) : _sortFuncs(), _times()
{
	_testLength = dataSize;
	_testStartIndex = start;
	_step = step;
	_threadManager = threads;
	
	srand(time(NULL));
}

template <typename T>
void SortTester<T>::addFunction(std::string name, std::function<void(T&)> func)
{
	if (_sortFuncs.find(name) == _sortFuncs.end())
	{
		_sortFuncs.emplace(std::make_pair(name, func));
	}
}

template <typename T>
void SortTester<T>::startTest()
{
	//Make vectors large enough to hold all data
	_testData.resize(_testLength);
	_sortedData.resize(_testLength);

	//Generate random values for test data
	std::generate(_testData.begin(), _testData.end(), rand);

	//Create sorted data for comparison and sorted runs
	std::copy(_testData.begin(), _testData.end(), _sortedData.begin());
	std::sort(_sortedData.begin(), _sortedData.end());

	for (unsigned int testcount = _testStartIndex; testcount <= _testLength; testcount = testcount + _step) {
		for (auto& i : _sortFuncs)
		{
			if (testcount == _testStartIndex)
			{
				//pre-construct TimeCompleted to prevent race conditions
				_times.emplace(i.first, std::vector<TimeCompleted>());
				//initalize vector for each function to be tested
				_times.at(i.first).reserve((_testLength - _testStartIndex)/ _step);
			}

			_times.at(i.first).emplace_back(TimeCompleted{ std::chrono::duration<float>(0.0), std::chrono::duration<float>(0.0), std::chrono::duration<float>(0.0), testcount});

			//Unsorted data----------------------------------------------------------------------
			_threadManager->requestThread<int>
			(
				[this, i, testcount]
				{
					T dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_testData.begin(), this->_testData.begin() + testcount);

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					//Check that vakues are correctly sorted
					if (!this->isSorted(dataCopy))
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
					T dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_sortedData.begin(), this->_sortedData.begin() + testcount);

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!this->isSorted(dataCopy))
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
					T dataCopy;
					dataCopy.insert(dataCopy.begin(), this->_sortedData.rbegin(), this->_sortedData.rbegin() + testcount);

					auto start = std::chrono::high_resolution_clock::now();
					i.second(dataCopy);
					auto end = std::chrono::high_resolution_clock::now();

					if (!this->isSorted(dataCopy))
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
}

template <typename T>
bool SortTester<T>::writeToFile()
{
	return false;
}

template <typename T>
bool SortTester<T>::isSorted(T& l)
{
	if (l.size() <= 1)
	{
		return true;
	}

	for (auto i = std::next(l.begin()); i != l.end(); i++)
	{
		if (*i < *std::prev(i))
		{
			return false;
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream& out, const TimeCompleted& rhs)
{
	out << rhs.iteration << "," <<  rhs.unsorted.count() << "," << rhs.sorted.count()  << "," << rhs.revSorted.count();
	return out;
}

#endif
