#pragma once
#include <string>
#include <map>
#include <vector>

enum Vehicle {
	Car = 2,
	Truck = 3,
	Red = 4
};

struct Position {
	int x;
	int y;
	char orient;
	Vehicle type;
};

class RushHourTester {
public:
	RushHourTester() {
		resetBoard();
	}

	void addVehicle(int x, int y, char orient, Vehicle type);
	bool Test();

	std::string popError();

private:
	std::map<std::string, std::string> _SearchResults;
	std::string _Error;
	int _Board[7][7];

	unsigned char cordianteHash(int x, int y, char orient, Vehicle type);
	Position unHash(unsigned char pos);
	std::string SearchBoard();
	void buildBoard(std::string);
	bool shift(Position pos);

	void resetBoard();
};