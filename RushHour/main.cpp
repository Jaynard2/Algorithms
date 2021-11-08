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

		game.addVehicle(x, y, dir.at(0), vehicle, color);
	}

	if (!game.Test())
	{
		std::cerr << game.popError() << std::endl;
		return -3;
	}

	std::cout << game;

	return 0;
}
