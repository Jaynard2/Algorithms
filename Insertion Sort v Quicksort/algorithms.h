#pragma once

#include <list>
#include <algorithm>
#include <vector>

class TestingAlgorithms {
public:
	static void quickSort(std::list<int> collection) {
		int pivotIndex = rand() % (collection.size() - 1);
		auto pivot = collection.begin();
		std::advance(pivot, pivotIndex);
		std::list<int> lower = qSort(&collection, pivot);
		if (collection.size() > 1) {
			quickSort(collection);
		}
		if (lower.size() > 1) {
			quickSort(lower);
		}
		collection.merge(lower);
	};

	static std::list<int> qSort(std::list<int>* collection, std::list<int>::iterator pivot) {
		std::list<int> lower = std::list<int>();
		std::vector<std::list<int>::iterator> tobeRemoved = std::vector<std::list<int>::iterator>();
		for (auto i = collection->begin(); i != collection->end(); i++) {
			if (*i < *pivot) {
				lower.push_back(*i);
				tobeRemoved.push_back(i);
			}
		}
		if (lower.size() == 0) {
			lower.push_back(*pivot);
			tobeRemoved.push_back(pivot);
		}
		for (int i = 0; i < tobeRemoved.size(); i++) {
			collection->erase(tobeRemoved[i]);
		}
		return lower;
	};

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
