#include <iostream>
#include <time.h>
#include "algorithms.h"
#include "SortTester.h"
#include "ThreadManager.h"

std::mutex io;

bool test();

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
		std::cout << "Incorment size: ";
		std::cin >> dstep;
		auto& threads = ThreadManager::getManager();

		SortTester Sorter(dsize, dindex, dstep, &threads);
		std::cout << "Starting Automated Test" << std::endl;
		Sorter.addFunction("quickSort", TestingAlgorithms::quickSort);
		Sorter.addFunction("quickSort_modified", TestingAlgorithms::quickSort_modified);
		Sorter.addFunction("insertSort", TestingAlgorithms::insertSort);
		Sorter.addFunction("quickSort_alternate", TestingAlgorithms::quickSort_alternate);
		Sorter.addFunction("quickSort_modified_alternate", TestingAlgorithms::quickSort_modified_alternate);
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

		std::cout << "Exit Program? ";
		char temp[5];
		std::cin >> temp;
		if (temp[0] == 'y') {
			exit = true;
		}
	} while (!exit);

	//unsigned id1 = threads.requestThread<bool>(test);
	//unsigned id2 = threads.requestThread<bool>(test);

	//Busy wait example (WARNING: IO DOES NOT HAVE PROPER LOCKING)
	/*bool thread1Done = false;
	bool thread2Done = false;
	std::any data1;
	std::any data2;
	while (!(thread1Done && thread2Done))
	{
		if(!thread1Done)
			data1 = threads.check(id1);
		if(!thread2Done)
			data2 = threads.check(id2);

		if (data1.has_value())
		{
			std::cout << "Thread 1: " << std::any_cast<bool>(data1) << std::endl;
			thread1Done = true;
		}
		else if(!thread1Done)
			std::cout << "Thread 1 working...\n";

		if (data2.has_value())
		{
			std::cout << "Thread 2: " << std::any_cast<bool>(data2) << std::endl;
			thread2Done = true;
		}
		else if(!thread2Done)
			std::cout << "Thread 2 working...\n";
	}

	//Blocking example

	std::unique_lock l(io);
	std::cout << "Thread 1: ";
	l.unlock();
	std::cout << std::any_cast<bool>(threads.get(id1)) << std::endl << std::flush;
	l.lock();
	std::cout << "Thread 2: " << std::flush;
	l.unlock();
	std::cout << std::any_cast<bool>(threads.get(id2)) << std::endl << std::flush;*/

	return 0;
}

bool test()
{
	static int counter = 0;

	unsigned count = 1000000000;
	while (count-- > 0);

	std::lock_guard l(io);
	std::cout << "This is test " << ++counter << std::endl;

	return true;
}
