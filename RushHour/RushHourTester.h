#pragma once
#include <string>
#include <map>
#include <vector>

enum Vehichle {
	Car = 2,
	Truck = 3,
	Red = 4
};

class RushHourTester {
public:

	void addVehicle(int x, int y, char orient, Vehichle type);
	bool Test();

	std::string popError();

private:
	std::map<std::string, std::pair<int, std::string>> _SearchResults;
	std::string _Error;
	int _Board[7][7];

	char cordianteHash(int x, int y, char orient, Vehichle type);
	void unHash(char pos);
	std::string SearchBoard();
	void buildBoard(std::string);
};