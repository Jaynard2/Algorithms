#include "RushHourTester.h"


bool RushHourTester::Test() {
	std::string base = "";
	_SearchResults.insert(SearchBoard(), base);

	for (auto obj : _SearchResults) {
		buildBoard(obj.first);
		for (int i = 0; i < obj.first.length(); i++) {
			Position current = unHash(obj.first[i]);
			if (shift(current)) {
				_SearchResults.insert(SearchBoard(), obj.first);
				return true;
			}
			_SearchResults.insert(SearchBoard(), obj.first);
		}
	}

}

void RushHourTester::addVehicle(int x, int y, char orient, Vehichle type) {
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

unsigned char RushHourTester::cordianteHash(int x, int y, char orient, Vehichle type) {
	orient = (orient == 'v');
	return ((x + (y + 10)) + (orient * 50) + ((type - 2) * 100);
}

void RushHourTester::unHash(unsigned char pos) {
	if (pos > 200) {
		pos -= 200;
		if (pos > 50) {
			addVehicle(pos, pos, 'v', Red);
		}
		else {
			addVehicle(pos, pos, 'h', Red);
		}
	}
	else if (pos > 100) {
		pos -= 100;
		if (pos > 50) {
			addVehicle(pos, pos, 'v', Truck);
		}
		else {
			addVehicle(pos, pos, 'h', Truck);
		}
	}
	else {
		if (pos > 50) {
			addVehicle(pos, pos, 'v', Car);
		}
		else {
			addVehicle(pos, pos, 'h', Car);
		}
	}
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
				BoardHash += cordianteHash(i, j, 'v', (Vehichle)val);
				for (int k = j; k < (j + val); k++) {
					_Board[i][k] = 0;
				}
			}
			else {
				BoardHash += cordianteHash(i, j, 'h', (Vehichle)val);
				for (int k = i; k < (i + val); k++) {
					_Board[k][j] = 0;
				}
			}
		}
	}
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
	if (pos.type = Red) {
	
	}
	else {
	
	}
}