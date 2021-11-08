#include <iostream>
#include <string>
#include <vector>
#include "RushHourTester.h"

int main()
{
	RushHourTester game;

	unsigned numCars;
	std::cin >> numCars;

	std::string type, color, dir;
	unsigned x, y;
	for (unsigned i = 0; i < numCars; i++)
	{
		std::cin >> type >> color >> dir >> y >> x;
		Vehicle vehicle;

		if (color == "red")
		{
			vehicle = Vehicle::Red;
		}
		else if (type == "car")
		{
			vehicle = Vehicle::Car;
		}
		else
		{
			vehicle = Vehicle::Truck;
		}

		game.addVehicle(x, y, dir.at(0), vehicle);
	}

	if (!game.Test())
	{
		std::cerr << game.popError() << std::endl;
		return -3;
	}

	auto re = game.Results();

	/*auto iter = re.rbegin();
	int i = 0;
	while (iter != re.rend()) {
		std::cout << *iter << " " << i++  << std::endl;
		iter++;
	}*/
	std::cout << std::to_string(re.size() - 1);

	return 0;
}
