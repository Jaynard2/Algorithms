#include <iostream>
#include "SortTester.h"

int main()
{
	unsigned long amount = 0;
	std::cin >> amount;

	SortTester tester(amount);

	if (!tester.startTest())
	{
		std::cout << "The following sorts failed:\n";
		for (const auto& i : tester.getBadSorts())
		{
			std::cout << "\t" << i << std::endl;
		}
	}

	return 0;
}
