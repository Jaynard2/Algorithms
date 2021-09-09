#include <iostream>
#include <time.h>
#include <vector>
#include <sstream>
#include <fstream>
#include "algorithms.h"
#include "SortTester.h"
#include "ThreadManager.h"

void writeDataToFile(const std::map<std::string, std::vector<TimeCompleted>>& results);

int main()
{
	bool exit = false;
	do 
	{
		auto& threads = ThreadManager::getManager();

		int dsize = 0;
		int dindex = 0;
		int dstep = 0;
		std::cout << "Input test parmaters" << std::endl << "Max size of Test: ";
		std::cin >> dsize;
		std::cout << "Starting Index: ";
		std::cin >> dindex;
		std::cout << "Incerment size: ";
		std::cin >> dstep;

		SortTester<std::list<int>> sorterList(dsize, dindex, dstep, &threads);
		std::cout << "Starting Automated Test" << std::endl;
		sorterList.addFunction("Linked List - quickSort", TestingAlgorithms::quickSort<std::list<int>>);
		sorterList.addFunction("Linked List - quickSort with median", TestingAlgorithms::quickSort_modified<std::list<int>>);
		sorterList.addFunction("Linked List - insertSort", TestingAlgorithms::insertSort<std::list<int>>);
		sorterList.addFunction("Linked List - quickSort alternate", TestingAlgorithms::quickSort_alternate<std::list<int>>);
		sorterList.addFunction("Linked List - quickSort alternate with median", TestingAlgorithms::quickSort_modified_alternate<std::list<int>>);
		sorterList.startTest();

		SortTester<std::vector<int>> sorterArr(dsize, dindex, dstep, &threads);
		/*std::cout << "Starting Automated Test" << std::endl;
		sorterArr.addFunction("Vector - quickSort", TestingAlgorithms::quickSort<std::vector<int>>);
		sorterArr.addFunction("Vector - quickSort with median", TestingAlgorithms::quickSort_modified<std::vector<int>>);
		sorterArr.addFunction("Vector - insertSort", TestingAlgorithms::insertSort<std::vector<int>>);*/
		sorterArr.addFunction("Vector - quickSort alternate", TestingAlgorithms::quickSort_alternate<std::vector<int>>);
		sorterArr.addFunction("Vector - quickSort alternate with median", TestingAlgorithms::quickSort_modified_alternate<std::vector<int>>);
		sorterArr.startTest();

		const auto& resultList = sorterList.getResults();
		for (const auto& i : resultList) {
			std::cout << i.first << std::endl;

			for (const auto& j : i.second)
			{
				std::cout << "    " << j << std::endl;
			}
		}

		writeDataToFile(resultList);

		std::cout << std::endl;
		std::cout << "Errors Encountered: ";
		auto error = sorterList.getBadSorts();
		std::cout << error.size() << std::endl;
		for (const auto& i : error) {
			std::cout << i.first << " " << i.second << std::endl;
		}

		const auto& resultArr = sorterArr.getResults();
		for (const auto& i : resultArr) {
			std::cout << i.first << std::endl;

			for (const auto& j : i.second)
			{
				std::cout << "    " << j << std::endl;
			}
		}

		writeDataToFile(resultArr);

		std::cout << std::endl;
		std::cout << "Errors Encountered: ";
		error = sorterArr.getBadSorts();
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

void writeDataToFile(const std::map<std::string, std::vector<TimeCompleted>>& results)
{
	for (const auto& i : results)
	{
		std::ofstream wr(i.first + ".csv");
		wr << "Count,Unsorted,Sorted,Reverse Sorted\n";
		for (const auto j : i.second)
		{
			wr << j << std::endl;
		}
	}
}
