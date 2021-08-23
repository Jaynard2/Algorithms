#include <iostream>
#include <future>
#include <vector>
#include <array>
#include <string>
#include <functional>
#include <mutex>

#include "algorithms.h"
#include "SortTester.h"

struct TestFunctions
{
	std::string name;
	std::function<void(std::list<int>&)> func;
};

int main()
{
	std::cout << "Starting Automated Test" << std::endl;

	std::vector<std::future<bool>> testThreads;
	std::vector<SortTester> tests;

	std::array<TestFunctions, 3> funcs =
	{
		"Quick Sort", TestingAlgorithms::quickSort,
		"Quick Sort Modified", TestingAlgorithms::quickSort_modified,
		"Insert Sort", TestingAlgorithms::insertSort
	};

	testThreads.reserve(1010);
	tests.reserve(1010);

	std::mutex mut;
	for (unsigned i = 1; i < 10000; i += 100)
	{
		std::lock_guard<std::mutex> lock(mut);

		tests.emplace_back(i);

		for (const auto& j : funcs)
		{
			tests.back().addFunction(j.name, j.func);
		}

		testThreads.emplace_back(std::async([&] { return tests.back().startTest(); }));
	}

	for (unsigned i = 15000; i < 1000000; i += 100000)
	{
		std::lock_guard<std::mutex> lock(mut);

		tests.emplace_back(i);

		for (const auto& j : funcs)
		{
			tests.back().addFunction(j.name, j.func);
		}

		testThreads.emplace_back(std::async([&] { return tests.back().startTest(); }));
	}

	bool success = true;
	for (auto& i : testThreads)
	{
		if (!i.get())
		{
			success = false;
		}
	}

	if (!success)
	{
		for (const auto& i : tests)
		{
			auto& badSorts = i.getBadSorts();
			if (badSorts.size() > 0)
			{
				for (const auto& j : badSorts)
				{
					std::cout << j << " ";
				}

				std::cout << std::endl;
			}
		}
	}

	return 0;
}
