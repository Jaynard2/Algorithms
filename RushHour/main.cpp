#include <iostream>
#include <string>
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
		std::cin >> type >> color >> dir >> x >> y;
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
			vehicle = Vehicle::Car;
		}

		game.addVehicle(x, y, dir.at(0), vehicle);
	}

	if (!game.Test())
	{
		std::cout << game.popError() << std::endl;
	}

	return 0;
}
