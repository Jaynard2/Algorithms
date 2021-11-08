#pragma once
#include <string>
#include <map>
#include <list>
#include <queue>
#include <array>
#include <iostream>

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
	RushHourTester();

	void addVehicle(int x, int y, char orient, Vehicle type, std::string color);
	bool Test();
	std::vector<std::string> Results();

	std::string popError();

private:
	std::map<std::string, std::string> _SearchResults;
	std::queue<std::map<std::string, std::string>::iterator> _work;
	std::list<std::pair<char, std::string>> _colors;

	std::string _Error;
	std::string _Final;
	std::array<std::array<int, 7>, 7> _Board;

	unsigned char coordinateHash(int x, int y, char orient, Vehicle type);
	Position unHash(unsigned char pos);
	std::string SearchBoard();
	void buildBoard(std::string);
	std::string shift(Position pos, std::string parent);
	void addVehicle(int x, int y, char orient, Vehicle type);

	void RemoveVehicle(Position pos);
	void resetBoard();

	void print(std::ostream& strm, std::string step, std::string next = "", int count = 0);

	friend std::ostream& operator<<(std::ostream& strm, RushHourTester& tester);
};

std::ostream& operator<<(std::ostream& strm, RushHourTester& tester);
