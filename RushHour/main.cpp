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
		Vehichle vehicle;

		if (color == "red")
		{
			vehicle = Vehichle::Red;
		}
		else if (type == "car")
		{
			vehicle = Vehichle::Car;
		}
		else
		{
			vehicle = Vehichle::Car;
		}

		game.addVehicle(x, y, dir.at(0), vehicle);
	}

	if (!game.Test())
	{
		std::cout << game.popError() << std::endl;
	}

	return 0;
}
