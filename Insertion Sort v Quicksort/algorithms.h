#pragma once

#include <list>
#include <algorithm>
#include <iterator>
#include <functional>

class TestingAlgorithms {
public:
	static void quickSort(std::list<int> collection) {
		sorter_quick(collection, collection.begin(), --collection.end(), getPivot);
	};

	static void sorter_quick(std::list<int>& collection, std::list<int>::iterator begin, std::list<int>::iterator end, std::function<std::list<int>::iterator(std::list<int>::iterator, std::list<int>::iterator)> pivotPoint) {
		if (collection.size() <= 1) {
			return;
		}
		//gets the pivot point from the function pointer passed to the function
		std::list<int>::iterator pivot = pivotPoint(begin, end);
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
			sorter_quick(collection, begin, pivot, pivotPoint);
		}
		if (end != pivot++ && end != pivot) {
			sorter_quick(collection, pivot, end, pivotPoint);
		}
	}

	static std::list<int>::iterator getPivot(std::list<int>::iterator begin, std::list<int>::iterator end) {
		int pivotIndex = rand() % (std::distance(begin, end));
		auto pivot = begin;
		std::advance(pivot, pivotIndex);
		return pivot;
	}

	static std::list<int>::iterator getPivot_modified(std::list<int>::iterator begin, std::list<int>::iterator end) {
		const int count = 3;
		int pivotIndecies[count];
		for (int i = 0; i < count; i++) {
			pivotIndecies[i] = rand() % (std::distance(begin, end));
		}
		std::sort(pivotIndecies, pivotIndecies + count);
		auto pivot = begin;
		std::advance(pivot, pivotIndecies[count/2]);
		return pivot;
	}

	static void quickSort_modified(std::list<int> collection) {
		sorter_quick(collection, collection.begin(), --collection.end(), getPivot_modified);
	};

	static void insertSort(std::list<int> collection) {
		for (auto i = collection.begin(); i != collection.end(); i) {
			for (auto j = i; j != collection.begin(); j--) {
				if (*i < *j) {
					collection.insert(j, *i);
					i++;
					collection.erase(std::next(i));
					break;
				}
				else {
					i++;
				}
			}
		}
	};
};
