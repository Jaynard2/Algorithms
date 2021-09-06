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
		//moves the pivot to the end
		std::list<int>::iterator pivot = pivotPoint(begin, end);
		auto start = begin;
		while (end != begin) {
			//move begining
			while(*begin < *pivot && begin != end) {
				begin++;
			}
			//move end
			while(*end >= *pivot && begin != end) {
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
		//Recuse if front is larger than two
		if (start != begin && std::next(start) != pivot) {
			sorter_quick(collection, start, begin, pivotPoint);
		}
		//Recuse if front is larger than two
		end++;
		if (end != pivot && std::next(end) != pivot) {
			sorter_quick(collection, end, pivot, pivotPoint);
		}
		/*int copyCounter = 0;
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
		}*/	
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

	static void quickSort_alternate(std::list<int> collection) {
		sorter_quick_alternate(collection, collection.begin(), --collection.end(), getPivot);
	};

	static void quickSort_modified_alternate(std::list<int> collection) {
		sorter_quick_alternate(collection, collection.begin(), --collection.end(), getPivot_modified);
	};

	static void sorter_quick_alternate(std::list<int>& collection, std::list<int>::iterator begin, std::list<int>::iterator end, std::function<std::list<int>::iterator(std::list<int>::iterator, std::list<int>::iterator)> pivotPoint) {
		if (std::distance(begin, end) < 2) {
			return;
		}
		std::list<int>::iterator pivot = pivotPoint(begin, end);
		std::list<int>::iterator lower = begin;
		for (end = begin; end != pivot; end++) {
			if (*end <= *pivot) {
				auto temp = *lower;
				*lower = *end;
				*end = temp;
				lower++;
			}
		}
		auto temp = *lower;
		*lower = *end;
		*end = temp;
		//Recuse if front is larger than two
		if (begin != lower && std::next(begin) != lower) {
			sorter_quick_alternate(collection, begin, lower, pivotPoint);
		}
		//Recuse if front is larger than two
		lower++;
		if (lower != end && std::next(lower) != end) {
			sorter_quick_alternate(collection, lower, end, pivotPoint);
		}
	};
};
