#pragma once

#include <list>
#include <algorithm>
#include <iterator>
#include <functional>

class TestingAlgorithms {
public:
	static void quickSort(std::list<int>& collection) {
		sorter_quick(collection, collection.begin(), --collection.end(), getPivot);
	};

	static void sorter_quick(std::list<int>& collection, std::list<int>::iterator begin, std::list<int>::iterator end, std::function<std::list<int>::iterator(std::list<int>::iterator, std::list<int>::iterator)> pivotPoint) {
		if (collection.size() <= 1) {
			return;
		}
		//gets the pivot point from the function pointer passed to the function
		//moves the pivot to the end
		std::list<int>::iterator pivot = pivotPoint(begin, end);
		auto start = begin;
		while (end != begin) {
			//move begining
			while(*begin < *pivot && begin != end) {
				begin++;
			}
			//move end
			while (*end >= *pivot && begin != end) {
				end--;
			}
			//switch values
			if (*begin > *end) {
				auto temp = *begin;
				*begin = *end;
				*end = temp;
			}
		}
		//switch the ending value that both end and begin stop on with the pivot value
		auto temp = *end;
		*end = *pivot;
		*pivot = temp;
		//Recurse if front is larger than one
		if (std::distance(start, begin) > 1) {
			--begin;
			sorter_quick(collection, start, begin, pivotPoint);
		}
		//Recurse if front is larger than two - pivot is included in this section
		if (std::distance(end, pivot) > 1) {
			end++;
			sorter_quick(collection, end, pivot, pivotPoint);
		}
	}

	static std::list<int>::iterator getPivot(std::list<int>::iterator begin, std::list<int>::iterator end) {
		return end;
	}

	static std::list<int>::iterator getPivot_modified(std::list<int>::iterator begin, std::list<int>::iterator end) {
		const int count = 3;
		int pivotIndecies[count];
		const int length = std::distance(begin, end);
		for (int i = 0; i < count; i++) {
			pivotIndecies[i] = rand() % length;
		}
		std::sort(pivotIndecies, pivotIndecies + count);
		auto pivot = begin;
		std::advance(pivot, pivotIndecies[count/2]);
		auto temp = *end;
		*end = *pivot;
		*pivot = temp;
		pivot = end;
		return pivot;
	}

	static void quickSort_modified(std::list<int>& collection) {
		sorter_quick(collection, collection.begin(), --collection.end(), getPivot_modified);
	};

	static void insertSort(std::list<int>& collection) {
		collection.push_front(-11);
		for (auto i = std::next(collection.begin(), 2); i != collection.end(); i++) {
			std::list<int>::iterator j;
			for (j = std::prev(i); *i < *j && j != collection.begin(); j--);
			j++;
			if (j != i) {
				collection.insert(j, *i);
				auto temp = std::prev(i);
				collection.erase(i);
				i = temp;
			}
		}
		collection.erase(collection.begin());
	};

	static void quickSort_alternate(std::list<int>& collection) {
		sorter_quick_alternate(collection, collection.begin(), --collection.end(), getPivot);
	};

	static void quickSort_modified_alternate(std::list<int>& collection) {
		sorter_quick_alternate(collection, collection.begin(), --collection.end(), getPivot_modified);
	};

	static void sorter_quick_alternate(std::list<int>& collection, std::list<int>::iterator begin, std::list<int>::iterator end, std::function<std::list<int>::iterator(std::list<int>::iterator, std::list<int>::iterator)> pivotPoint) {
		if (std::distance(begin, end) < 2) {
			return;
		}
		std::list<int>::iterator pivot = pivotPoint(begin, end);
		std::list<int>::iterator lower = begin;
		for (end = begin; end != std::prev(pivot); end++) {
			if (*end <= *pivot) {
				auto temp = *lower;
				*lower = *end;
				*end = temp;
				lower++;
			}
		}
		lower++;
		auto temp = *lower;
		*lower = *pivot;
		*pivot = temp;
		//Recurse if front is larger than two
		lower--;
		if (begin != lower) {
			sorter_quick_alternate(collection, begin, lower, pivotPoint);
		}
		//Recurse if larger than 1
		lower++;
		if (lower != pivot) {
			sorter_quick_alternate(collection, lower, pivot, pivotPoint);
		}
	};
};
