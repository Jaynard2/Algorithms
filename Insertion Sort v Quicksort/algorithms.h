#ifndef ALGORITHMS_TO_BE_TESTED
#define ALGORITHMS_TO_BE_TESTED

#include <list>
#include <algorithm>
#include <vector>
#include <iterator>

class TestingAlgorithms{
public:
	static void quickSort(std::list<int> collection) {
		sorter_quick(collection, collection.begin(), --collection.end());
	};

	static void sorter_quick(std::list<int>& collection, std::list<int>::iterator begin, std::list<int>::iterator end) {
		int pivotIndex = rand() % (std::distance(begin, end));
		auto pivot = begin;
		std::advance(pivot, pivotIndex);
		int copyCounter = 0;
		for (auto i = begin; i != pivot; i) {
			if (*i > *pivot) {
				collection.insert(std::next(pivot), *i);
				if (begin == i) {
					begin++;
				}
				i++;
				copyCounter++;
				collection.erase(std::prev(i));
			}
			else {
				i++;
			}
		}
		auto stop = std::next(pivot, copyCounter);
		for (auto i = end; i != stop; i) {
			if (*i < *pivot) {
				collection.insert(pivot, *i);
				if (end == i) {
					end--;
				}
				else if (begin == pivot) {
					begin--;
				}
				i--;
				collection.erase(std::next(i));
			}
			else {
				i--;
			}
		}
		if(begin != pivot && std::next(begin) != pivot){
			sorter_quick(collection, begin, pivot);
		}
		if (end != pivot++ && end != pivot) {
			sorter_quick(collection, pivot, end);
		}
	}

	static void quickSort_modified(std::list<int> collection) {
		const int count = 3;
		int pivotIndecies[count];
		for (int i = 0; i < count; i++) {
			pivotIndecies[i] = rand() % (collection.size() - 1);
		}
		//std::sort(pivotIndecies, pivotIndecies + count);
		auto pivot = collection.begin();
		std::advance(pivot, pivotIndecies[count / 2]);
		auto lower = qSort(&collection, pivot);
		quickSort_modified(collection);
		quickSort_modified(lower);
	};

	static void insertSort(std::list<int> collection) {
		for (auto i = collection.begin(); i != collection.end(); i++) {
			for (auto j = i; j != collection.begin(); j--) {
				if (*i < *j) {
					collection.insert(j, *i);
					collection.erase(i);
					break;
				}
			}
		}
	};
};
#endif