#pragma once
#include <string>
#include <map>
#include <vector>

class RushHourTester {
public:

	void addVehicle(int x, int y, Vehichle type);
	bool Test();

	std::string popError();

private:
	std::map<std::string, std::pair<std::string, std::string>> _SearchResults;
	std::string _Error;

	std::string cordianteHash(int x, int y, Vehichle type);

};

enum Vehichle {
	Car = 2,
	Truck = 3
};