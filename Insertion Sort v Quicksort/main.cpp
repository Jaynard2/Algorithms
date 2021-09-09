#include <iostream>
#include <time.h>
#include "algorithms.h"
#include "SortTester.h"
#include "ThreadManager.h"

int main()
{
	bool exit = false;
	do {
		int dsize = 0;
		int dindex = 0;
		int dstep = 0;
		std::cout << "Input test parmaters" << std::endl << "Max size of Test: ";
		std::cin >> dsize;
		std::cout << "Starting Index: ";
		std::cin >> dindex;
		std::cout << "Incerment size: ";
		std::cin >> dstep;
		auto& threads = ThreadManager::getManager();

		SortTester<std::list<int>> Sorter(dsize, dindex, dstep, &threads);
		std::cout << "Starting Automated Test" << std::endl;
		Sorter.addFunction("quickSort", TestingAlgorithms::quickSort<std::list<int>>);
		Sorter.addFunction("quickSort_modified", TestingAlgorithms::quickSort_modified<std::list<int>>);
		Sorter.addFunction("insertSort", TestingAlgorithms::insertSort<std::list<int>>);
		Sorter.addFunction("quickSort_alternate", TestingAlgorithms::quickSort_alternate<std::list<int>>);
		Sorter.addFunction("quickSort_modified_alternate", TestingAlgorithms::quickSort_modified_alternate<std::list<int>>);
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

		std::cout << "Run again? ";
		char temp[5];
		std::cin >> temp;
		if (temp[0] != 'y') {
			exit = true;
		}
	} while (!exit);

	return 0;
}
