#pragma once

#include <algorithm>
#include <iterator>
#include <functional>

class TestingAlgorithms {
public:
	template <typename T>
	static void quickSort(T& collection) {
		sorter_quick<T>(collection, collection.begin(), --collection.end(), getPivot<T>);
	};

	template <typename T>
	static void quickSort_modified(T& collection) {
		sorter_quick<T>(collection, collection.begin(), --collection.end(), getPivot_modified<T>);
	};

	template <typename T>
	static void quickSort_alternate(T& collection) {
		sorter_quick_alternate<T>(collection, collection.begin(), --collection.end(), getPivot<T>);
	};

	template <typename T>
	static void quickSort_modified_alternate(T& collection) {
		sorter_quick_alternate<T>(collection, collection.begin(), --collection.end(), getPivot_modified<T>);
	};

	template <typename T>
	static void sorter_quick(T& collection, typename T::iterator begin, typename T::iterator end, std::function<typename T::iterator(typename T::iterator&, typename T::iterator&)> pivotPoint) {
		if (collection.size() <= 1) {
			return;
		}
		//gets the pivot point from the function pointer passed to the function
		//moves the pivot to the end
		typename T::iterator pivot = pivotPoint(begin, end);
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
			sorter_quick<T>(collection, start, begin, pivotPoint);
		}
		//Recurse if front is larger than two - pivot is included in this section
		if (std::distance(end, pivot) > 1) {
			end++;
			sorter_quick<T>(collection, end, pivot, pivotPoint);
		}
	}

	template <typename T>
	static void insertSort(T& collection) {
		collection.emplace_front(-11);
		for (auto i = std::next(collection.begin(), 2); i != collection.end(); i++) {
			typename T::iterator j;
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

	template <typename T>
	static void sorter_quick_alternate(T& collection, typename T::iterator begin, typename T::iterator end,
		std::function<typename T::iterator(typename T::iterator&, typename T::iterator&)> pivotPoint) {
		if (std::distance(begin, end) < 1) {
			return;
		}
		typename T::iterator pivot = pivotPoint(begin, end);
		collection.emplace(begin, -11);
		typename T::iterator lower = std::prev(begin);
		for (end = begin; end != pivot; end++) {
			if (*end <= *pivot) {
				lower++;
				auto temp = *lower;
				*lower = *end;
				*end = temp;
			}
		}
		lower++;
		auto temp = *lower;
		*lower = *pivot;
		*pivot = temp;
		collection.erase(std::prev(begin));
		//Recurse if front is larger than two
		if (std::distance(begin, lower) > 1) {
			sorter_quick_alternate(collection, begin, std::prev(lower), pivotPoint);
		}
		//Recurse if larger than 1
		if (lower != pivot) {
			sorter_quick_alternate(collection, std::next(lower), pivot, pivotPoint);
		}
	};

	template <typename T>
	static typename T::iterator getPivot(typename T::iterator begin, typename T::iterator &end) { return end; }

	template <typename T>
	static typename T::iterator getPivot_modified(typename T::iterator &begin, typename T::iterator &end) {
		const int count = 3;
		typename T::iterator pivotIndecies[count];
		typename T::iterator pivot;
		const int length = std::distance(begin, end);
		for (int i = 0; i < count; i++) {
			int test = rand();
			pivotIndecies[i] = std::next(begin, test % length);
		}
		if (*pivotIndecies[1] < *pivotIndecies[0]) {
			if (*pivotIndecies[2] > *pivotIndecies[0]) {
				pivot = pivotIndecies[0];
			}
			else if (*pivotIndecies[1] < *pivotIndecies[2]) {
				pivot = pivotIndecies[1];
			}
			else {
				pivot = pivotIndecies[2];
			}
		}
		else {
			if (*pivotIndecies[2] > *pivotIndecies[1]) {
				pivot = pivotIndecies[1];
			}
			else if (*pivotIndecies[0] < *pivotIndecies[2]) {
				pivot = pivotIndecies[0];
			}
			else {
				pivot = pivotIndecies[2];
			}
		}
		auto temp = *end;
		*end = *pivot;
		*pivot = temp;
		return end;
	}
};
