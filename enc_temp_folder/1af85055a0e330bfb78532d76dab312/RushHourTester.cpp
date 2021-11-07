#include "RushHourTester.h"


bool RushHourTester::Test() {

	unsigned char one = cordianteHash(1, 1, 'v', Truck);
	Position pos = unHash(one);
	unsigned char two = cordianteHash(2, 4, 'h', Truck);
	pos = unHash(two);
	unsigned char three = cordianteHash(4, 6, 'v', Car);
	pos = unHash(three);
	unsigned char four = cordianteHash(1, 3, 'h', Red);
	pos = unHash(four);
	//std::string base = "";
	//_SearchResults.insert(SearchBoard(), base);

	//for (auto obj : _SearchResults) {
	//	buildBoard(obj.first);
	//	for (int i = 0; i < obj.first.length(); i++) {
	//		Position current = unHash(obj.first[i]);
	//		if (shift(current)) { //Returns True if Read Car Escaps
	//			_SearchResults.insert(SearchBoard(), obj.first);
	//			return true;
	//		}
	//		_SearchResults.insert(SearchBoard(), obj.first);
	//	}
	//}

	return true;

}

void RushHourTester::addVehicle(int x, int y, char orient, Vehicle type) {
	if (orient == 'h') {
		for (int i = x; i < type; i++) {
			_Board[i][y] = type;
		}
	}
	else if (orient == 'v') {
		for (int j = y; j < type; j++) {
			_Board[x][j] = type + 10;
		}
	}
}

std::string RushHourTester::popError() {
	if (_Error == "") {
		return "";
	}
	auto temp = _Error;
	_Error = "";
	return temp;
}

unsigned char RushHourTester::cordianteHash(int x, int y, char orient, Vehicle type) 
{
	bool isRed = type == Red;
	char val = (x << 5) + (y << 2) + ((orient == 'v') << 1) + (type - 2) * !isRed;
	if (isRed)
	{
		val |= 0x1C;
	}

	return val;
}

Position RushHourTester::unHash(unsigned char pos) 
{
	int x = pos >> 5;
	int y = (pos & 0x1C) >> 2;
	Vehicle type;
	if (y == 7)
	{
		type = Red;
		y = 3;
	}
	else
	{
		type = (Vehicle)((pos & 0x01) + 2);
	}
	char orient = ((pos & 0x02) ? 'v' : 'h');
	

	return { x, y, orient, type };
}

std::string RushHourTester::SearchBoard() {
	std::string BoardHash = "";
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7; j++) {
			int val = _Board[i][j];
			if (val == 0) {
				continue;
			}
			else if (val > 10) {
				//vertial
				val -= 10;
				BoardHash += cordianteHash(i, j, 'v', (Vehicle)val);
				for (int k = j; k < (j + val); k++) {
					_Board[i][k] = 0;
				}
			}
			else {
				BoardHash += cordianteHash(i, j, 'h', (Vehicle)val);
				for (int k = i; k < (i + val); k++) {
					_Board[k][j] = 0;
				}
			}
		}
	}

	return "";
}
void RushHourTester::buildBoard(std::string input) {
	for (int i = 0; i < input.length(); i++) {
		unHash(input[i]);
	}
}

void RushHourTester::resetBoard() {
	for (int i = 0; i < 7; i++) {
		memset(_Board[i], 0, 7);
	}
}

bool RushHourTester::shift(Position pos) {
	return true;
	if (pos.type = Red) {
	
	}
	else {
	
	}
}