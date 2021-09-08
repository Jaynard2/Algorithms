#include <iostream>
#include <time.h>
#include "algorithms.h"
#include "SortTester.h"
#include "ThreadManager.h"

int main()
{
	std::cout << "Starting Automated Test" << std::endl;
	auto& threads = ThreadManager::getManager();

	SortTester Sorter(100000, 100000, 1, &threads);
	Sorter.addFunction("quickSort", TestingAlgorithms::quickSort);
	Sorter.addFunction("quickSort with median pivot", TestingAlgorithms::quickSort_modified);
	Sorter.addFunction("insertSort", TestingAlgorithms::insertSort);
	Sorter.addFunction("quickSort '1-pointer'", TestingAlgorithms::quickSort_alternate);
	Sorter.addFunction("quickSort '1-pointer' with median pivot", TestingAlgorithms::quickSort_modified_alternate);
	Sorter.startTest();

	const auto& result = Sorter.getResults();
	for (const auto& i : result) {
		std::cout << i.first << std::endl;

		for (const auto& j : i.second)
		{
			std::cout << "    " << j << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "Errors Encountered: ";
	auto error = Sorter.getBadSorts();
	std::cout << error.size() << std::endl;
	for (const auto& i : error) {
		std::cout << i.first << " " << i.second << std::endl;
	}

	return 0;
}
