#pragma once
#include <string>
#include <map>
#include <vector>
#include <queue>

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
		_Final = "";
	}

	void addVehicle(int x, int y, char orient, Vehicle type);
	bool Test();
	std::vector<std::string> Results();

	std::string popError();

private:
	std::map<std::string, std::string> _SearchResults;
	std::queue<std::map<std::string, std::string>::iterator> _work;

	std::string _Error;
	std::string _Final;
	int _Board[7][7];

	unsigned char coordinateHash(int x, int y, char orient, Vehicle type);
	Position unHash(unsigned char pos);
	std::string SearchBoard();
	void buildBoard(std::string);
	std::string shift(Position pos, std::string parent);

	void RemoveVehicle(Position pos);
	void resetBoard();
};